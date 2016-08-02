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
	FString string = "";
	string += CElement::GetCElementByName(ElemQueue.element1).GetLetter();
	string += CElement::GetCElementByName(ElemQueue.element2).GetLetter();
	string += CElement::GetCElementByName(ElemQueue.element3).GetLetter();

	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Red, string,true, FVector2D{ 5,5 });
	moveCamera(DeltaTime);
	
}

void APlayerCharacter::AddElemToQueue_Implementation(int element_id)
{
	/* the elemQueue can only be modified by the server*/
	UE_LOG(LogTemp, Warning, TEXT("server func"));

	/* if element1 is null the queue is empty */
	if (ElemQueue.element1 == NULL_ELEM)
	{
		ElemQueue.element1 = element_id;
	}
	else if (ElemQueue.element2 == NULL_ELEM)
	{
		ElemQueue.element2 = element_id;
	}
	else if (ElemQueue.element3 == NULL_ELEM)
	{
		ElemQueue.element3 = element_id;
	}
	else
	{
		return; // Queue is full;
	}
	return; // the new elemQueue (calculated here, on the server) is replicated to clients.
}
bool APlayerCharacter::AddElemToQueue_Validate(int element_id)
{
	return true;
}

void APlayerCharacter::RemoveElemFromQueue_Implementation(int element_id)
{
	/* the elemQueue can only be modified by the server*/
	UE_LOG(LogTemp, Warning, TEXT("server func"));

	if (element_id == ElemQueue.element3)
	{
		ElemQueue.element3 = NULL_ELEM;
	}
	else if(element_id == ElemQueue.element2)
	{
		ElemQueue.element2 = ElemQueue.element3; // shift left
	}
	else if (element_id == ElemQueue.element1)
	{
		ElemQueue.element1 = ElemQueue.element2; // shift left
		ElemQueue.element2 = ElemQueue.element3; // shift left
	}
	else
	{
		return; // no such element
	}
}
bool APlayerCharacter::RemoveElemFromQueue_Validate(int element_id)
{
	return true;
}
void APlayerCharacter::TryAddElementToQueue(CElement & NewElement)
{
	/* client-side function */

	CElement e1 = CElement::GetCElementByName(ElemQueue.element1);
	CElement e2 = CElement::GetCElementByName(ElemQueue.element2);
	CElement e3 = CElement::GetCElementByName(ElemQueue.element3);

	/* ask the server to add/remove an element*/
	if (NewElement.Cancels(e1)) RemoveElemFromQueue(e1.GetName());
	else if (NewElement.Cancels(e2)) RemoveElemFromQueue(e2.GetName());
	else if (NewElement.Cancels(e3)) RemoveElemFromQueue(e3.GetName());
	else if (ElemQueue.element3 == NULL_ELEM )
	{
		AddElemToQueue(NewElement.GetName());
	}
	else
	{
		return; /* queue is full */
	}

}

void APlayerCharacter::AddElementToQueue(CElement &e)
{

	 /* this is debug */

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



