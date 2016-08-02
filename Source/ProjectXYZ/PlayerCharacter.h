// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Array.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class ASpell;

USTRUCT()
struct FElemQueueStruct
{
	GENERATED_USTRUCT_BODY()
public:
	uint8 element1;
	uint8 element2;
	uint8 element3;
};


UCLASS()
class PROJECTXYZ_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	~APlayerCharacter();

	void moveCamera(float DeltaSeconds);
	void ReleaseSpellForward();
	void beginCharge();
	void endCharge();
	void ReleaseSpellSelf();
	void KeyupForward();

	void AddElementToQueue(CElement &e);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* camera;

	UPROPERTY(EditAnywhere)
		float SmoothingTime = 4.5f;

	UPROPERTY(EditAnywhere)
		float ScreenScale = 1000.0f;

	UPROPERTY(EditAnywhere)
		float MaxChargeTime = 5.0;
	
	UPROPERTY(Replicated, ReplicatedUsing=onElemQueueChange)
		TArray<int> ElemQueue;

	UFUNCTION()
		void onElemQueueChange();

private:
	
	CElement *elementQueue[3] = { &nullElement, &nullElement, &nullElement };
	
	FVector startOffset;
	ASpell* currentSpell;
	int elementQueueSize = 0;
	FTimerHandle chargeHandler;
};
