// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "CustomGameState.h"
#include "Spell.h"
#include "ChargeableSpell.h"
#include "Element.h"
#include "UnrealNetwork.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);
	ElemQueue.Init(NULL_ELEM, 3);
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
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString string = "";
	string += CElement::GetCElementByName(ElemQueue[0]).GetLetter();
	string += CElement::GetCElementByName(ElemQueue[1]).GetLetter();
	string += CElement::GetCElementByName(ElemQueue[2]).GetLetter();

	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Red, string, true, FVector2D{ 5,5 });
	moveCamera(DeltaTime);

}

void APlayerCharacter::AddElementToQueue(CElement & NewElement)
{
	int element_id = NewElement.GetName();

	for (int i = 0; i < elementQueueSize; i++)
	{
		CElement inQueue = CElement::GetCElementByName(ElemQueue[i]);
		if (NewElement.Cancels(inQueue))
		{
			ElemQueue.RemoveSingle(ElemQueue[i]);
			ElemQueue.Add(NULL_ELEM);
			elementQueueSize--;
			return;
		}
	}
	if (elementQueueSize == 3)
	{
		return; // Not more than 3 elements at once.
	}

	ElemQueue[elementQueueSize] = element_id;
	elementQueueSize++;
}
void APlayerCharacter::onElemQueueChange()
{
	UE_LOG(LogTemp, Warning, TEXT("replicated elemQueue changed"));
	return;
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



