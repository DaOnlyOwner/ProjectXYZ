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
#define NULL_CHAR 'X'
#define SELFCAST_CHAR '!'

class PROJECTXYZ_API CElement
{

public:
	CElement(char name_ ,char canceledBy_ , char canceledBy2_, int rank_ );

	/*
	@return first opposite element.
	@example q cancels a
	*/
	inline char GetCancelledBy() const //q cancels a
	{
		return cancelledBy;
	}

	/*
	@return second opposite element.
	@example d cancels a
	*/
	inline char GetCancelledBy2() const //d cancels a
	{
		return cancelledBy2;
	}

	inline char GetName() const
	{
		return name;
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

private:
	//don't copy elements
	CElement (CElement &el) {};
	char cancelledBy;
	char cancelledBy2;
	char name;
	int rank;
};

extern CElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;
