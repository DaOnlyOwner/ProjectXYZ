// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam(STEAM_ELEM, NULL_ELEM, NULL_ELEM, STEAM_CHAR);
CElement ice(ICE_ELEM, NULL_ELEM, NULL_ELEM, ICE_CHAR);
CElement water(WATER_ELEM, LIGHTNING_ELEM, EARTH_ELEM, WATER_CHAR);
CElement fire(FIRE_ELEM, COLD_ELEM,NULL_ELEM, FIRE_CHAR);
CElement cold(COLD_ELEM, FIRE_ELEM, NULL_ELEM, COLD_CHAR);
CElement life(LIFE_ELEM, DEATH_ELEM,NULL_ELEM, LIFE_CHAR);
CElement death(DEATH_ELEM, LIFE_ELEM, NULL_ELEM, DEATH_CHAR);
CElement lightning(LIGHTNING_ELEM, EARTH_ELEM, WATER_ELEM, LIGHTNING_CHAR);
CElement earth(EARTH_ELEM, LIGHTNING_ELEM, NULL_ELEM, EARTH_CHAR);
CElement shield(SHIELD_ELEM, SHIELD_ELEM, NULL_ELEM, SHIELD_CHAR);
CElement nullElement(NULL_ELEM, NULL_ELEM, NULL_ELEM, NULL_CHAR);

CElement::CElement(ElementID id_, ElementID canceledBy_, ElementID canceledBy2_, char letter_):id(id_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), letter(letter_)
{

}

CElement::~CElement()
{
}

CElement &CElement::GetCElementByID(ElementID element_id)
{ 
	switch (element_id)
	{
	case SHIELD_ELEM: return shield;
	case EARTH_ELEM: return earth;
	case LIGHTNING_ELEM: return lightning;
	case ICE_ELEM: return ice;
	case DEATH_ELEM: return death;
	case LIFE_ELEM: return life;
	case STEAM_ELEM: return steam;
	case COLD_ELEM: return cold;
	case FIRE_ELEM: return fire;
	case WATER_ELEM: return water;
	default:
		return nullElement;
	}
}
