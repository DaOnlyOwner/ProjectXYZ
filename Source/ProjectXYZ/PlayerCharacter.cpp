// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->AttachTo(RootComponent);
	stack = new CElement[3];
}

APlayerCharacter::~APlayerCharacter()
{
	delete[] stack;
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
	for (int i = 0; i < index; i++)
	{
		string += stack[i].getName();
	}

	GEngine->AddOnScreenDebugMessage(-1, 0.007f, FColor::Red, string,true, FVector2D{ 5,5 });


	if (HasAuthority()) moveCamera(DeltaTime);
	
}



void APlayerCharacter::Push(CElement e)
{


	for (int i = 0; i < index; i++)
	{
		char cancelling1 = e.getCancelledBy();
		char cancelling2 = e.getCancelledBy2();

		if (stack[i] == cancelling1 || stack[i] == cancelling2)
		{
			// Remove stack[i] and resize.
			for (int k = i; k < index - 1; k++)
			{
				stack[k] = stack[k + 1];
			}
			index--;
			return; // One element can only remove one element from the Q.
					//TODO: Function to inform that element was removed
		}
	}

	if (index == 3)
	{
		return; // Not more than 3 elements at once.
	}

	stack[index] = e;
	index++;
}


void APlayerCharacter::ReleaseSpellForward()
{
	if (index == 0)
	{
		return;
	}

	TArray<CElement> in;
	for (int i = 0; i < index; i++)
	{
		in.Add(stack[i]);
	}

	ASpell* spell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(in, false, GetActorLocation());
	index = 0;
	
}

void APlayerCharacter::ReleaseSpellSelf()
{

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



