// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"

// I might replace that with a better working solution. Right now its just too ugly
ASpell * ACustomGameState::genSpell(TArray<ElementID> &queue, bool selfcast)
{
	/*FString string = "GENSPELL: ";
	for (int i = 0; i < queue.Num(); i++)
		string += CElement::GetCElementByID((ElementID)queue[i]).GetLetter();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);

	ASpell * spell;
	FString lookupstring = selfcast ? "!" : "";

	//Replace
	int32 waterIndex = queue.Find(WATER_ELEM);
	if (waterIndex != INDEX_NONE)
	{
		int32 fireIndex = queue.Find(FIRE_ELEM);
		if (fireIndex != INDEX_NONE)
		{
			queue.RemoveAtSwap(fireIndex);
			queue.RemoveAtSwap(waterIndex);
			queue.Add(STEAM_ELEM);
		}

		else
		{
			int32 coldIndex = queue.Find(COLD_ELEM);
			if (coldIndex != INDEX_NONE)
			{
				queue.RemoveAtSwap(coldIndex);
				queue.RemoveAtSwap(waterIndex);
				queue.Add(ICE_ELEM);
			}
		}
	}

	queue.Sort();

	if (queue[0] == SHIELD_ELEM)
	{
		lookupstring += SHIELD_CHAR; 
		if (queue.Num() > 1)
            lookupstring += CElement::GetCElementByID(queue[1]).GetLetter();
	}
	else
       lookupstring.AppendChar(CElement::GetCElementByID(queue[0]).GetLetter());

	spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));


	if(spell)
       spell->SetInitialValues(queue,nullptr);

	return spell;*/
	return nullptr;
}

