// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "BeamSpell.h"

ABeamSpell::ABeamSpell()
{
	this->PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName(TEXT("RootComponent")));
	hitEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("HitEffect")));
}

//TODO: Play effect when it hits actor;
AActor* ABeamSpell::calculateBeamPoints(TArray<FVector>& hitpoints, float maxBounces, float maxDistance)
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(originPlayer.Get());
	params.bTraceAsyncScene = false;
	for (ABeamPart* part : beamParts)
	{
		params.AddIgnoredActor(static_cast<AActor*>(part)); // Don't trace against own beam parts!
	}
	//GetWorld()->DebugDrawTraceTag = "DebugTraceBeam";
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
			if (out.Actor->ActorHasTag(TEXT("Shield")) )
			{
				hitpoints.Add(out.ImpactPoint);
				reflectionVector = reflectionVector - 2 * FVector::DotProduct(reflectionVector, out.ImpactNormal) * out.ImpactNormal;
				maxDistance -= out.Distance;
				params = FCollisionQueryParams{};
				params.AddIgnoredActor(out.GetActor());
				params.bTraceComplex = false;
				for (ABeamPart* part : beamParts)
				{
					params.AddIgnoredActor(static_cast<AActor*>(part)); // Don't trace against own beam parts!
				}
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

void ABeamSpell::StartBehaviorLowLevel()
{
	queryDamage(FName(TEXT("Beam")));	// Retrieve damage;
	FString queueAsFString;
	if (damageInformation.Elements.Num() > 1) // Construct string to retrieve the correct ParticleSystems;
	{
		if (damageInformation.Elements[1] == damageInformation.Elements[0])
			queueAsFString = UElement::GetFStringByID(damageInformation.Elements[0]);
		else queueAsFString = UElement::GetFStringByID(damageInformation.Elements[1]) + UElement::GetFStringByID(damageInformation.Elements[0]);
	}

	else queueAsFString = UElement::GetFStringByID(damageInformation.Elements[0]);


	USpellTable* table = GET_CASTED_DATABASE();
	hitEffectComponent->SetTemplate(table->ParticleSystems[queueAsFString + TEXT("3")]);
	spawnTemplate = table->ParticleSystems[queueAsFString + TEXT("1")];
	reflectorTemplate = table->ParticleSystems[queueAsFString + TEXT("2")];
	GetWorldTimerManager().SetTimer(timerHandle, this, &ABeamSpell::DamageTick, Interval, true);
}

void ABeamSpell::DamageTick()
{
	if (hitActor != nullptr && Cast<IDamageAble>(hitActor))
	{
		IDamageAble::Execute_ReceiveDamage(hitActor, this->damageInformation); // Damage tick; Apply damage to the hit actor
	}
}

void ABeamSpell::EndBehaviorLowLevel()
{
	ASpell::EndBehaviorLowLevel();
	for (int i = 0; i < beamParts.Num(); i++)
	{
		beamParts[i]->Destroy();
	}
}

void ABeamSpell::Tick(float deltaTime)
{
	TArray<FVector> result;
	hitActor = calculateBeamPoints(result, MaxBounces, MaxDistance); 
	resizeBeamPartArray(result.Num() - 1);
	beamParts[0]->SetTemplate(spawnTemplate);	// There are always two elements inside beamParts;
	beamParts[0]->SetSourceTargetPoints(result[0], result[1]);

	for (int i = 1; i < result.Num() - 1; i++) // For each position of a shield, set the corresponding beam part to use the reflection template.
	{
		beamParts[i]->SetTemplate(reflectorTemplate);	
		beamParts[i]->SetSourceTargetPoints(result[i], result[i + 1]);
	}

	if (hitActor != nullptr)
	{
		turnOnHitEffect(result[result.Num() -1], UKismetMathLibrary::FindLookAtRotation(result[result.Num()-2],result[result.Num()-1]));	// Hit an actor, turn on Hit particles;
	}

	else turnOffHitEffect();

}

void ABeamSpell::turnOnHitEffect(const FVector& location, const FRotator& rotation)
{
	if(!systemActive)
	hitEffectComponent->ActivateSystem(true);
	hitEffectComponent->SetWorldTransform(FTransform{ rotation,location });
	systemActive = true;
}

void ABeamSpell::turnOffHitEffect()
{
	if (systemActive)
	{
		hitEffectComponent->DeactivateSystem();
		systemActive = false;
	}
}

void ABeamSpell::resizeBeamPartArray(int newSize)
{
	int overflow = beamParts.Num() - newSize; // overflow > 0 => beamParts > newSize; overflow < 0 => beamParts < newSize
	if (overflow > 0)
	{
		for (int i = 0; i < overflow; i++)
		{
			beamParts.Pop()->Destroy(); // TODO: To increase Performance, don't delete them but rather deactivate them. This is the only thing that hurts the performance; The traces don't hurt it, even after 1000 iterations they only take up ~.36 ms
		}
	}

	else if (overflow < 0)
	{
		for (int i = overflow; i < 0; i++)
		{
			beamParts.Add(static_cast<ABeamPart*>(GetWorld()->SpawnActor(ABeamPart::StaticClass())));
		}
	}

}
