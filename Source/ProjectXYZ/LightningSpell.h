// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpellSystemConstants.h"
#include "Spell.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "LightningSpell.generated.h"

UCLASS()
class PROJECTXYZ_API ALightningSpell : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightningSpell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void StartBehavior(APlayerCharacter& playerCharacter) override;

private:
	void bounce(AActor* actor, int bounce);
	void triggerNextLightningTick(void);
	FCollisionShape boxShape;
	TArray<AActor*> lightningChain;
	FTimerHandle lightningHandle;
	int tickAmount = 0;
	


};
