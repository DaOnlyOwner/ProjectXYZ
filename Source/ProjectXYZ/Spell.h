// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

enum Spelltype
{
	None = 0,
	Charged = 1,
	Channeled = 2,
	Burst = 3
};

UCLASS()
class PROJECTXYZ_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE void SetSpellElements(const TArray<uint8> &queue) {
	   spellElements = queue;
	} 

	// Advance this if you need.
	virtual void StartBehavior(APlayerCharacter& player) {};
	virtual void EndBehavior() {};
	
protected:
	TArray<uint8> spellElements;
};
