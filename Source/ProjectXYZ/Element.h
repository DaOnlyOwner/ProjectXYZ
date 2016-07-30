// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

/*
Class defining the elements.
*/

enum ElementID {
   NULL_ID,
   WATER_ID,
   LIFE_ID,
   SHIELD_ID,
   COLD_ID,
   LIGHTNING_ID,
   DEATH_ID,
   EARTH_ID,
   FIRE_ID,
   ICE_ID,
   STEAM_ID
};

typedef TArray<uint8> ElementQueue;

class PROJECTXYZ_API CElement
{

public:
        CElement(char name_ , ElementID id, char canceledBy_ , char canceledBy2_, int rank_ );

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

	inline char GetID() const
	{
	   return id;
	}

	inline int GetRank() const
	{
		return rank;
	}

	static CElement &GetElementByID(ElementID id);

	bool Cancels(CElement &el)
	{
	   return id == el.GetCancelledBy() ||
	     id == el.GetCancelledBy2();
	}

	bool isNull()
	{
	   return id == 0;
	}

	// --------------------- END ACCESSORS FOR ELEMENTS ---------------------

	inline bool operator==(ElementID c) const 
	{
		return c == id;
	}

	inline bool operator<(const CElement& other) const
	{
		return other.GetRank() < rank;
	}

	~CElement();

private:
	//don't copy elements
	CElement (CElement &el) {};

	char id;
	char cancelledBy;
	char cancelledBy2;
	char name;
	int rank;
};

extern CElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;


