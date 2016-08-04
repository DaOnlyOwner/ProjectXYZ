// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "CustomGameState.h"
#include "Spell.h"
#include "ChargeableSpell.h"
#include "Element.h"
#include "UnrealNetwork.h"
#include "SpellSystemConstants.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);
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
	GEngine->AddOnScreenDebugMessage(11, 2.0f, FColor::Red, "replicated elemQueue changed");
	UE_LOG(LogTemp, Warning, TEXT("replicated elemQueue changed"));
	return;
}

/* ROLE_AutonomousProxy */
void APlayerCharacter::ReleaseSpellForward()
{
    if (elementQueue.Num() == 0 || State != READY)
		return;

	ReleaseSpellForwardNet();
	elementQueue.Empty();
}

/* ROLE_authority */
void APlayerCharacter::ReleaseSpellForwardNet_Implementation()
{
	GEngine->AddOnScreenDebugMessage(14, 2.0f, FColor::Red, "right click DOWN");
	
	if (State != READY) {// player is busy doing something else, can't cast anything right now.
		return;
	}

	currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(elementQueue, false);

	if (currentSpell->Type == Spelltype::Charged)
	{
		State = BUSY_CHARGING;

		GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::endCharge, MAX_CHARGE_TIME, 0);
		GEngine->AddOnScreenDebugMessage(15, 2.0f, FColor::Red, "spawned rock");
	}

}
bool APlayerCharacter::ReleaseSpellForwardNet_Validate()
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
		GetWorldTimerManager().SetTimer(timerHandler, this, &APlayerCharacter::setStateToReady, KNOCKED_DOWN_TIME, 0);
	}
}

/* ROLE_Authority */
void APlayerCharacter::setStateToReady()
{
	State = READY;
}
void APlayerCharacter::ReleaseSpellSelf()
{

}

void APlayerCharacter::KeyupForward()
{
	if (currentSpell != nullptr && State == BUSY_CHARGING && currentSpell->Type == Spelltype::Charged)
	{
		KeyupForwardNet();
	}
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

		GEngine->AddOnScreenDebugMessage(16, 5.0f,  FColor::Red, FString::SanitizeFloat(elapsedTime));
		static_cast<AChargeableSpell*>(currentSpell)->SetChargedTime(elapsedTime);
		currentSpell->StartBehavior(*this);
	}
	else if (State == BUSY_BEAMING || State == BUSY_SPRAYING)
	{
		currentSpell->EndBehavior();
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
	FString string = "Enforced new state: ";
	string += FString::SanitizeFloat(State);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);
}



