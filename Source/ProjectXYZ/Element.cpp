// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"


CElement::CElement()
{
	name = 0;
	cancelledBy = 0;
	cancelledBy2 = 0;
	rank = 0;
}

CElement::CElement(char name_, char canceledBy_, char canceledBy2_, int rank_):name(name_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_)
{

}


CElement::~CElement()
{
}


