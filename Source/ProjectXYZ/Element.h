// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

/*
Class defining the elements.
*/


class PROJECTXYZ_API CElement
{

public:
	CElement();
	CElement(char name_ ,char canceledBy_ , char canceledBy2_, int rank_ );

	/*
	@return first opposite element.
	@example q cancels a
	*/
	inline char getCancelledBy() const //q cancels a
	{
		return cancelledBy;
	}


	/*
	@return second opposite element.
	@example d cancels a
	*/
	inline char getCancelledBy2() const //d cancels a
	{
		return cancelledBy2;
	}

	inline char getName() const
	{
		return name;
	}

	inline int getRank() const
	{
		return rank;
	}

	bool cancels(CElement &el)
	{
	   return name == el.getCancelledBy() ||
	     name == el.getCancelledBy2();
	}


	// --------------------- END ACCESSORS FOR ELEMENTS ---------------------

	inline bool operator==(char c ) const 
	{
		return c == name;
	}

	inline bool operator<(const CElement& other) const
	{
		return other.getRank() < rank;
	}

	~CElement();

private:
	
	char cancelledBy;
	char cancelledBy2;
	char name;
	int rank;
};

extern CElement steam, ice, water, fire, cold, life, death, lightning, earth, shield;
