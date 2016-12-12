// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Spell.h"
#include "DamageAble.h"
#include "Tools.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API UTools : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Tools")
	/*
	@param openingAngle - Angle in degrees*/
	static bool OverlapCone( AActor* causer, // Can't pass UObjects as References, only T's and F's; UObjects are passed as Pointers
		TArray<AActor*>& outHitresults, 
		ECollisionChannel channel,  
		float openingAngle,  
		float length,  /*RVO*/
		const TArray<AActor*>& actorsToIgnore,
		bool ignoreCauser,
		bool traceComplex);

	/*Function that calculates the final damage based on the elements int queue and the specific function implemented in damageAbleObject (see IDamageAble)
	@param damageAbleObject - Object that implements IDamageAble; This function calls CalculateDamageForElementID on this object.
	@param elementKeys - The queue basically.
	@param rawDamage - The damage values in the DamageValueTable.
	@return - final damage output to be applied.
	*/
	UFUNCTION(BlueprintCallable, Category="Tools")
	static float CalculateFinalDamage(AActor* damageAbleObject, const TArray<ElementID>& elementKeys, const TArray<int>& rawDamage);
};