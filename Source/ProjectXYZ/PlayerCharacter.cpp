// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APlayerCharacter::ReleaseSpellForward()
{
	TArray<CElement> in;
	for (int i = 0; i < index; i++)
	{
		in.Add(stack[i]);
	}

	ASpell* spell = GetWorld()->GetGameState<ACustomGameState>()->genSpell(in, false, GetActorLocation());

	
}

void APlayerCharacter::ReleaseSpellSelf()
{
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


