// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Spell.h"


// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpell::StartBehavior()
{
}

void ASpell::EndBehavior()
{
}

// May only be called twice!
void ASpell::PushAdditionalElement(CElement& element)
{
	additionalElements[index] = element;
	index++;
}



