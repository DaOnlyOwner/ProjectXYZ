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

ASpell ASpellfactory::genSpell(TArray<Element> queue)
{
	bool isF;
	bool isQ;
	bool isR;

	int index = queue.IndexOfByKey<char>('Q');
	if (index != INDEX_NONE)
	{
		
	}

	//Sort
	queue.Sort();


}

