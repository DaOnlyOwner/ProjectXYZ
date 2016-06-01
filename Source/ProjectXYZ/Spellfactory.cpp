// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Spellfactory.h"

// Sets default values
ASpellfactory::ASpellfactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpellfactory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpellfactory::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

ASpell* ASpellfactory::genSpell(TArray<CElement>& queue, char selfcast, const FVector& location) 
{

	//Replace
	int32 indexQ = queue.IndexOfByKey<char>('Q');
	if (indexQ != INDEX_NONE)
	{
		int32 indexF = queue.IndexOfByKey<char>('F');
		if(indexF!=INDEX_NONE)
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
	FString lookupstring;
	lookupstring.AppendChar(selfcast);
	int count = queue.Num();

	for (int i = 0; i < count;i++ )
	{
		lookupstring += queue[i].getName();
	}
	
		
	if (queue.FindByKey<char>('E') != nullptr)
	{
		
		return static_cast<ASpell*>(GetWorld()->SpawnActor(*eDict[lookupstring], &location));

	}

	return static_cast<ASpell*>(GetWorld()->SpawnActor(*normalDict[lookupstring], &location));
	

}

