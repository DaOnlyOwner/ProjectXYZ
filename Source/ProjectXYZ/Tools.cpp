// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Tools.h"

bool UTools::OverlapCone(AActor* causer,
	TArray<AActor*>& outHitresults,
	ECollisionChannel channel,
	float openingAngle,
	float length,
	const TArray<AActor*>& actorsToIgnore, 
	bool ignoreCauser,
	bool traceComplex)
{
	TArray<FOverlapResult> results;
	FCollisionQueryParams params{};
	params.bTraceComplex = traceComplex;
	if(actorsToIgnore.Num() != 0)
		params.AddIgnoredActors(actorsToIgnore);
	if (ignoreCauser)
		params.AddIgnoredActor(causer);
	//causer->GetWorld()->DebugDrawTraceTag = "OverlapCone";
	//params.TraceTag = "OverlapCone";
	bool hit = causer->GetWorld()->OverlapMultiByChannel(results, causer->GetActorLocation(), causer->GetActorRotation().Add(0,0,0).Quaternion(), channel, FCollisionShape::MakeBox(FVector{ length,length,length }), params);
	if (!hit) return false;
	for (int i = 0; i < results.Num(); i++)
	{
		FOverlapResult& result = results[i];
		AActor* actor = result.GetActor();
		FVector locationToTest{ actor->GetActorLocation() };
		locationToTest.Z = causer->GetActorLocation().Z; // Same height has the causer;
		FVector dirToHitresult = locationToTest - causer->GetActorLocation();
		dirToHitresult.Normalize();
		float cosalpha = FVector::DotProduct(dirToHitresult, causer->GetActorForwardVector());
		float alpha = FMath::Acos(cosalpha);
		//DrawDebugLine(causer->GetWorld(), causer->GetActorLocation(), locationToTest, FColor::Green, true, 3.0f,(uint8)'\000',1.0f);
		if (FMath::RadiansToDegrees(alpha) <= openingAngle)
		{
			outHitresults.Add(actor);
		}
	}

	return true;
}

float UTools::CalculateFinalDamage(AActor* damageAbleObject, const TArray<ElementID>& elementKeys, const TArray<int>& rawDamage)
{
	// Can be optimized I guess
	// Make this non staic some day. 

	if (!(damageAbleObject->GetClass()->ImplementsInterface(UDamageAble::StaticClass())))
		return 0;

	TArray<ElementID> elementKeysUnique;
	TArray<int> rawDamageUnique;
	for (int i = 0; i < elementKeys.Num(); i++)
	{
		elementKeysUnique.AddUnique(elementKeys[i]); 
		rawDamageUnique.AddUnique(rawDamage[i]);
	}

	int seed = 0;
	for (int i = 0; i < elementKeysUnique.Num(); i++)
	{
		ElementID id = elementKeysUnique[i];
		int count = 0;
		for (int k = 0; k < elementKeys.Num(); k++)
		{
			if (id == elementKeys[k]) count++;
		}

		seed += IDamageAble::Execute_CalculateDamageForElementID(damageAbleObject, id, count, rawDamageUnique[i]);
	}
	return seed;
}
