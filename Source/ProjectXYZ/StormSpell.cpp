// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "StormSpell.h"


AStormSpell::AStormSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StormMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AStormSpell::OnOverlapBegin);
	mesh->Activate(true);
	this->SetReplicates(true);

}

void AStormSpell::BeginPlay()
{
	Super::BeginPlay();

}

void AStormSpell::StartBehavior(const APlayerCharacter & player)
{
	SetActorLocation(player.GetActorLocation());

}

void AStormSpell::EndBehavior()
{
	Destroy();

}

void AStormSpell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "stormspell OVERLAP", true);
	}
}



