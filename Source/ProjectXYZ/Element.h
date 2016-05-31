// Fill out your copyright notice in the Description page of Project Settings.




#pragma once


/**
 * 
 */
class PROJECTXYZ_API Element
{
public:
	Element();
	Element(char,char,int);
	
	FORCEINLINE char getOppositeName()
	{
		return oppositeName;
	}

	FORCEINLINE char getName()
	{
		return name;
	}

	~Element();

private:
	
	char oppositeName;
	char name;
	int rank;



};
