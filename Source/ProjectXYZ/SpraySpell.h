// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spell.h"
#include "SpraySpell.generated.h"


UCLASS()
class PROJECTXYZ_API ASpraySpell : public ASpell
{
	GENERATED_BODY()

protected:
	void queryDamage();
	void StartBehaviorLowLevel()
	{
		queryDamage();
	}
};
