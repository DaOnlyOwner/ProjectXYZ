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


	/*
	*
	* --------------------- Begin ACCESSORS FOR ELEMENTS ---------------------
	*
	*/

	/*
	@return the CElement steam with name=T, rank=3
	*/
	inline static CElement getSteam()
	{
		CElement out('T', 'X', 'X', 4);
		return out;
	}

	/*
	@return the CElement ice with name=I, rank=8
	*/
	inline static CElement getIce()
	{
		CElement out('I','X', 'X', 7);
		return out; 
	}

	/*
	@return the CElement water with name=Q, rank=1
	*/
	inline static CElement getWater()
	{
		CElement out('Q', 'A', 'D', 1);
		return out;
	}

	/*
	@return the CElement fire with name=F, rank=2
	*/
	inline static CElement getFire()
	{
		CElement out('F', 'R','X', 2);
		return out;
	}

	/*
	@return the CElement cold with name=R, rank=3
	*/
	inline static CElement getCold()
	{
		CElement out('R', 'F', 'X', 3);
		return out;
	}

	/*
	@return the CElement life with name=W, rank=5
	*/
	inline static CElement getLife()
	{
		CElement out('W', 'S','X', 5);
		return out;
	}

	/*
	@return the CElement death with name=S, rank=6
	*/
	inline static CElement getDeath()
	{
		CElement out('S', 'W', 'X', 6);
		return out;
	}


	/*
	@return the CElement lightning with name=A, rank=8
	*/
	inline static CElement getLightning()
	{
		CElement out('A', 'D', 'Q', 8);
		return out;
	}


	/*
	@return the CElement earth with name=D, rank=10
	*/
	inline static CElement getEarth()
	{
		CElement out('D', 'A', 'X', 10);
		return out;
	}


	/*
	@return the CElement shield with name=E, rank=11
	*/
	inline static CElement getShield()
	{
		CElement out('E', 'E', 'X', 11);
		return out;



	}

/*
*
* --------------------- END ACCESSORS FOR ELEMENTS ---------------------
*
*/

	inline bool operator==(char c ) const 
	{
		return c == name;
	}

	inline bool operator<(const CElement& other) const
	{
		return other.getRank() < rank;
	}

	inline CElement& operator=(const CElement& other)
	{
		cancelledBy = other.getCancelledBy();
		cancelledBy2 = other.getCancelledBy2();
		name = other.getName();
		rank = other.getRank();
		return *this;
	}

	~CElement();

private:
	
	char cancelledBy;
	char cancelledBy2;
	char name;
	int rank;



};
