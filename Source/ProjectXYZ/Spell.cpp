// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Spell.h"

void ASpell::assignDamageValues(FDamageTable * row)
{
	for (int i = 0; i < damageInformation.Elements.Num(); i++)
	{
		ElementID id = damageInformation.Elements[i];
		switch (id)
		{
		case ElementID::Earth:
			damageInformation.RawDamage.Add(row->D);
			break;
		case ElementID::Lightning:
			damageInformation.RawDamage.Add(row->A);
			break;
		case ElementID::Ice:
			damageInformation.RawDamage.Add(row->I);
			break;
		case ElementID::Death:
			damageInformation.RawDamage.Add(row->S);
			break;
		case ElementID::Life:
			damageInformation.RawDamage.Add(row->W);
			break;
		case ElementID::Steam:
			damageInformation.RawDamage.Add(row->T);
			break;
		case ElementID::Cold:
			damageInformation.RawDamage.Add(row->R);
			break;
		case ElementID::Fire:
			damageInformation.RawDamage.Add(row->F);
			break;
		case ElementID::Water:
			damageInformation.RawDamage.Add(row->Q);
			break;
		default:
			damageInformation.RawDamage.Add(0);
			break;
		}
	}
}

