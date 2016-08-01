// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayerCharacter.h"
#include "ChargeableSpell.h"
#include "RockMovement.h"
#include "RockSpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXYZ_API ARockSpell : public AChargeableSpell
{
	GENERATED_BODY()
	
public:

	//This are public because you can change it whenever you want
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
		UStaticMeshComponent* RockMesh;

	UPROPERTY(EditAnywhere)
		float MaxRockDistance;

	ARockSpell();
	~ARockSpell();
	void StartBehavior(const APlayerCharacter& player) override;
	void EndBehavior() override;
	
private:
	URockMovement* movementComponent;
};
