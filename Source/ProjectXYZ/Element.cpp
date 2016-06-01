// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"


CElement::CElement()
{
	name = 0;
	oppositeName = 0;
	rank = 0;
}

CElement::CElement(char name_, char oppositeName_, int rank_):name(name_),oppositeName(oppositeName_),rank(rank_)
{

}


CElement::~CElement()
{
}


