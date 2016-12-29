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
	
public:
	ABeamSpell()
	{
		this->PrimaryActorTick.bCanEverTick = true;
	}

protected:
	UFUNCTION(BlueprintCallable, Category = Damage)
		/*Use this if you want to retrieve the points where the beam reflects, ends etc.
		@param hitpoints - Stores the points where the beam should reflect. The first value is the position of the beam, the last position is always the ending position
		@param maxBounces - How often the beam should reflect
		@param maxDistance - The maximal distance the beam can go
		@return - The actor that was hit, if no actor was hit, a nullptr is returned, so you ALWAYS need to check if this actor is valid*/
		AActor* calculateBeamPoints(TArray<FVector>& hitpoints, float maxBounces, float maxDistance);
	
	
	
};
