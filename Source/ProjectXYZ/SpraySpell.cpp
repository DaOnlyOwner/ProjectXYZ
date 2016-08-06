// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "SpraySpell.h"


// Sets default values
ASpraySpell::ASpraySpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SprayMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &ASpraySpell::OnOverlapBegin);
	mesh->Activate(true);
	this->SetReplicates(true);
	
}

// Called when the game starts or when spawned
void ASpraySpell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpraySpell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "OVERLAP", true);
		if (spellElements.Contains(WATER_ELEM))
		{
			//make OtherActor wet or remove burn

			if (!spellElements.Contains(STEAM_ELEM))
			{
				// push otherActor

				/*FVector MovementVector = (this->GetActorLocation() - OtherActor->GetActorLocation());
				MovementVector.Normalize();
				static_cast<APlayerCharacter*>(OtherActor)->SetActorLocation(OtherActor->GetActorLocation() + MovementVector*100);*/
			}
			else
			{
				//it's a STEAM+WATER spray
			}
		}
		else if (spellElements.Contains(FIRE_ELEM))
		{
			if (!spellElements.Contains(STEAM_ELEM))
			{
				//make OtherActor burn or remove wet
			}
			else
			{
				//it's a STEAM+FIRE spraya
			}
		}
	}
}

