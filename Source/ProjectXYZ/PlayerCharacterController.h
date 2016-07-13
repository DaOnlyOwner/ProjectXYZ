// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayerCharacter.h"
#include "UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:

	APlayerCharacterController();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SelfCast() const;
	void MoveToWaypoint();
	void TurnToPoint(const FVector & point, float deltaTime);
	void CustomSetWaypoint(const FVector & waypoint);
	void ForwardCast() const;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	// Called to bind functionality to input

private:
	APlayerCharacter* actor;
	FVector movementVector;
	FVector waypoint;
	float range = 10;
	float turnSpeed = 4.5f;
	float movementSpeed = 1.0f;
	
};
