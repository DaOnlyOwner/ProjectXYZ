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
	void SelfCast(); // May not be const
	void ForwardCast(); // May not be const

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "MoveFunctions")
		void TurnToWaypoint(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = "MoveFunctions")
		void MoveToWaypoint();


	UPROPERTY(EditAnywhere)
		float Range = 10;

	UPROPERTY(BlueprintReadOnly)
		FVector Waypoint;


	UPROPERTY(EditAnywhere)
		float TurnSpeed = 4.5f;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1.0f;

	UPROPERTY(BlueprintReadOnly)
		FVector MovementVector;



private:
	APlayerCharacter* actor;
	void setWaypoint(float AxisValue);
};
