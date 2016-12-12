// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Spell.h"
#include "DamageAble.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UDamageAble : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class PROJECTXYZ_API IDamageAble
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/*Applies damage to this object
	@param damageInformation - the additional damageInformation about elemetns, raw damage values etc.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Damage)
	bool ReceiveDamage(const FDamageInformation& damageInformation);

	/*Pushes this object
	@param - The specified direction (doesn't have to be a normalized vector)
	@return - dummy value (see Interface docs)*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Damage)
	bool Push(const FVector& direction);

	/*Knocks this object down
	@return - dummy value (see Interface docs)*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Damage)
	bool KnockDown();


	/*Shocks this object
	@return - dummy value; see Interface docs*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Damage)
	bool Shock();	

	/*Called by CalculateFinalDamage. Calculates final damage of this particular element for the given spell. (See Tools/CalculateFinalDamage)
	@param id - The Id of the element
	@param count - The amount of occurences in the queue
	@param rawDamage - the raw damage value of this ElementID;
	@return The calculated damage value.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Damage)
		float CalculateDamageForElementID(ElementID id, int count, int rawDamage);
};
