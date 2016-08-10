// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "CustomGameState.h"
#include "Spell.h"
#include "ChargeableSpell.h" 
#include "SpraySpell.h"
#include "AoESpell.h"
#include "Element.h"
#include "UnrealNetwork.h"
#include "SpellSystemConstants.h"
#include "PlayerCharacterController.h"


#define PRINTSCR(text) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 50.0f, FColor::Orange, text, true)

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);
	State = READY;
}

APlayerCharacter::~APlayerCharacter()
{
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	startOffset = camera->GetRelativeTransform().GetLocation();
	camera->DetachFromParent(true, true);
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacter, elementQueue);
	DOREPLIFETIME(APlayerCharacter, currentSpell);
	DOREPLIFETIME(APlayerCharacter, State);
	DOREPLIFETIME(APlayerCharacter, wards);
	DOREPLIFETIME(APlayerCharacter, Health);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	moveCamera(DeltaTime);
}

/* ROLE_AutonomousProxy */
void APlayerCharacter::AddElementToQueue(CElement & newElement)
{
	if(!elementQueue.RemoveSingle(newElement.GetCancelledBy()) &&
		!elementQueue.RemoveSingle(newElement.GetCancelledBy2()) &&
		elementQueue.Num() < 3)
		elementQueue.Push(newElement.GetID());

	FString string = "My Queue: ";
	for (int i = 0; i < elementQueue.Num(); i++)
		string += CElement::GetCElementByID((ElementID)elementQueue[i]).GetLetter();
	GEngine->AddOnScreenDebugMessage(13, 5.0f, FColor::Red, string);
}

void APlayerCharacter::onElementQueueChange()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "replicated elemQueue changed", true);
	UE_LOG(LogTemp, Warning, TEXT("replicated elemQueue changed"));
	return;
}
/* ROLE_authority && ROLE_AutonomousProxy*/
int APlayerCharacter::QueueToSpellType(TArray<uint8> elemQueue)
{
	if (!elemQueue.Contains(SHIELD_ELEM))
	{
		if (elemQueue.Contains(EARTH_ELEM))
			return Charged;
		else if (((elemQueue.Contains(DEATH_ELEM) || elemQueue.Contains(LIFE_ELEM))) /* beam*/
			|| (!elemQueue.Contains(LIGHTNING_ELEM) && !elemQueue.Contains(EARTH_ELEM))) /* spray */
			return Channeled;
		return Burst;
	}
	return Burst;
}

/* ROLE_AutonomousProxy */
void APlayerCharacter::ReleaseSpellForward()
{
	if (elementQueue.Num() == 0 || State != READY)
		return;
	ReleaseSpellForwardNet(elementQueue);
}

/* ROLE_authority */
void APlayerCharacter::ReleaseSpellForwardNet_Implementation(const TArray<uint8> & elemQueue)
{
	GEngine->AddOnScreenDebugMessage(14, 2.0f, FColor::Red, "right click DOWN");
	
	if (State != READY) {// player is busy doing something else, can't cast anything right now.
		return;
	}

	serverSideElementQueue = elemQueue;

	if (QueueToSpellType(elemQueue) == Charged)
	{
		State = BUSY_CHARGING;
		GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::endCharge, MAX_CHARGE_TIME, 0);
	}
	else if (QueueToSpellType(elemQueue) == Channeled)
	{
		State = BUSY_CHANNELING;
		currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(serverSideElementQueue, false);
		/*currentSpell->SetOwner(this);*/
		currentSpell->AttachRootComponentToActor(this, NAME_None, EAttachLocation::KeepRelativeOffset);
		/*GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::endCharge, MAX_CHANNEL_TIME, 0);*/
	}
}
bool APlayerCharacter::ReleaseSpellForwardNet_Validate(const TArray<uint8> & elemQueue)
{
	return true;
}

void APlayerCharacter::beginCharge()
{
	// Animations, Particles missing
}

/* ROLE_Authority */
void APlayerCharacter::endCharge()
{
	if (State == BUSY_CHARGING)
	{
		KeyupForwardNet(); // release the spell
		State = BUSY_KNOCKED;
		SetReplicateMovement(false);
		GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::setStateToReady, KNOCKED_DOWN_TIME, 0);
	}
	else if (State == BUSY_CHANNELING)
	{
		KeyupForwardNet();
		State = READY;
	}
}

/* ROLE_Authority */
void APlayerCharacter::setStateToReady()
{
	State = READY;
	SetReplicateMovement(true);
	
}
void APlayerCharacter::ReleaseSpellSelf()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "middle click DOWN - client", true);

	if (elementQueue.Num() == 0 || State != READY)
		return;
	ReleaseSpellSelfNet(elementQueue);
	elementQueue.Empty();
}
void APlayerCharacter::ReleaseSpellSelfNet_Implementation(const TArray<uint8> & elemQueue)
{
	GEngine->AddOnScreenDebugMessage(14, 2.0f, FColor::Red, "middle click DOWN - server");

	if (State != READY) {// player is busy doing something else, can't cast anything right now.
		return;
	}
		
	serverSideElementQueue = elemQueue;
	State = BUSY_PLACING_SPELL;
	if (elemQueue.Contains(SHIELD_ELEM))
	{
		// Assign wards
		wards.Empty();
		if (elemQueue.Num() >= 2)
		{
			for (uint8 i = 0; i < elemQueue.Num(); i++)
			{
				if (elemQueue[i] != ElementID::SHIELD_ELEM)
				{
					wards.Add(elemQueue[i]);
				}
			}
			State = READY;
		}
		else
		{
			// it's a dome shield
		}
	}
	else
	{
		// it's an AoE
		currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(serverSideElementQueue, true);
		currentSpell->StartBehavior(*this);
		GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::setStateToReady, 0.5f, 0);

	}


}
bool APlayerCharacter::ReleaseSpellSelfNet_Validate(const TArray<uint8> & elemQueue)
{
	return true;
}


void APlayerCharacter::KeyupForward()
{
	if ((QueueToSpellType(elementQueue) == Charged && State == BUSY_CHARGING)
		|| QueueToSpellType(elementQueue) == Channeled && State == BUSY_CHANNELING )
	{
		KeyupForwardNet();
	}
	elementQueue.Empty();
}
/* ROLE_authority */
void APlayerCharacter::KeyupForwardNet_Implementation()
{
	GEngine->AddOnScreenDebugMessage(14, 2.0f, FColor::Red, "right click UP ");

	if (State == BUSY_CHARGING)
	{
		float elapsedTime = GetWorldTimerManager().GetTimerElapsed(this->timerHandler);
		GetWorldTimerManager().ClearTimer(timerHandler);
	
		if (elapsedTime < 0.0f) // when comming from endCharge it somehow has negative value
		{
			elapsedTime = MAX_CHARGE_TIME;
		}
		State = READY;
		
		currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(serverSideElementQueue, false);
		GEngine->AddOnScreenDebugMessage(16, 5.0f,  FColor::Red, FString::SanitizeFloat(elapsedTime));
		static_cast<AChargeableSpell*>(currentSpell)->SetChargedTime(elapsedTime);
		currentSpell->StartBehavior(*this);
	}
	else if (State == BUSY_CHANNELING)
	{
		currentSpell->EndBehavior();
		State = READY;
	}
	else if (State == BUSY_HEALING)
	{
		// stop healing
	}

}
bool APlayerCharacter::KeyupForwardNet_Validate()
{
	return true;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (!HasAuthority()) return 0;
	ASpell* spell;
	if ( (spell = Cast<ASpell>(DamageCauser)) != nullptr)
	{
		// DamageCauser is a spell;
		FDamageInformation damage = spell->CalcDamageBasedOnWards(wards, Status); // We have to compute it here because of additional information needed (wards etc.)
		Status = damage.computedStatus;
		Health -= damage.computedDamage;
		if (Health <= 0)
		{
			KillActor(damage.spellType);
		}

		return damage.computedDamage;
	}

	else
	{


		// DamageCauser is self - caused by burning
		int fireWardAmount = 0;
		for (int i = 0; i < 2; i++)
		{
			if (wards[i] == ElementID::FIRE_ELEM)
			{
				fireWardAmount++;
			}
		}

		if(fireWardAmount > 0)
			DamageAmount = fireWardAmount == 1 ? DamageAmount * 0.5f : 0;

		return DamageAmount;
	}
}

void APlayerCharacter::KillActor(Spelltype spellType)
{
	if (!HasAuthority()) return;
	// Spawn animations, particles etc. for death based on the spellType (for example Charged will smash the player to pieces)
}

void APlayerCharacter::moveCamera(float DeltaTime)
{
	int x;
	int y;

	float xM;
	float yM;
	APlayerController* controller = static_cast<APlayerController*>(GetController());
	if (!controller)return;

	controller->GetViewportSize(x, y);
	if (controller->GetMousePosition(xM, yM))
	{
		float normX = (xM / (float)x - .5f);
		float normY = -1 * (yM / (float)y - .5f);

		FVector norm{ normY, normX, 0 };

		FVector cameraLocationToGo = FMath::VInterpTo(camera->GetComponentLocation(), GetActorLocation() + startOffset + norm*ScreenScale, DeltaTime, SmoothingTime);
		camera->SetWorldLocation(cameraLocationToGo);
	}
}
void APlayerCharacter::onStateChange()
{
	/*FString string = "Enforced new state: ";
	string += FString::SanitizeFloat(State);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);*/
}
void APlayerCharacter::onCurrentSpellChange()
{
	/*GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, "current spell changed", true);*/
}

void APlayerCharacter::onWardChange()
{
	/*FString print = "";
	print += "Wards Changed for " + this->GetHumanReadableName();
	print += "Ward1: " + (wards.Num() > 0 ? FString::SanitizeFloat(wards[0]) : TEXT("Null"));
	print += "Ward2: " + (wards.Num() > 1 ? FString::SanitizeFloat(wards[1]) : TEXT("Null"));
	PRINTSCR(print);*/
}




