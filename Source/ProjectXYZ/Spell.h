// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

enum Spelltype
{
	Charged = 0,
	Channeled = 1,
	Burst = 2
};

UCLASS()
class PROJECTXYZ_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	

	Spelltype Type;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void PushAdditionalElement(CElement &el) {
	   switch (additionalElems) {
	     case 0:
		additionalElem1 = el; break;
	     case 1:
		additionalElem2 = el; break;
	     case 2: return;
	   }

	   additionalElems++;
	}
	
	// Advance this if you need.
	virtual void StartBehavior(const APlayerCharacter& player) {};
	virtual void EndBehavior() {};
	
protected:
	CElement &additionalElem1 = nullElement;
	CElement &additionalElem2 = nullElement;
	short additionalElems = 0;

};
