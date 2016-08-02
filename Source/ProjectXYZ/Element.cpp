// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam(STEAM_ELEM, NULL_ELEM, NULL_ELEM, 4, STEAM_CHAR);
CElement ice(ICE_ELEM, NULL_ELEM, NULL_ELEM, 7, ICE_CHAR);
CElement water(WATER_ELEM, LIGHTNING_ELEM, EARTH_ELEM, 1, WATER_CHAR);
CElement fire(FIRE_ELEM, COLD_ELEM,NULL_ELEM, 2, FIRE_CHAR);
CElement cold(COLD_ELEM, FIRE_ELEM, NULL_ELEM, 3, COLD_CHAR);
CElement life(LIFE_ELEM, DEATH_ELEM,NULL_ELEM, 5, LIFE_CHAR);
CElement death(DEATH_ELEM, LIFE_ELEM, NULL_ELEM, 6, DEATH_CHAR);
CElement lightning(LIGHTNING_ELEM, EARTH_ELEM, WATER_ELEM, 8, LIGHTNING_CHAR);
CElement earth(EARTH_ELEM, LIGHTNING_ELEM, NULL_ELEM, 10, EARTH_CHAR);
CElement shield(SHIELD_ELEM, SHIELD_ELEM, NULL_ELEM, 11, SHIELD_CHAR);
CElement nullElement(NULL_ELEM, NULL_ELEM, NULL_ELEM, 0, NULL_CHAR);

CElement::CElement(int name_, int canceledBy_, int canceledBy2_, int rank_, char letter_):name(name_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_), letter(letter_)
{

}

CElement::~CElement()
{
}

CElement CElement::GetCElementByName(int element_id)
{ 
	switch (element_id)
	{
		case WATER_ELEM: return water;
		case FIRE_ELEM: return fire;
		case COLD_ELEM: return cold;
		case LIFE_ELEM: return life;
		case DEATH_ELEM: return death;
		case LIGHTNING_ELEM: return lightning;
		case EARTH_ELEM: return earth;
		case SHIELD_ELEM: return shield;
	}
	return nullElement;
}
