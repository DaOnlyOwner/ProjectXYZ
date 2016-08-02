// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "RockMovement.h"

#define ROCK_FALL_TIME (1/4.0f)

//#define horizontal_pos(t) (startPos + (charge/maxCharge) * (t/ROCK_FALL_TIME) * maxRockDistance * normalizedDirectionVector)
//#define vertical_pos(t) (height * (1-(t/ROCK_FALL_TIME)*(t/ROCK_FALL_TIME)))

#define horizontal_pos(t) (startPos + normalizedDirectionVector*950 * charge * t )
#define vertical_pos(t) (height - (981.0f * t*t) / 1.3f )

void URockMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (bMove)
	{
		timeSinceLaunch += DeltaTime;

		FVector newPos = horizontal_pos(timeSinceLaunch);
		newPos.Z = vertical_pos(timeSinceLaunch);
		UpdatedComponent->SetWorldLocation(newPos);
	}
}

void URockMovement::InitializeAndStart(float maxRockDistance, float charge, const FVector & normalizedDirectionVector, float maxCharge)
{
	this->charge = charge;
	this->normalizedDirectionVector = normalizedDirectionVector;
	this->maxCharge = maxCharge;
	this->height = this->UpdatedComponent->GetComponentLocation().Z;
	this->maxRockDistance = maxRockDistance;
	this->startPos = UpdatedComponent->GetComponentLocation();
	bMove = true;
}
