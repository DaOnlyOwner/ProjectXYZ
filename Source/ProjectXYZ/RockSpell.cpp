// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "RockSpell.h"


ARockSpell::ARockSpell()
{
	Type = Spelltype::Charged;
	// Can we create the mesh here, when the size is still unknown?
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	RootComponent = RockMesh;

	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
}

ARockSpell::~ARockSpell()
{

}

void ARockSpell::init(int size, ElementQueue add)
{
   additionalElements = add;
   rocksize = size;
}

void ARockSpell::StartBehavior(const APlayerCharacter& player)
{
	this->SetActorHiddenInGame(false);
	this->SetActorEnableCollision(true);

	RockMesh->Activate(true);
	RockMesh->SetSimulatePhysics(true);
	SetActorLocation(player.GetActorLocation() + player.GetActorForwardVector() * 100,false,(FHitResult*)nullptr,ETeleportType::TeleportPhysics);
	RockMesh->AddImpulse(player.GetActorForwardVector() * chargedTime*chargedTime * 100, NAME_None, true);
}

void ARockSpell::EndBehavior()
{
	
}


