// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Spell.h"
#include "MineUnit.h"
#include "MineSpell.generated.h"

UCLASS()
class PROJECTXYZ_API AMineSpell : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineSpell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void EndBehaviorLowLevel() override;
    void StartBehaviorLowLevel() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> MineUnitBP;

	TArray<AActor*> Units;
	
	void SpawnNewUnit();

	FTimerHandle timerHandler;

	int FrontAngle;
	FVector playerLoc;
};
