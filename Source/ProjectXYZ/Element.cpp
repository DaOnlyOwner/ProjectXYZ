// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam('T', 'X', 'X', 4);
CElement ice('I','X', 'X', 7);
CElement water('Q', 'A', 'D', 1);
CElement fire('F', 'R','X', 2);
CElement cold('R', 'F', 'X', 3);
CElement life('W', 'S','X', 5);
CElement death('S', 'W', 'X', 6);
CElement lightning('A', 'D', 'Q', 8);
CElement earth('D', 'A', 'X', 10);
CElement shield('E', 'E', 'X', 11);
CElement nullElement('X', 'X', 'X', 0);

CElement::CElement(char name_, char canceledBy_, char canceledBy2_, int rank_):name(name_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_)
{
	/*UE_LOG(LogTemp, Warning, TEXT("new element instanciated"));*/
}


CElement::~CElement()
{
}

CElement CElement::getElementByName(char name)
{
	switch (name)
	{
	case 'Q': return water;
	case 'W': return life;
	case 'E': return shield;
	case 'R': return cold;
	case 'A': return lightning;
	case 'S': return death;
	case 'D': return earth;
	case 'F': return fire;
	default: return nullElement;
	}
	
}
