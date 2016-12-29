// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

CElement steam(ElementID::Steam, ElementID::Null, ElementID::Null, STEAM_CHAR);
CElement ice(ElementID::Ice, ElementID::Null, ElementID::Null, ICE_CHAR);
CElement water(ElementID::Water, ElementID::Lightning, ElementID::Earth, WATER_CHAR);
CElement fire(ElementID::Fire, ElementID::Cold,ElementID::Null, FIRE_CHAR);
CElement cold(ElementID::Cold, ElementID::Fire, ElementID::Null, COLD_CHAR);
CElement life(ElementID::Life, ElementID::Death,ElementID::Null, LIFE_CHAR);
CElement death(ElementID::Death, ElementID::Life, ElementID::Null, DEATH_CHAR);
CElement lightning(ElementID::Lightning, ElementID::Earth, ElementID::Water, LIGHTNING_CHAR);
CElement earth(ElementID::Earth, ElementID::Lightning, ElementID::Null, EARTH_CHAR);
CElement shield(ElementID::Shield, ElementID::Shield, ElementID::Null, SHIELD_CHAR);
CElement nullElement(ElementID::Null, ElementID::Null, ElementID::Null, NULL_CHAR);


CElement::CElement(ElementID id_, ElementID canceledBy_, ElementID canceledBy2_, char letter_):id(id_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), letter(letter_)
{

}

CElement::~CElement()
{

}

CElement &CElement::GetCElementByID(ElementID element_id)
{ 
	static CElement table[11] = { shield,earth,lightning,ice,death,life,steam,cold,fire,water,nullElement };
	return table[(uint8)element_id];
}

FString CElement::GetFStringByID(ElementID id)
{
	static FString table[11] = { FString() + SHIELD_CHAR,FString() + EARTH_CHAR,FString() + LIGHTNING_CHAR,FString() + ICE_CHAR,FString() + DEATH_CHAR,FString() + LIFE_CHAR,FString() + STEAM_CHAR,FString() + COLD_CHAR,FString() + FIRE_CHAR,FString() + WATER_CHAR,FString() + NULL_CHAR};
	return table[(uint8)id];
}