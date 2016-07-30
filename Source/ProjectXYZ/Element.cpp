// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam('T', STEAM_ID, NULL_ID, NULL_ID, 4);
CElement ice('I', ICE_ID, NULL_ID, NULL_ID, 7);
CElement water('Q', WATER_ID, LIGHTNING_ID, EARTH_ID, 1);
CElement fire('F', FIRE_ID, COLD_ID, NULL_ID, 2);
CElement cold('R', COLD_ID, FIRE_ID, NULL_ID, 3);
CElement life('W', LIFE_ID, DEATH_ID, NULL_ID, 5);
CElement death('S', DEATH_ID, LIFE_ID, NULL_ID, 6);
CElement lightning('A', LIGHTNING_ID, EARTH_ID, WATER_ID, 8);
CElement earth('D', EARTH_ID, LIGHTNING_ID, NULL_ID, 10);
CElement shield('E', SHIELD_ID, SHIELD_ID, NULL_ID, 11);
CElement nullElement('X', NULL_ID, NULL_ID, NULL_ID, 0);

CElement::CElement(char name_, ElementID id_, char canceledBy_, char canceledBy2_, int rank_):name(name_), id(id_), cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), rank(rank_)
{

}


CElement::~CElement()
{
}


CElement &CElement::GetElementByID(ElementID id)
{
   static CElement *table[] = {&nullElement, &water, &life, &shield, &cold, &lightning, &death, &earth, &fire, &ice, &steam};

   if(id > 10)
      return nullElement;
   else 
      return *table[id];
}
