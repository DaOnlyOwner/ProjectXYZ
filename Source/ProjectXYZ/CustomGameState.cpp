// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"
#include "PlayerCharacter.h"
#include "RockSpell.h"

// I might replace that with a better working solution. Right now its just too ugly
ASpell* ACustomGameState::genSpell(TArray<CElement *>& queue, bool selfcast, const APlayerCharacter& player)
{

	//Replace
        int32 indexQ = queue.IndexOfByPredicate([](CElement *el){
	return el->GetName() == 'Q';});
        if (indexQ != INDEX_NONE)
	{
	        int32 indexF = queue.IndexOfByPredicate([](CElement *el){return el->GetName() == 'F';});
		if (indexF != INDEX_NONE)
		{
			queue.RemoveAtSwap(indexF);
			queue.RemoveAtSwap(indexQ);
			queue.Add(&steam);
		}

		else
		{
	    	        int32 indexR = queue.IndexOfByPredicate([](CElement *el){return el->GetName() == 'R';});
			if (indexR != INDEX_NONE)
			{
				queue.RemoveAtSwap(indexR);
				queue.RemoveAtSwap(indexQ);
				queue.Add(&ice);
			}
		}

	}

	//Sort
	queue.Sort();
	FString lookupstring = selfcast ? "!" : "";
	ASpell* out;
	if (queue[0]->GetName() == 'E')
	{
		lookupstring += 'E'; 
		if (queue.Num() > 1)
		{
			lookupstring += queue[1]->GetName();
		}


		out = static_cast<ASpell*>(GetWorld()->SpawnActor(eDict[lookupstring]));

		if(queue.Num()>2)
		   out->PushAdditionalElement(*queue[2]);
	}

	else
	{
		lookupstring.AppendChar(queue[0]->GetName()); //This takes 2ms somehow lol

		out = static_cast<ASpell*>(GetWorld()->SpawnActor(ARockSpell::StaticClass()));
		for (int i = 0; i < queue.Num(); i++)
		{
			out->PushAdditionalElement(*queue[i]);
		}
	}


	return out;
}

