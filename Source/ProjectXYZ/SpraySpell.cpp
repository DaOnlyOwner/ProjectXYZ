// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "SpraySpell.h"

void ASpraySpell::queryDamage()
{
	FString contextString(TEXT("Default"));
    UDataTable* damageValues = static_cast<USpellTable*>(database)->DamageTable;
	FDamageTable * row;

    if(damageInformation.Elements.Contains(steam.GetID()))
    {
		row = damageValues->FindRow<FDamageTable>(FName{ TEXT("SteamSpray") },contextString,true); // true only for debugging. 
    }

    else
    {
		row = damageValues->FindRow<FDamageTable>(FName{ TEXT("Spray") }, contextString, true);
    }
	assignDamageValues(row);

}


