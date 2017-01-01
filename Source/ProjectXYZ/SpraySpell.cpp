// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "SpraySpell.h"

void ASpraySpell::queryDamage()
{
	FString contextString(TEXT("Default"));
	USpellTable* database_ = static_cast<USpellTable*>(database);
    UDataTable* damageValues = database_->DamageTable;
	FDamageTable * row;

    if(damageInformation.Elements.Contains(steam.GetID()))
    {
		row = damageValues->FindRow<FDamageTable>(FName{ TEXT("SteamSpray") },contextString,true); // true only for debugging. 
    }

    else
    {
		row = damageValues->FindRow<FDamageTable>(FName{ TEXT("Spray") }, contextString, true);
    }
	assignDamageValues(row);
}

void ASpraySpell::Tick(float deltaTime)
{
	UTools::OverlapCone(originPlayer.Get(), cachedHitResults, ECollisionChannel::DamageAble, 30, 200, TArray<AActor*>{}, true, false);
	for (int i = 0; i < cachedHitResults.Num(); i++)
	{
		AActor* actor = cachedHitResults[i];
		if (actor->Implements<UDamageAble>())
		{
			// I didn't find a reasonable method to push the actor back. I am thinking of applying an impuls to the actor based on how far away he is from the source of the spell (the player)
			//IDamageAble::Execute_Push(actor, originPlayer->GetActorForwardVector() * pushFactor * (16000.0f / actor->GetSquaredDistanceTo(originPlayer.Get())));
		}
	}
}

void ASpraySpell::StartBehaviorLowLevel()
{
	queryDamage();	// Retrieve the damage
	USpellTable* database_ = static_cast<USpellTable*>(database);	// Retrieve the particle system for the spell; It's different for every spell, so I don't refractor into a function
	UParticleSystem* PStemplate = database_->ParticleSystems[UElement::GetFStringByID(damageInformation.Elements[0])];
	systemComponent = UGameplayStatics::SpawnEmitterAttached(PStemplate, RootComponent, NAME_None, ((FVector)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
	GetWorldTimerManager().SetTimer(timerHandle, this, &ASpraySpell::DamageTick, interval, true);	// Set a timer; main logic inside the DamageTick function.
	isWaterSpray = (damageInformation.Elements[0] == ElementID::Water);	// If its a waterspray, turn on ticking;
	if (isWaterSpray)
	{
		this->SetActorTickEnabled(true);
	}
	else this->SetActorTickEnabled(false);
}

void ASpraySpell::DamageTick()
{
	if (!isWaterSpray)
	UTools::OverlapCone(originPlayer.Get(), cachedHitResults, ECollisionChannel::DamageAble, openingAngle, 200, TArray<AActor*>{}, true, false);

	for (int i = 0; i < cachedHitResults.Num(); i++)
	{
		AActor* actor = cachedHitResults[i];
		if (actor->Implements<UDamageAble>())
		{
			IDamageAble::Execute_ReceiveDamage(actor, this->damageInformation);
		}
	}
	cachedHitResults.Empty();
}

void ASpraySpell::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(timerHandle);
}


