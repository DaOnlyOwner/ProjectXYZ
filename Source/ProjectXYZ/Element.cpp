// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam(STEAM_ELEM, NULL_ELEM, NULL_ELEM, 4);
CElement ice(ICE_ELEM, NULL_ELEM, NULL_ELEM, 7);
CElement water(WATER_ELEM, LIGHTNING_ELEM, EARTH_ELEM, 1);
CElement fire(FIRE_ELEM, COLD_ELEM,NULL_ELEM, 2);
CElement cold(COLD_ELEM, FIRE_ELEM, NULL_ELEM, 3);
CElement life(LIFE_ELEM, DEATH_ELEM,NULL_ELEM, 5);
CElement death(DEATH_ELEM, LIFE_ELEM, NULL_ELEM, 6);
CElement lightning(LIGHTNING_ELEM, EARTH_ELEM, WATER_ELEM, 8);
CElement earth(EARTH_ELEM, LIGHTNING_ELEM, NULL_ELEM, 10);
CElement shield(SHIELD_ELEM, SHIELD_ELEM, NULL_ELEM, 11);
CElement nullElement(NULL_ELEM, NULL_ELEM, NULL_ELEM, 0);

CElement::CElement(int name_, int canceledBy_, int canceledBy2_, int rank_):name(name_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_)
{

}

CElement::~CElement()
{
}

CElement CElement::getCElementByName(int name)
{
	switch (name)
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
