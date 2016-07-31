// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "RockSpell.h"
#include "engine.h"


ARockSpell::ARockSpell()
{
	Type = Spelltype::Charged;
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
	RockMesh->SetStaticMesh(meshAsset.Object);
	RootComponent = RockMesh;

	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
}

ARockSpell::~ARockSpell()
{

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


