// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "MineSpell.h"
#include "MineUnit.h"
#include "SpellSystemConstants.h"


// Sets default values
AMineSpell::AMineSpell()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMineSpell::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMineSpell::StartBehavior(APlayerCharacter & player)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FrontAngle = player.GetActorRotation().Yaw;
	playerLoc = player.GetActorLocation();

	playerLoc.Z = 1; // player location is centered on the body, we want to spawn on the floor
	const FRotator newRot = player.GetActorRotation();

	SpawnNewUnit();
	
}
void AMineSpell::SpawnNewUnit()
{
	int angleShift;

	angleShift = FrontAngle - 35 + 35 * Units.Num();

	Units.Push(static_cast<AActor*>(GetWorld()->SpawnActor(MineUnitBP)));
	Units[Units.Num() - 1]->SetActorLocation( playerLoc + FVector(STORM_UNIT_DISTANCE_FROM_PLAYER * cos((angleShift) * 3.1415f / 180), STORM_UNIT_DISTANCE_FROM_PLAYER * sin((angleShift) * 3.1415f / 180), 0), false, nullptr, ETeleportType::None);
	Units[Units.Num() - 1]->SetActorRotation(FRotator(0.0f), ETeleportType::None);
	if (Units.Num() < 3)
	{
		GetWorldTimerManager().SetTimer(timerHandler, this, &AMineSpell::SpawnNewUnit, 0.05f, 0);
	}
}
void AMineSpell::EndBehavior()
{
	for (int i = 0; i < Units.Num(); i++)
	{
		Units[i]->Destroy();
	}
	Destroy();
}

// Called every frame
void AMineSpell::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

