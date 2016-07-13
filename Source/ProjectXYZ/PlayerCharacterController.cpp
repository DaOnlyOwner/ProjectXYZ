// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacterController.h"

APlayerCharacterController::APlayerCharacterController()
{
		PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacterController::BeginPlay()
{
	
	actor = static_cast<APlayerCharacter*>(this->GetCharacter()); // Later: dynamic cast

	movementVector = FVector(0, 0, 0);
	waypoint = FVector(0, 0, 0);

}

void APlayerCharacterController::ForwardCast() const
{
	actor->ReleaseSpellForward();
}

void APlayerCharacterController::SelfCast() const
{
	actor->ReleaseSpellSelf();
}

//This is just dirty
void APlayerCharacterController::Tick(float DeltaSeconds)
{
	if (WasInputKeyJustPressed(EKeys::Q))
	{
		actor->Push(CElement::getWater());
	}
	else if (WasInputKeyJustPressed(EKeys::W))
	{
		actor->Push(CElement::getLife());
	}
	else if (WasInputKeyJustPressed(EKeys::E))
	{
		actor->Push(CElement::getShield());
	}
	else if (WasInputKeyJustPressed(EKeys::R))
	{
		actor->Push(CElement::getCold());
	}
	else if (WasInputKeyJustPressed(EKeys::A))
	{
		actor->Push(CElement::getLightning());
	}
	else if (WasInputKeyJustPressed(EKeys::S))
	{
		actor->Push(CElement::getDeath());
	}
	else if (WasInputKeyJustPressed(EKeys::D))
	{
		actor->Push(CElement::getEarth());
	}
	else if (WasInputKeyJustPressed(EKeys::F))
	{
		actor->Push(CElement::getFire());
	}




}
void APlayerCharacterController::MoveToWaypoint()
{
	FVector location(actor->GetActorLocation());

	if ((waypoint - location).SizeSquared() >= range)
	{
		FVector direction = (waypoint - location);
		actor->AddMovementInput(movementVector);

	}

}

void APlayerCharacterController::TurnToPoint(const FVector & point, float deltaTime)
{
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(actor->GetActorLocation(), point);
	rotator = FMath::RInterpTo(actor->GetActorRotation(), rotator, deltaTime, turnSpeed);
	SetControlRotation(rotator);
}

void APlayerCharacterController::CustomSetWaypoint(const FVector & waypoint)
{
	this->waypoint = waypoint;

	movementVector = (waypoint - actor->GetActorLocation());
	if (movementVector.Normalize());
	else movementVector = FVector{};

}
