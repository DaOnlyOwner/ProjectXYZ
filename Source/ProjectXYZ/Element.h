// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

/*
Class defining the elements.
*/


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

	bool Cancels(CElement &el)
	{
	   return name == el.GetCancelledBy() ||
	     name == el.GetCancelledBy2();
	}

	bool isNull()
	{
	   return name == 'X';
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

	static CElement getElementByName(char name);

private:
	//don't copy elements
	CElement (CElement &el) {};
	
	char cancelledBy;
	char cancelledBy2;
	char name;
	int rank;
};

extern CElement nullElement, steam, ice, water, fire, cold, life, death, lightning, earth, shield;
