// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"


CElement::CElement()
{
	name = 0;
	canceledBy = 0;
	canceledBy2 = 0;
	rank = 0;
}

CElement::CElement(char name_, char canceledBy_, char canceledBy2_, int rank_):name(name_),canceledBy(canceledBy_), canceledBy2(canceledBy2_), rank(rank_)
{

}


CElement::~CElement()
{
}


