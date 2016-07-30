// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

enum Spelltype
{
	Charged = 0,
	Channeled = 1,
	Burst = 2
};

UCLASS()
class PROJECTXYZ_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	

	Spelltype Type;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Advance this if you need.
	virtual void StartBehavior(const APlayerCharacter& player) {};
	virtual void EndBehavior() {};
	
protected:
	// PackedElementQueue additionalElements;
	UPROPERTY()
	TArray<uint8> additionalElements;
};
