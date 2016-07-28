// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "PlayerCharacterController.h"

APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bAllowTickBeforeBeginPlay = false;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("SetWaypoint", this, &APlayerCharacterController::setWaypoint);
	InputComponent->BindAction("ForwardCast", IE_Pressed, this, &APlayerCharacterController::ForwardCast);
	InputComponent->BindAction("ForwardCast", IE_Released, this, &APlayerCharacterController::ForwardCastRelease);
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	actor = static_cast<APlayerCharacter*>(this->GetCharacter()); // Later: dynamic cast

	MovementVector = FVector(0, 0, 0);
	Waypoint = FVector(0, 0, 0);

}

void APlayerCharacterController::ForwardCast()
{
	actor->ReleaseSpellForward();
}

void APlayerCharacterController::ForwardCastRelease()
{
	actor->KeyupForward();
}

void APlayerCharacterController::SelfCast()
{
	actor->ReleaseSpellSelf();
}

//This is just dirty
void APlayerCharacterController::Tick(float DeltaSeconds)
{
	if (actor != nullptr)
	{
		MoveToWaypoint();
		TurnToWaypoint(DeltaSeconds);

		if (WasInputKeyJustPressed(EKeys::Q))
		{
			actor->AddElementToQueue(water);
		}
		if (WasInputKeyJustPressed(EKeys::W))
		{
			actor->AddElementToQueue(life);
		}
		if (WasInputKeyJustPressed(EKeys::E))
		{
			actor->AddElementToQueue(shield);
		}
		if (WasInputKeyJustPressed(EKeys::R))
		{
			actor->AddElementToQueue(cold);
		}
		if (WasInputKeyJustPressed(EKeys::A))
		{
			actor->AddElementToQueue(lightning);
		}
		if (WasInputKeyJustPressed(EKeys::S))
		{
			actor->AddElementToQueue(death);
		}
		if (WasInputKeyJustPressed(EKeys::D))
		{
			actor->AddElementToQueue(earth);
		}
		if (WasInputKeyJustPressed(EKeys::F))
		{
			actor->AddElementToQueue(fire);
		}
	}
}



void APlayerCharacterController::MoveToWaypoint()
{
	FVector location(actor->GetActorLocation());
	if ((Waypoint - location).SizeSquared() >= Range)
	{
		FVector direction = (Waypoint - location);
		actor->AddMovementInput(MovementVector);

	}

}

void APlayerCharacterController::TurnToWaypoint(float deltaTime)
{
	FHitResult result;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, result);
	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(actor->GetActorLocation(), result.ImpactPoint);
	rotator = FMath::RInterpTo(actor->GetActorRotation(), rotator, deltaTime, TurnSpeed);
	SetControlRotation(rotator);
}

void APlayerCharacterController::setWaypoint(float AxisValue)
{
	if (actor != nullptr && AxisValue > 0)
	{
		FHitResult result;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, result);
		Waypoint = FVector(result.ImpactPoint);

		MovementVector = (Waypoint - actor->GetActorLocation());
		if (MovementVector.Normalize());
		else MovementVector = FVector{};
	}

}
