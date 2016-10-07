// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "StormUnit.h"


// Sets default values
AStormUnit::AStormUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StormUnitMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AStormUnit::OnOverlapBegin);

	mesh->Activate(true);
	this->SetReplicates(true);

}

// Called when the game starts or when spawned
void AStormUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStormUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AStormUnit::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "stormspell OVERLAP", true);
	}
}