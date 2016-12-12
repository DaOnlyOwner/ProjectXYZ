// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "DamageTable.h"
#include "SpellTable.generated.h"

class ASpell;

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API USpellTable : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FString, TSubclassOf<ASpell>> Spells;
	
	UPROPERTY(EditAnywhere)
		UDataTable* DamageTable;

};
