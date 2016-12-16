// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "BeamSpell.h"


AActor* ABeamSpell::calculateBeamPoints(TArray<FVector>& hitpoints, float maxBounces, float maxDistance)
{
	FHitResult out;
	FVector reflectionVector{ GetActorForwardVector() };
	hitpoints.Add(GetActorLocation());
	for (int i = 0; i < maxBounces; i++)
	{
		// We found something!!
		if (GetWorld()->LineTraceSingleByChannel(out, hitpoints[i], reflectionVector * maxDistance + hitpoints[i],ECollisionChannel::DamageAble) && maxDistance > 0)
		{
			// It is a shield, reflect beam!
			if (out.Actor->ActorHasTag(TEXT("Shield")))
			{
				hitpoints.Add(out.ImpactPoint);
				reflectionVector = reflectionVector - 2 * FVector::DotProduct(reflectionVector, out.ImpactNormal) * out.ImpactNormal;
				maxDistance -= out.Distance;
			}

			// Else, the hit was blocked by an object; End it
			else
			{
				hitpoints.Add(out.ImpactPoint);
				if (out.Actor.IsValid()) return out.Actor.Get();
				else return nullptr;
			}

		}
	}

	return nullptr;

}

