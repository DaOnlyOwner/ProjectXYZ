// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "LightningSpell.h"


// Sets default values
ALightningSpell::ALightningSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // We don't need the Tick function here.
	boxShape = FCollisionShape::MakeBox(FVector(LIGHTNING_LENGTH/2.0f, LIGHTNING_LENGTH / 2.0f, LIGHTNING_LENGTH / 2.0f));
}

// Called when the game starts or when spawned
void ALightningSpell::BeginPlay()
{
	Super::BeginPlay();
}

void ALightningSpell::StartBehavior(APlayerCharacter& playerCharacter)
{
	TArray<FOverlapResult> hitresults;
	
	FVector center = playerCharacter.GetActorLocation() + playerCharacter.GetActorForwardVector() * 250.0f;
	FQuat rot{ playerCharacter.GetActorRotation().Add(0,90,0) };
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor(&playerCharacter);
	collisionQueryParams.TraceTag = "DebugTrace";
	collisionQueryParams.bTraceComplex = false; // Trace only against spheres, capsules, boxes, cones etc. (No meshes)
	
	GetWorld()->DebugDrawTraceTag = "DebugTrace";
	
	bool hit = GetWorld()->OverlapMultiByChannel(hitresults, center, rot, ECollisionChannel::ECC_GameTraceChannel1, boxShape, collisionQueryParams);  // The naming is bad. In the collision settings the Profile Response has to be Blocking Hit not Overlap...

	if (!hit)
	{
		// Cast into the wild;
		Destroy();
	}
	
	lightningChain.Add( static_cast<AActor*>(&playerCharacter) );
	AActor* bestChoice = nullptr;

	float lengthBetweenThisAndBestChoice = LIGHTNING_LENGTH * LIGHTNING_LENGTH + 100; // Make the initial value worst; Remember squared!
	for (int i = 0; i < hitresults.Num(); i++)
	{
		FOverlapResult& result = hitresults[i];
		AActor* actor = result.GetActor();
		FVector dirToHitresult = actor->GetActorLocation() - playerCharacter.GetActorLocation();
		dirToHitresult.Normalize();
		float cosalpha = FVector::DotProduct( dirToHitresult , playerCharacter.GetActorForwardVector());
		float alpha = FMath::Acos(cosalpha);
		debugScreen(FString::SanitizeFloat(alpha * (180.0f / PI)), 5.0f);
		if (alpha < LIGHTNING_OPENING_ANGLE) 
		{
			float lengthHitresult = (playerCharacter.GetActorLocation() - actor->GetActorLocation()).SizeSquared();
			if (lengthHitresult < lengthBetweenThisAndBestChoice)
			{
				bestChoice = actor;
				lengthBetweenThisAndBestChoice = lengthHitresult;
			}
		}

	}

	if (bestChoice != nullptr)
	{
		lightningChain.Add(bestChoice);
		bounce(bestChoice, 1); // Lightning Chain was filled up.
		GetWorldTimerManager().SetTimer(lightningHandle, this, &ALightningSpell::triggerNextLightningTick, LIGHTNING_TIME_BETWEEN_TICKS, true);
	}
}

void ALightningSpell::triggerNextLightningTick(void)
{
	if (tickAmount == LIGHTNING_AMOUNT_TICKS)
	{
		// Do some final computations or whatever.
		GetWorldTimerManager().ClearTimer(lightningHandle);
		this->Destroy();
	}

	for (int i = 1; i < lightningChain.Num(); i++)
	{
		AActor* actor = lightningChain[i];
		if (actor == nullptr || actor->IsPendingKill())
		{
			// Actor is dead
			// Just go ahead and take the next one
			debugScreen("Actor is dead; Lightning stopped", 10.0f);
			continue;
		}

		DrawDebugLine(GetWorld(), lightningChain[i-1]->GetActorLocation(), lightningChain[i]->GetActorLocation(), FColor::Black,true,5.0f,(uint8)'\000',5.0f);
		//actor->AddActorLocalTransform(FTransform(FVector(0, 0, 500)));
	}

	tickAmount++;
}

void ALightningSpell::bounce(AActor* actor, int bounce)
{
	if (bounce == LIGHTNING_BOUNCES) return;
	TArray<FOverlapResult> hitresults;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActors(lightningChain);
	queryParams.bTraceComplex = false;
	queryParams.TraceTag = "DebugTrace";
	GetWorld()->DebugDrawTraceTag = "DebugTrace";

	bool hit = GetWorld()->OverlapMultiByChannel(hitresults, actor->GetActorLocation(), FQuat(actor->GetActorRotation()), ECollisionChannel::ECC_GameTraceChannel1, boxShape, queryParams);
	if (!hit) return;
	AActor* bestChoice = hitresults[0].GetActor();
	float distanceToBestChoice = bestChoice->GetSquaredDistanceTo(actor); // Just found out about this method w.w

	for (int i = 1; i < hitresults.Num(); i++)
	{
		AActor* potentiallyBestChoice = hitresults[i].GetActor();
		if (potentiallyBestChoice->GetSquaredDistanceTo(actor) < distanceToBestChoice)
		{
			bestChoice = potentiallyBestChoice;
		}
	}

	lightningChain.Add(bestChoice);
	this->bounce(bestChoice, ++bounce);
}

// Called every frame
void ALightningSpell::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}
