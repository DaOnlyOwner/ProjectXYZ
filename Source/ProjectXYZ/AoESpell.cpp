// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "AoESpell.h"


AAoESpell::AAoESpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AoEMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AAoESpell::OnOverlapBegin);
	mesh->Activate(true);

	this->SetReplicates(true);

}

// Called when the game starts or when spawned
void AAoESpell::BeginPlay()
{
	Super::BeginPlay();

}
void AAoESpell::StartBehaviorLowLevel()
{
    SetActorLocation(originPlayer->GetActorLocation());
    int scale = damageInformation.Elements.Num() * 2 ;
	SetActorRelativeScale3D(FVector(scale, scale, 0.1f));
	GetWorldTimerManager().SetTimer(timerHandler, this, &AAoESpell::EndBehaviorLowLevel, 0.5f, 0);

}
void AAoESpell::EndBehaviorLowLevel()
{
	Destroy();

}
void AAoESpell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()) && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, "OVERLAP", true);
        if (damageInformation.Elements.Contains(ElementID::Water))
		{
			//make OtherActor wet or remove burn

            if (!damageInformation.Elements.Contains(ElementID::Steam))
			{
				// push otherActor

				/*FVector MovementVector = (this->GetActorLocation() - OtherActor->GetActorLocation());
				MovementVector.Normalize();
				static_cast<APlayerCharacter*>(OtherActor)->SetActorLocation(OtherActor->GetActorLocation() + MovementVector*100);*/
			}
			else
			{
				//it's a STEAM+WATER AOE
			}
		}
        else if (damageInformation.Elements.Contains(ElementID::Fire))
		{
            if (!damageInformation.Elements.Contains(ElementID::Steam))
			{
				//make OtherActor burn or remove wet
			}
			else
			{
				//it's a STEAM+FIRE AOE
			}
		}
	}
}

