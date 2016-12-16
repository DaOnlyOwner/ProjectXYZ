// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "BeamSpell.h"

void ABeamSpell::queryDamage()
{
	FString contextString(TEXT("Default"));
	UDataTable* damageValues = static_cast<USpellTable*>(database)->DamageTable;
	FDamageTable * row;

	row = damageValues->FindRow<FDamageTable>(FName{ TEXT("Beam") }, contextString, true); // true only for debugging. 

	assignDamageValues(row);
}

bool ABeamSpell::calculateBeamHitPoints(TArray<int>& outPoints, AActor * hitActor, float maxReflectionBounces, float maxDistance)
{
	return false;
}


