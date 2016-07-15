// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Array.h"
#include "CustomGameState.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


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
	void ReleaseSpellSelf();


	void Push(CElement e);

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

	

private:

	CElement* stack = nullptr;
	FVector startOffset;
	int index = 0;
};
