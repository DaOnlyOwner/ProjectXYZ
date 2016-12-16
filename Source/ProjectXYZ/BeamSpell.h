// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "BeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API ABeamSpell : public ASpell
{
	GENERATED_BODY()
protected:
		void queryDamage();
		void StartBehaviorLowLevel()
		{
			queryDamage();
		}

		UFUNCTION(BlueprintCallable, Category=NotReadyYet)
			bool calculateBeamHitPoints(TArray<int>& outPoints, AActor* hitActor, float maxReflectionBounces, float maxDistance);

};
