// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacter.h"
#include "MineUnit.h"
#include "Spell.h"


// Sets default values
AMineUnit::AMineUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineUnitMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AMineUnit::OnOverlapBegin);
	mesh->OnComponentEndOverlap.AddDynamic(this, &AMineUnit::OnOverlapEnd);

	mesh->Activate(true);
	this->SetReplicates(true);
}

// Called when the game starts or when spawned
void AMineUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMineUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void AMineUnit::EndBehaviorLowLevel()
{
	Destroy();
}
void AMineUnit::Explode()
{
	// temporary
	SetActorRelativeScale3D(FVector(5.0f, 5.0f, 1.0f));
	GetWorldTimerManager().SetTimer(timerHandler, this, &AMineUnit::EndBehaviorLowLevel, 0.2f, 0);
}

void AMineUnit::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "mine triggered", true);
		Triggered = true;
	}
	else if (OtherActor->IsA(ASpell::StaticClass()) && OtherActor != this)
	{
		GetWorldTimerManager().SetTimer(timerHandler, this, &AMineUnit::Explode, 0.1f, 0);
	}
}

void AMineUnit::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		if (Triggered)
		{
			Explode();
		}
		
	}
}