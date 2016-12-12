// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "SpellTable.h"
#include "Spell.generated.h"

UENUM(BlueprintType)
enum class SpellType : uint8
{
    Spray = 0,
    SteamSpray = 1,
    Projectile = 2,
    Rock = 3,
    Beam = 4,
    Lightning = 5,
    Mine = 6,
    Storm = 7,
    Wall = 8,
    IceWall = 9,
    Aoe = 10,
    Quake = 11
};

USTRUCT(BlueprintType)
struct FDamageInformation
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
    TWeakObjectPtr<APlayerCharacter> Causer;
	UPROPERTY(BlueprintReadWrite)
    TArray<ElementID> Elements;
	UPROPERTY(BlueprintReadOnly)
    SpellType Type;
	UPROPERTY(BlueprintReadWrite)
    float Charge = 1;
	UPROPERTY(BlueprintReadOnly)
    TArray<int> RawDamage;
};

UCLASS()
class PROJECTXYZ_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
    void SetInitialValues(const TArray<ElementID> &queue, const APlayerCharacter* player_)
    {
        damageInformation.Elements = queue;
        damageInformation.Causer = player_;
        this->originPlayer = player_;
		this->AttachToActor(originPlayer.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false)); // Later attach it to the hand.
	} 

	// Advance this if you need.
	virtual void StartBehaviorLowLevel() {}
	virtual void EndBehaviorLowLevel() {
		if (originPlayer.IsValid()) originPlayer->DisposeSpellRef();
		Destroy();
	}

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UDataAsset* database;
	UPROPERTY(BlueprintReadWrite)
    FDamageInformation damageInformation;
	UPROPERTY(BlueprintReadWrite)
    TWeakObjectPtr<APlayerCharacter> originPlayer;
	
	void assignDamageValues(FDamageTable* row);
};
