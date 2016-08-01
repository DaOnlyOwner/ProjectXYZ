// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "RockSpell.h"

ARockSpell::ARockSpell()
{
	Type = Spelltype::Charged;
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	RootComponent = RockMesh;
	movementComponent = CreateDefaultSubobject<URockMovement>(TEXT("RockMovementComponent"));
	movementComponent->SetUpdatedComponent(RootComponent);
	movementComponent->bIsActive = false;

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
	SetActorLocation(player.GetActorLocation() + player.GetActorForwardVector() * 100,false,(FHitResult*)nullptr,ETeleportType::TeleportPhysics);
	movementComponent->InitializeAndStart(MaxRockDistance, chargedTime, player.GetActorForwardVector(), player.MaxChargeTime);

}

void ARockSpell::EndBehavior()
{
	
}


