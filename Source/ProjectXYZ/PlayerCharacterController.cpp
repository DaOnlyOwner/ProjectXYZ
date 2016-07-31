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

	InputComponent->BindAction("handleWater", IE_Pressed, this, &APlayerCharacterController::handleWaterKey);
	InputComponent->BindAction("handleLife", IE_Pressed, this, &APlayerCharacterController::handleLifeKey);
	InputComponent->BindAction("handleShield", IE_Pressed, this, &APlayerCharacterController::handleShieldKey);
	InputComponent->BindAction("handleCold", IE_Pressed, this, &APlayerCharacterController::handleColdKey);
	InputComponent->BindAction("handleLightning", IE_Pressed, this, &APlayerCharacterController::handleLightningKey);
	InputComponent->BindAction("handleDeath", IE_Pressed, this, &APlayerCharacterController::handleDeathKey);
	InputComponent->BindAction("handleEarth", IE_Pressed, this, &APlayerCharacterController::handleEarthKey);
	InputComponent->BindAction("handleFire", IE_Pressed, this, &APlayerCharacterController::handleFireKey);
}
void APlayerCharacterController::handleWaterKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the water key"));
	actor->AddElementToQueue(water);
}
void APlayerCharacterController::handleLifeKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the life key"));
	actor->AddElementToQueue(life);
}
void APlayerCharacterController::handleShieldKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the shield key"));
	actor->AddElementToQueue(shield);
}
void APlayerCharacterController::handleColdKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the cold key"));
	actor->AddElementToQueue(cold);
}
void APlayerCharacterController::handleLightningKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the lightning key"));
	actor->AddElementToQueue(lightning);
}
void APlayerCharacterController::handleDeathKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the death key"));
	actor->AddElementToQueue(death);
}
void APlayerCharacterController::handleEarthKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the Earth key"));
	actor->AddElementToQueue(earth);
}
void APlayerCharacterController::handleFireKey()
{
	UE_LOG(LogTemp, Warning, TEXT("player pressed the fire key"));
	actor->AddElementToQueue(fire);
}
void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	actor = static_cast<APlayerCharacter*>(this->GetCharacter());

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
