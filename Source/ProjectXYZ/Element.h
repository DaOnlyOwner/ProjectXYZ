// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

/*
Class defining the elements.
*/

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

UENUM()
enum ElementID
{
   SHIELD_ELEM,
   EARTH_ELEM,
   LIGHTNING_ELEM,
   ICE_ELEM,
   DEATH_ELEM,
   LIFE_ELEM,
   STEAM_ELEM,
   COLD_ELEM,
   FIRE_ELEM,
   WATER_ELEM,
   NULL_ELEM
};

class PROJECTXYZ_API CElement
{

public:
	CElement(ElementID id_ , ElementID canceledBy_ , ElementID canceledBy2_,  char letter_);

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

	inline bool Cancels(CElement &el) const
	{
	   return id == el.GetCancelledBy() ||
	     id == el.GetCancelledBy2();
	}

	inline bool isNull() const
	{
	   return id == NULL_ELEM;
	}

	// --------------------- END ACCESSORS FOR ELEMENTS ---------------------

	inline bool operator==(CElement &el) const 
	{
	   return id == el.GetID();
	}

	inline bool operator<(const CElement& other) const
	{
	   return id < other.GetID();
	}

	~CElement();

	static CElement &GetCElementByID(ElementID id);
private:
	//don't copy elements
	CElement () {};
	
	ElementID cancelledBy;
	ElementID cancelledBy2;
	ElementID id;
	char letter;
};

extern CElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;
