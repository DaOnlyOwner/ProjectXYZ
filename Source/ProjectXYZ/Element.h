// Fill out your copyright notice in the Description page of Project Settings.




#pragma once

/*
Class defining the elements.
*/


class PROJECTXYZ_API CElement
{

public:
	CElement();
	CElement(char,char,int);
	
	inline char getOppositeName() const
	{
		return oppositeName;
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
	@return the CElement steam with name=T, rank=3
	*/
	inline static CElement getSteam()
	{
		CElement out('X', 'T', 3);
		return out;
	}

	/*
	@return the CElement ice with name=I, rank=8
	*/
	inline static CElement getIce()
	{
		CElement out('X', 'I', 8);
		return out; 
	}

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
		oppositeName = other.getOppositeName();
		name = other.getName();
		rank = other.getRank();
		return *this;
	}

	~CElement();

private:
	
	char oppositeName;
	char name;
	int rank;



};
