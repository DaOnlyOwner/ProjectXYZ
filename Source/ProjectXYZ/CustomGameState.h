// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Spell.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameState.h"
#include "CustomGameState.generated.h"


struct SpellToCaster
{
	const UClass* Spellclass; // The referenced object will remain until the end of the game. 
	CElement additionalElements[2];
	const int index = 0;
};


/**
 * 
 */
UCLASS()
class PROJECTXYZ_API ACustomGameState : public AGameState
{
	GENERATED_BODY()

public:
	//TODO: Edict 
	void BeginPlay() override
	{
		for (int i = 0; i < KeysNormal.Num(); i++)
		{
			spellClassDict.Add(KeysNormal[i], MoveTemp(ValuesNormal[i])); // I am not that familiar with move semantics but I believe that's the way it's done.
		}

		KeysNormal.Empty();
		ValuesNormal.Empty();

	};

	ASpell * genSpell(TArray<uint8>& queue, bool selfcast, const APlayerCharacter & player);

	UPROPERTY(EditAnywhere)
		TArray<FString> KeysNormal;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<ASpell>> ValuesNormal;

private:
	TMap<FString, TSubclassOf<ASpell>> spellClassDict;

};
