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
#define NULL_CHAR '-'
#define SELFCAST_CHAR '!'

UENUM()
enum ELEMENTS
{
	NULL_ELEM,
	WATER_ELEM,
	LIFE_ELEM,
	SHIELD_ELEM,
	COLD_ELEM,
	LIGHTNING_ELEM,
	DEATH_ELEM,
	EARTH_ELEM,
	FIRE_ELEM,
	STEAM_ELEM,
	ICE_ELEM
};

class PROJECTXYZ_API CElement
{

public:
	CElement(int name_ , int canceledBy_ , int canceledBy2_, int rank_ , char letter_);

	/*
	@return first opposite element.
	@example q cancels a
	*/
	inline int GetCancelledBy() const //q cancels a
	{
		return cancelledBy;
	}

	/*
	@return second opposite element.
	@example d cancels a
	*/
	inline int GetCancelledBy2() const //d cancels a
	{
		return cancelledBy2;
	}

	inline int GetName() const
	{
		return name;
	}
	inline char GetLetter() const
	{
		return letter;
	}

	inline int GetRank() const
	{
		return rank;
	}

	inline bool Cancels(CElement &el) const
	{
	   return name == el.GetCancelledBy() ||
	     name == el.GetCancelledBy2();
	}

	inline bool isNull() const
	{
	   return name == NULL_CHAR;
	}

	// --------------------- END ACCESSORS FOR ELEMENTS ---------------------

	inline bool operator==(char c ) const 
	{
		return c == name;
	}

	inline bool operator<(const CElement& other) const
	{
		return other.GetRank() < rank;
	}

	~CElement();

	static CElement GetCElementByName(int name);
	char name;

private:
	//don't copy elements
	CElement () {};
	
	char cancelledBy;
	char cancelledBy2;
	int rank;
	char letter;
};

extern CElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;
