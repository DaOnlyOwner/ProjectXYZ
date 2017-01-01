// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectXYZ.h"
#include "Element.h"

UElement steam(ElementID::Steam, ElementID::NullElement, ElementID::NullElement, STEAM_CHAR);
UElement ice(ElementID::Ice, ElementID::NullElement, ElementID::NullElement, ICE_CHAR);
UElement water(ElementID::Water, ElementID::Lightning, ElementID::Earth, WATER_CHAR);
UElement fire(ElementID::Fire, ElementID::Cold,ElementID::NullElement, FIRE_CHAR);
UElement cold(ElementID::Cold, ElementID::Fire, ElementID::NullElement, COLD_CHAR);
UElement life(ElementID::Life, ElementID::Death,ElementID::NullElement, LIFE_CHAR);
UElement death(ElementID::Death, ElementID::Life, ElementID::NullElement, DEATH_CHAR);
UElement lightning(ElementID::Lightning, ElementID::Earth, ElementID::Water, LIGHTNING_CHAR);
UElement earth(ElementID::Earth, ElementID::Lightning, ElementID::NullElement, EARTH_CHAR);
UElement shield(ElementID::Shield, ElementID::Shield, ElementID::NullElement, SHIELD_CHAR);
UElement nullElement(ElementID::NullElement, ElementID::NullElement, ElementID::NullElement, NULL_CHAR);


UElement::UElement(ElementID id_, ElementID canceledBy_, ElementID canceledBy2_, char letter_):id(id_),cancelledBy(canceledBy_), cancelledBy2(canceledBy2_), letter(letter_)
{

}

UElement::~UElement()
{

}

UElement &UElement::GetCElementByID(ElementID element_id)
{ 
	static UElement table[11] = { shield,earth,lightning,ice,death,life,steam,cold,fire,water,nullElement };
	return table[(uint8)element_id];
}

FString UElement::GetFStringByID(ElementID id)
{
	static FString table[11] = { FString() + SHIELD_CHAR,FString() + EARTH_CHAR,FString() + LIGHTNING_CHAR,FString() + ICE_CHAR,FString() + DEATH_CHAR,FString() + LIFE_CHAR,FString() + STEAM_CHAR,FString() + COLD_CHAR,FString() + FIRE_CHAR,FString() + WATER_CHAR,FString() + NULL_CHAR};
	return table[(uint8)id];
}