// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Element.h"
#include "Core.h"
#include "GameFramework/Actor.h"
#include "Spellfactory.generated.h"


UCLASS()
class PROJECTXYZ_API ASpellfactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellfactory();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	TMap<FString, ASpell> normalDict;
	TMap<FString, ASpell> eSpellDict; 
	ASpell genSpell(FString);
};
