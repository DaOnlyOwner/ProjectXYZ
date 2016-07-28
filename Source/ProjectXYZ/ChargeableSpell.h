// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "ChargeableSpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API AChargeableSpell : public ASpell
{
	GENERATED_BODY()
	

public:
	FORCEINLINE void SetChargedTime(float time)
	{
		chargedTime = time;
	}

protected:
	float chargedTime;
	
	
};
