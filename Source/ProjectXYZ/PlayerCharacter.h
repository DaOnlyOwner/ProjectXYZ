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
	NULL_STATE,
	READY, /* ready to cast spell */
	BUSY_CHARGING,
	BUSY_CHANNELING, /* beam and sprays */
	BUSY_HEALING,
	BUSY_PLACING_SPELL, /* to block movement for a short period of time*/
	BUSY_KNOCKED, 
	BUSY_PUSHED,
	BUSY_SHOCKED /* in lightning storms */
};
UENUM()

enum Status
{
	NORMAL,
	WET,
	BURNING,
	COLD
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
	
	UFUNCTION(Server,Reliable, WithValidation)
	void ReleaseSpellForwardNet(const TArray<uint8>  &elementQueue);
	void ReleaseSpellForwardNet_Implementation(const TArray<uint8> &elementQueue);
	bool ReleaseSpellForwardNet_Validate(const TArray<uint8> &elementQueue);

	UFUNCTION(Server, Reliable, WithValidation)
	void KeyupForwardNet();
	void KeyupForwardNet_Implementation();
	bool KeyupForwardNet_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ReleaseSpellSelfNet(const TArray<uint8> &elementQueue);
	void ReleaseSpellSelfNet_Implementation(const TArray<uint8> &elementQueue);
	bool ReleaseSpellSelfNet_Validate(const TArray<uint8> &elementQueue);

	//Executed only on the server
	void KillActor(enum Spelltype spelltype);
	void AddElementToQueue(CElement &e);
	int QueueToSpellType(TArray<uint8> elementQueue);
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Garuanteed to be executed only on the server
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* camera;

	UPROPERTY(EditAnywhere)
		float SmoothingTime = 4.5f;

	UPROPERTY(EditAnywhere)
		float ScreenScale = 1000.0f;

	UPROPERTY(BlueprintReadOnly, Replicated, ReplicatedUsing = onHealthChanged) // update healthbar etc.
		float Health;

	UPROPERTY(Replicated, ReplicatedUsing = onStateChange)
		int State = READY;

	UPROPERTY(Replicated)
		int Status = NORMAL;

	UFUNCTION()
		void setStateToReady();




	UFUNCTION()
		void onElementQueueChange();
	UFUNCTION()
		void onStateChange();
	UFUNCTION()
		void onCurrentSpellChange();

	UFUNCTION()
		void onWardChange();

	UFUNCTION(BlueprintImplementableEvent)
		void onHealthChanged();


private:

	UPROPERTY(Replicated, ReplicatedUsing = onWardChange)
		TArray<uint8> wards;

	UPROPERTY(Replicated, ReplicatedUsing = onElementQueueChange)
		TArray<uint8> elementQueue;

		TArray<uint8> serverSideElementQueue;

	UPROPERTY(Replicated, ReplicatedUsing = onCurrentSpellChange)
		ASpell* currentSpell;	
	FVector startOffset;

	FTimerHandle timerHandler;
};
