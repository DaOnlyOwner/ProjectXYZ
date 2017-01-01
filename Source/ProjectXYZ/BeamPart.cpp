// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "BeamPart.h"


// Sets default values
ABeamPart::ABeamPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(EName::NAME_Default));
	collision = CreateDefaultSubobject<UCapsuleComponent>(FName(TEXT("CollisionComponent")));
	collision->InitCapsuleSize(50, 1);
	collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	collision->SetCollisionResponseToChannel(ECollisionChannel::DamageAble, ECollisionResponse::ECR_Block);
}

void ABeamPart::SetTemplate(UParticleSystem* systemTemplate)
{
	if(systemTemplate != particleSystemComponent->Template)
	particleSystemComponent->SetTemplate(systemTemplate);
}

void ABeamPart::SetSourceTargetPoints(const FVector& source, const FVector& target)
{
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(source, target);
	SetActorRotation(rotation);
	SetActorLocation(source);
	particleSystemComponent->SetBeamSourcePoint(1, source, 0);
	particleSystemComponent->SetBeamTargetPoint(1, target, 0);
	collision->SetCapsuleHalfHeight((target - source).Size());
	collision->SetRelativeLocation((target - source) / 2.0f);
}