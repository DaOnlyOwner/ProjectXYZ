// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"


ASpell* ACustomGameState::genSpell(TArray<CElement>& queue, bool selfcast, const FVector& location)
{

	//Replace
	int32 indexQ = queue.IndexOfByKey<char>('Q');
	if (indexQ != INDEX_NONE)
	{
		int32 indexF = queue.IndexOfByKey<char>('F');
		if (indexF != INDEX_NONE)
		{
			queue.RemoveAtSwap(indexF);
			queue.RemoveAtSwap(indexQ);
			queue.Add(CElement::getSteam());
		}

		else
		{
			int32 indexR = queue.IndexOfByKey('R');
			if (indexR != INDEX_NONE)
			{
				queue.RemoveAtSwap(indexR);
				queue.RemoveAtSwap(indexQ);
				queue.Add(CElement::getIce());
			}
		}

	}

	//Sort
	queue.Sort();
	FString lookupstring = selfcast ? "!" : "";
	int count = queue.Num();
	
	for (int i = 0; i < count; i++)
	{
		lookupstring += queue[i].getName();
	}

	if (queue.FindByKey<char>('E') != nullptr)
	{
		return static_cast<ASpell*>(GetWorld()->SpawnActor(*eDict[lookupstring], &location));
	}

	return static_cast<ASpell*>(GetWorld()->SpawnActor(*normalDict[lookupstring], &location));


}

