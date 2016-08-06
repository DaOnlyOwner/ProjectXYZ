// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "AoESpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API AAoESpell : public ASpell
{
	GENERATED_BODY()
public:
	AAoESpell();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mesh;

	void EndBehavior();
	void StartBehavior(const APlayerCharacter& player) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	FTimerHandle timerHandler;
};
