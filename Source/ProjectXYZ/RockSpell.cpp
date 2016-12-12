// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "RockSpell.h"

ARockSpell::ARockSpell()
{
	RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RockMesh"));
	RockMesh->OnComponentBeginOverlap.AddDynamic(this, &ARockSpell::OnOverlapBegin);
	RockMesh->Activate(true);

	movementComponent = CreateDefaultSubobject<URockMovement>(TEXT("RockMovementComponent"));
	movementComponent->SetUpdatedComponent(RootComponent);
	movementComponent->bIsActive = false;
}

ARockSpell::~ARockSpell()
{

}

void ARockSpell::StartBehaviorLowLevel()
{
    SetActorLocation(originPlayer->GetActorLocation() + originPlayer->GetActorForwardVector() * 100,false,(FHitResult*)nullptr,ETeleportType::TeleportPhysics);
    movementComponent->InitializeAndStart(MaxRockDistance, chargedTime, originPlayer->GetActorForwardVector());
}

void ARockSpell::EndBehaviorLowLevel()
{
	
}
void ARockSpell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "OVERLAP", true);
}

