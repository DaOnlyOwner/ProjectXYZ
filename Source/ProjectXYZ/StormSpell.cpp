// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "StormSpell.h"
#include "StormUnit.h"
#include "SpellSystemConstants.h"


AStormSpell::AStormSpell()
{
	this->SetReplicates(true);


}

void AStormSpell::StartBehaviorLowLevel()
{

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    int angle = originPlayer->GetActorRotation().Yaw;
    FVector playerLoc = originPlayer->GetActorLocation();

	playerLoc.Z = 0; // player location is centered on the body, we want to spawn on the floor
    const FRotator newRot = originPlayer->GetActorRotation();

    if (damageInformation.Elements.Num() > 2)
	{
		angle = angle - STORM_UNIT_GAP * 2;
		for (int i = 0; i < 5; i++)
		{
			Units.Push(static_cast<AActor*>(GetWorld()->SpawnActor(StormUnitBP)));
			Units[i]->SetActorLocation(playerLoc + FVector(STORM_UNIT_DISTANCE_FROM_PLAYER * cos(angle * 3.1415 / 180), STORM_UNIT_DISTANCE_FROM_PLAYER * sin(angle * 3.1415 / 180), 0), false, nullptr, ETeleportType::None);
			Units[i]->SetActorRotation(newRot, ETeleportType::None);
			angle += STORM_UNIT_GAP;
		}
	}
	else
	{
		Units.Push(static_cast<AActor*>(GetWorld()->SpawnActor(StormUnitBP)));
		Units[0]->SetActorLocation(playerLoc + FVector(STORM_UNIT_DISTANCE_FROM_PLAYER * cos(angle * 3.1415 / 180), STORM_UNIT_DISTANCE_FROM_PLAYER * sin(angle * 3.1415 / 180), 0), false, nullptr, ETeleportType::None);
		Units[0]->SetActorRotation(newRot, ETeleportType::None);
	}

	GetWorldTimerManager().SetTimer(timerHandler, this, &AStormSpell::EndBehaviorLowLevel, MAX_STORM_LIFETIME, 0);

}

void AStormSpell::EndBehaviorLowLevel()
{
	for (int i = 0; i < Units.Num(); i++)
	{
		Units[i]->Destroy();
	}
	Destroy();
}

void AStormSpell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "stormspell OVERLAP", true);
	}
}



