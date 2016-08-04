// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Array.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class ASpell;

UENUM()
enum CharacterState /* used for delay-related mechanics */
{
	READY, /* ready to cast spell */
	BUSY_CHARGING,
	BUSY_BEAMING,
	BUSY_SPRAYING,
	BUSY_PLACING_SPELL, /* to block movement for a short period of time*/
	BUSY_KNOCKED, 
	BUSY_PUSHED,
	BUSY_SHOCKED /* in lightning storms */
};
UENUM()

enum STATUS
{
	NORMAL,
	WET,
	BURNING
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

	UFUNCTION(Server, Reliable, WithValidation)
	void UpdateQueue(const TArray<uint8> &newQueue);
	void UpdateQueue_Implementation(const TArray<uint8> &newQueue);
	bool UpdateQueue_Validation(const TArray<uint8> &newQueue);
	
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

	UPROPERTY(Replicated)
		int State = READY;

	UPROPERTY(Replicated)
		int Status = NORMAL;


	UFUNCTION()
		void onElementQueueChange();

private:
	UPROPERTY(Replicated, ReplicatedUsing=onElementQueueChange)
		TArray<uint8> elementQueue;

	
	FVector startOffset;
	ASpell* currentSpell;
	FTimerHandle chargeHandler;
};
