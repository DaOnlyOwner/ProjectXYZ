// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "RockMovement.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API URockMovement : public UMovementComponent
{
	GENERATED_BODY()
	
public:

	//Moves the rock to its next position according to the formula: https://github.com/DaOnlyOwner/ProjectXYZ/wiki/Spell-system-notes
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);
	bool bMove;

	URockMovement()
	{
		bUpdateOnlyIfRendered = true;
		FCollisionResponseParams response(ECollisionResponse::ECR_Overlap);
		FCollisionQueryParams query(false);
		InitCollisionParams(query, response);
		SetComponentTickEnabled(false); // This doesn't change anything ): It's still ticking.
	}
	
	void InitializeAndStart(float maxRockDistance, float charge, const FVector & normalizedDirectionVector);

private:
	float timeSinceLaunch = 0;
	FVector startPos;
	float charge;
	float maxRockDistance;
	FVector normalizedDirectionVector;
	float height;


};

