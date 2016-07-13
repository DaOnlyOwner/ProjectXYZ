// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Core.h"
#include "Spell.h"
#include "GameFramework/GameState.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API ACustomGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpell* ACustomGameState::genSpell(TArray<CElement>& queue, bool selfcast, const FVector& location);
	
private:
	TMap<FString, TSubclassOf<ASpell>> eDict;
	TMap<FString, TSubclassOf<ASpell>> normalDict;

};
