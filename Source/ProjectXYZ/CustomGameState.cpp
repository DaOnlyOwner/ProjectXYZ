// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"

// I might replace that with a better working solution. Right now its just too ugly
ASpell* ACustomGameState::genSpell(TArray<uint8>& queue, bool selfcast, const APlayerCharacter& player)
{

	//Replace
        int32 waterIndex = queue.Find(WATER_CHAR);
        if (waterIndex != INDEX_NONE)
	{
	        int32 fireIndex = queue.Find(FIRE_CHAR);
		if (fireIndex != INDEX_NONE)
		{
			queue.RemoveAtSwap(fireIndex);
			queue.RemoveAtSwap(waterIndex);
			queue.Add(STEAM_ELEM);
		}

		else
		{
			int32 coldIndex = queue.Find(COLD_CHAR);
			if (coldIndex != INDEX_NONE)
			{
				queue.RemoveAtSwap(coldIndex);
				queue.RemoveAtSwap(waterIndex);
				queue.Add(ICE_ELEM);
			}
		}
	}

	//Sort
	queue.Sort();
	FString lookupstring = selfcast ? "!" : "";
	ASpell* spell;

	if (queue[0] == SHIELD_ELEM)
	{
		lookupstring += SHIELD_CHAR; 
		if (queue.Num() > 1)
			lookupstring += CElement::GetCElementByID((ElementID)queue[1]).GetLetter();
	}

	else
	   lookupstring.AppendChar(CElement::GetCElementByID((ElementID)queue[0]).GetLetter());

	spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));
	
	if(spell)
	   spell->SetSpellElements(queue);

	return spell;
}

