// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "CustomGameState.h"

// I might replace that with a better working solution. Right now its just too ugly
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
	if (queue[0].getName() == 'E')
	{
		lookupstring += 'E'; 
		if (queue.Num() > 1)
		{
			lookupstring += queue[1].getName();
		}
		/*ASpell* out = static_cast<ASpell*>(GetWorld()->SpawnActor(*eDict[lookupstring], &location));
		for (int i = 1; i < queue.Num(); i++)
		{
			out->PushAdditionalElement(queue[i]);
		}*/
	}

	else
	{
		lookupstring += queue[0].getName();
		/*ASpell* out =  static_cast<ASpell*>(GetWorld()->SpawnActor(*normalDict[lookupstring], &location));
		for (int i = 0; i < queue.Num(); i++)
		{
			out->PushAdditionalElement(queue[i]);
		}*/
	}

	UE_LOG(LogTemp, Warning, TEXT("Final output for search: %s"), *lookupstring);
	return nullptr;
	//return out;
}

