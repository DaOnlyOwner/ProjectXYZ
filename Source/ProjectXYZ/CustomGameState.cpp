// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"

// I might replace that with a better working solution. Right now its just too ugly
ASpell * ACustomGameState::genSpell(TArray<uint8> &queue, bool selfcast)
{
	FString string = "GENSPELL: ";
	for (int i = 0; i < queue.Num(); i++)
		string += CElement::GetCElementByID((ElementID)queue[i]).GetLetter();
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);

	ASpell * spell;
	spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict["F"]));
	spell->SetSpellElements(queue);
	return spell;

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

	//Sort
	/*queue.Sort([](const uint8& A, const uint8& B) {
		return A < B;
	});*/

	FString lookupstring = selfcast ? "!" : "";

	/*if (queue[0] == SHIELD_ELEM)
	{
		lookupstring += SHIELD_CHAR; 
		if (queue.Num() > 1)
			lookupstring += CElement::GetCElementByID((ElementID)queue[1]).GetLetter();
	}
	else
	   lookupstring.AppendChar(CElement::GetCElementByID((ElementID)queue[0]).GetLetter());*/

	/*spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));
	
	if(spell)
	   spell->SetSpellElements(queue);*/

	spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));
	return spell;
}

