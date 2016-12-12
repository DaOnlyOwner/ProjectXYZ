// Fill out your copyright notice in the Description page of Project Settings.

//[OBSOLOTE]

#pragma once

#include "Engine/DataTable.h"
#include "Element.h"
#include "DamageTable.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FDamageTable : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
		int Q;
	UPROPERTY(EditAnywhere)
		int W;
	UPROPERTY(EditAnywhere)
		int R;
	UPROPERTY(EditAnywhere)
		int A;
	UPROPERTY(EditAnywhere)
		int S;
	UPROPERTY(EditAnywhere)
		int D;
	UPROPERTY(EditAnywhere)
		int F;
	UPROPERTY(EditAnywhere)
		int T;
	UPROPERTY(EditAnywhere)
		int I;

};
