// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"

int32 elementIndex(TArray<CElement *>& queue, char el)
{
   return queue.IndexOfByPredicate([=](CElement *el2){
	 return el2->GetName() == el;
     });
}

// I might replace that with a better working solution. Right now its just too ugly
ASpell* ACustomGameState::genSpell(TArray<CElement *>& queue, bool selfcast, const APlayerCharacter& player)
{

	//Replace
        int32 waterIndex = elementIndex(queue, WATER_CHAR);
        if (waterIndex != INDEX_NONE)
	{
	        int32 fireIndex = elementIndex(queue, FIRE_CHAR);
		if (fireIndex != INDEX_NONE)
		{
			queue.RemoveAtSwap(fireIndex);
			queue.RemoveAtSwap(waterIndex);
			queue.Add(&steam);
		}

		else
		{
		        int32 coldIndex = elementIndex(queue, COLD_CHAR);
			if (coldIndex != INDEX_NONE)
			{
				queue.RemoveAtSwap(coldIndex);
				queue.RemoveAtSwap(waterIndex);
				queue.Add(&ice);
			}
		}
	}

	//Sort
	queue.Sort();
	FString lookupstring = selfcast ? "!" : "";
	ASpell* spell;

	if (queue[0]->GetName() == SHIELD_CHAR)
	{
		lookupstring += SHIELD_CHAR; 
		if (queue.Num() > 1)
		   lookupstring += queue[1]->GetName();
	}

	else
	{
		lookupstring.AppendChar(queue[0]->GetName()); //This takes 2ms somehow lol
		spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));
	}

	spell = static_cast<ASpell*>(GetWorld()->SpawnActor(spellClassDict[lookupstring]));
	
	if(spell)
	   spell->SetSpellElements(queue);

	return spell;
}

