// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam(STEAM_CHAR, NULL_CHAR, NULL_CHAR, 4);
CElement ice(ICE_CHAR, NULL_CHAR, NULL_CHAR, 7);
CElement water(WATER_CHAR, LIGHTNING_CHAR, EARTH_CHAR, 1);
CElement fire(FIRE_CHAR, COLD_CHAR,NULL_CHAR, 2);
CElement cold(COLD_CHAR, FIRE_CHAR, NULL_CHAR, 3);
CElement life(LIFE_CHAR, DEATH_CHAR,NULL_CHAR, 5);
CElement death(DEATH_CHAR, LIFE_CHAR, NULL_CHAR, 6);
CElement lightning(LIGHTNING_CHAR, EARTH_CHAR, WATER_CHAR, 8);
CElement earth(EARTH_CHAR, LIGHTNING_CHAR, NULL_CHAR, 10);
CElement shield(SHIELD_CHAR, SHIELD_CHAR, NULL_CHAR, 11);
CElement nullElement(NULL_CHAR, NULL_CHAR, NULL_CHAR, 0);

CElement::CElement(char name_, char canceledBy_, char canceledBy2_, int rank_):name(name_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_)
{

}

CElement::~CElement()
{
}

