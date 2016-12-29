// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "BeamSpell.h"


AActor* ABeamSpell::calculateBeamPoints(TArray<FVector>& hitpoints, float maxBounces, float maxDistance)
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(originPlayer.Get());
	params.bTraceAsyncScene = false;
	GetWorld()->DebugDrawTraceTag = "DebugTraceBeam";
	//params.TraceTag = "DebugTraceBeam";
	FHitResult out;
	FVector reflectionVector{ GetActorForwardVector() };
	hitpoints.Add(originPlayer->GetActorLocation());
	for (int i = 0; i <= maxBounces; i++) // "<=" is intentional!  
	{
		// We found something!!
		if (GetWorld()->LineTraceSingleByChannel(out, hitpoints[i], reflectionVector * maxDistance + hitpoints[i], ECollisionChannel::DamageAble, params) && maxDistance > 0)
		{
			// It is a shield, reflect beam!
			if (out.Actor->ActorHasTag(TEXT("Shield")))
			{
				hitpoints.Add(out.ImpactPoint);
				reflectionVector = reflectionVector - 2 * FVector::DotProduct(reflectionVector, out.ImpactNormal) * out.ImpactNormal;
				maxDistance -= out.Distance;
				params = FCollisionQueryParams{};
				params.AddIgnoredActor(out.GetActor());
				params.bTraceComplex = false;
				//params.TraceTag = "DebugTraceBeam";
			}

			// Else, the hit was blocked by an object; End it
			else
			{
				hitpoints.Add(out.ImpactPoint);
				return out.GetActor();
			}

		}

		// The beam hit nothing!!
		else
		{
			hitpoints.Add(reflectionVector * maxDistance + hitpoints[i]);
			return nullptr;
		}

	}
	return nullptr;
}

