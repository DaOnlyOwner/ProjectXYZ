// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "CustomGameState.h"
#include "Spell.h"
#include "ChargeableSpell.h"
#include "UnrealNetwork.h"


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
	DOREPLIFETIME(APlayerCharacter, ElemQueue);
}


// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FString string;
	/*for (int i = 0; i < elementQueueSize; i++)
	{
		string += elementQueue[i]->GetName();
	}*/
	string = FString::FromInt(ElemQueue.element1);

	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Red, string,true, FVector2D{ 5,5 });
	moveCamera(DeltaTime);
	
}

void APlayerCharacter::AddElemToQueue_Implementation(int element_id)
{
	UE_LOG(LogTemp, Warning, TEXT("server func"));
	ElemQueue.element1 = element_id; /* TODO */
}
bool APlayerCharacter::AddElemToQueue_Validate(int name)
{
	return true;
}

void APlayerCharacter::AddElementToQueue(CElement &e)
{

	AddElemToQueue(e.GetName()); /* this is debug */

	for (int i = 0; i < elementQueueSize; i++)
	{
		if (e.Cancels(*elementQueue[i]))
		{
			// Remove elementQueue[i] and resize.
			for (int k = i; k < elementQueueSize - 1; k++)
			{
				elementQueue[k] = elementQueue[k + 1];
			}
			elementQueueSize--;
			return; // One element can only remove one element from the Q.
					//TODO: Function to inform that element was removed
		}
	}

	if (elementQueueSize == 3)
	{
		return; // Not more than 3 elements at once.
	}

	elementQueue[elementQueueSize] = &e;
	elementQueueSize++;
}

void APlayerCharacter::ReleaseSpellForward()
{
	if (elementQueueSize == 0)
	{
		return;
	}

	TArray<CElement *> in;
	for (int i = 0; i < elementQueueSize; i++)
	{
		in.Add(elementQueue[i]);
	}

	currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(in, false, *this);

	switch (currentSpell->Type)
	{
	case Spelltype::Charged:
		beginCharge();
		break;
	default:
		break;

	}

	elementQueueSize = 0;
	
}

void APlayerCharacter::beginCharge()
{
	// Animations, Particles missing
	GetWorldTimerManager().SetTimer(chargeHandler, this, &APlayerCharacter::endCharge, MaxChargeTime, 0);

}

void APlayerCharacter::endCharge()
{
	float elapsedTime = GetWorldTimerManager().GetTimerElapsed(this->chargeHandler);
	GetWorldTimerManager().ClearTimer(chargeHandler);
	static_cast<AChargeableSpell*>(currentSpell)->SetChargedTime(elapsedTime);
	currentSpell->StartBehavior(*this);
}

void APlayerCharacter::ReleaseSpellSelf()
{

}

void APlayerCharacter::KeyupForward()
{
	if (currentSpell != nullptr)
	{
		switch (currentSpell->Type)
		{
		case Spelltype::Charged:
			endCharge();
			currentSpell = nullptr;
			break;
		default:
			currentSpell->EndBehavior(); 
			currentSpell = nullptr;
		}
	}
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



