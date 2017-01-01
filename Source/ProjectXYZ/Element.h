// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectXYZ.h"

/*Defining elements*/

#define STEAM_CHAR 'T'
#define ICE_CHAR 'I'
#define WATER_CHAR 'Q'
#define FIRE_CHAR 'F'
#define COLD_CHAR 'R'
#define LIFE_CHAR 'W'
#define DEATH_CHAR 'S'
#define LIGHTNING_CHAR 'A'
#define EARTH_CHAR 'D'
#define SHIELD_CHAR 'E'
#define NULL_CHAR ' '
#define SELFCAST_CHAR '!'


UENUM(BlueprintType)
enum class ElementID : uint8
{
	Shield, Earth, Lightning, Ice, Death, Life, Steam, Cold, Fire, Water, NullElement
};

class PROJECTXYZ_API UElement
{

public:
    UElement(ElementID id_ , ElementID canceledBy_ , ElementID canceledBy2_,  char letter_);

	/*
	@return first opposite element.
	@example q cancels a
	*/
	inline ElementID GetCancelledBy() const //q cancels a
	{
		return cancelledBy;
	}

	/*
	@return second opposite element.
	@example d cancels a
	*/
	inline ElementID GetCancelledBy2() const //d cancels a
	{
		return cancelledBy2;
	}

	inline ElementID GetID() const
	{
		return id;
	}
    inline char GetLetter() const
    {
		return letter;
	}

	inline bool Cancels(UElement &el) const
	{
	   return id == el.GetCancelledBy() ||
	     id == el.GetCancelledBy2();
	}

	inline bool isNull() const
    {
	   return id == ElementID::NullElement;
	}

	// --------------------- END ACCESSORS FOR ELEMENTS ---------------------

	inline bool operator==(UElement &el) const 
	{
	   return id == el.GetID();
	}

	inline bool operator<(const UElement& other) const
	{
	   return id < other.GetID();
	}

	~UElement();

	static UElement &GetCElementByID(ElementID id);
	static FString GetFStringByID(ElementID id);
private:
	//don't copy elements
    UElement () {}
	
	ElementID cancelledBy;
	ElementID cancelledBy2;
	ElementID id;
    char letter;
};

extern UElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;
