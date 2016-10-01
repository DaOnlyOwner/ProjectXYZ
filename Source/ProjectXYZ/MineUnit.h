// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spell.h"
#include "MineUnit.generated.h"

UCLASS()
class PROJECTXYZ_API AMineUnit : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void EndBehavior();
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool Triggered = false;

	void Explode();

	FTimerHandle timerHandler;
	
};
