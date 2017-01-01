// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tools.h"
#include "GameFramework/Actor.h"
#include "Spell.h"
#include "SpraySpell.generated.h"


UCLASS()
class PROJECTXYZ_API ASpraySpell : public ASpell
{
	GENERATED_BODY()

public:
	ASpraySpell()
	{
		PrimaryActorTick.bCanEverTick = true;
	}
protected:

	float interval = 1;
	bool isWaterSpray = false;

	UPROPERTY(EditAnywhere)
		float openingAngle = 30.0f;
	UPROPERTY(EditAnywhere)
		float pushFactor;
	void queryDamage();
	void StartBehaviorLowLevel() override;
	void DamageTick();
	void Tick(float deltaTime) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UParticleSystemComponent* systemComponent;
	TArray<AActor*> cachedHitResults;

};
