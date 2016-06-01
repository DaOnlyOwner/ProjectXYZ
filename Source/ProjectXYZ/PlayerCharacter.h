// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Element.h"
#include "Array.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class PROJECTXYZ_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	~APlayerCharacter();

	FORCEINLINE void Push(CElement e) // Compiler optimization: Copy elision.
	{ 

		if (index == 3)
		{
			return; // Not more than 3 elements at once.
		}

		for (int i = 0; i < index; i++)
		{
			if (stack[i].getOppositeName() == e.getName()) 
			{
				// Remove stack[i] and resize, looks like O(n^2), however its actually O(n+n) = O(n)
				// because we only evaluate the for expression once. 
				for (int k = i; k < index-1; k++)
				{
					stack[k] = stack[k + 1];
				}
				index--;
				break; // One element can only remove one element from the Q.
				//TODO: Function to inform that element was removed
			
			}
		}

		stack[index] = e;
		index++;
	}	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	

private:

	CElement* stack = nullptr;
	int index = 0;
};
