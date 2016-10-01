// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "StormSpell.h"
#include "StormUnit.h"


AStormSpell::AStormSpell()
{
	this->SetReplicates(true);


}

void AStormSpell::BeginPlay()
{
	Super::BeginPlay();

}

void AStormSpell::StartBehavior(const APlayerCharacter & player)
{
	//SetActorLocation(player.GetActorLocation() + FVector(250.0f, 0.0f, 0.0f));
	//SetActorRotation(player.GetActorRotation());
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FString string = FString::SanitizeFloat(player.GetActorRotation().Roll);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);

	 string = FString::SanitizeFloat(player.GetActorRotation().Pitch);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);

	 string = FString::SanitizeFloat(player.GetActorRotation().Yaw);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.0f, FColor::Red, string, true);


	int angle = player.GetActorRotation().Yaw;
	FVector playerLoc = player.GetActorLocation();

	playerLoc.Z = 0; // player location is centered on the body, we want to spawn on the floor
	const FRotator newRot = player.GetActorRotation();

	angle = angle - 20 - 20;
	for (int i = 0; i < 5; i++)
	{
		Units.Push(static_cast<AActor*>(GetWorld()->SpawnActor(StormUnitBP)));
		Units[i]->SetActorLocation(playerLoc + FVector(250 * cos(angle * 3.1415 / 180), 250 * sin(angle * 3.1415 / 180), 0), false, nullptr, ETeleportType::None);
		Units[i]->SetActorRotation(newRot, ETeleportType::None);
		angle += 20;
	}

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



