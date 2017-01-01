// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"
#include "BeamPart.generated.h"

UCLASS()
class PROJECTXYZ_API ABeamPart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeamPart();
	void SetSourceTargetPoints(const FVector& source, const FVector& target);
	void SetTemplate(UParticleSystem* systemTemplate);

private:
	UParticleSystemComponent* particleSystemComponent;
	UCapsuleComponent* collision;
};
