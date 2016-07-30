// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "CustomGameState.h"
#include "Spell.h"
#include "ChargeableSpell.h"


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

	if (HasAuthority())
	{
		startOffset = camera->GetRelativeTransform().GetLocation();
		camera->DetachFromParent(true, true);
	}
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FString string;
	for (int i = 0; i < elementQueue.Num(); i++)
	{
	    string += CElement::GetElementByID((ElementID)elementQueue[i]).GetName();
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Red, string,true, FVector2D{ 5,5 });


	if (HasAuthority()) moveCamera(DeltaTime);
	
}



void APlayerCharacter::AddElementToQueue(CElement &e)
{
   if(elementQueue.RemoveSingle(e.GetCancelledBy()) == 0 &&
      elementQueue.RemoveSingle(e.GetCancelledBy2()) == 0 &&
      elementQueue.Num() < 3)
      elementQueue.Push(e.GetID());
}

void APlayerCharacter::ReleaseSpellForward()
{
        if (elementQueue.Num() == 0)
	{
	    //melee here?
		return;
	}

	currentSpell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(elementQueue, false, *this);

	switch (currentSpell->Type)
	{
	case Spelltype::Charged:
		beginCharge();
		break;
	default:
		break;

	}

	elementQueue.Empty();
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



