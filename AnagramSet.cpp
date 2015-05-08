//AnagramSet.cpp

#include<iostream>
#include "AnagramSet.h"
using namespace std;

AnagramSet::AnagramSet()
{
	key = "";
	for(int i = 0; i < 100; i++)
	{
		value[i] = "";
	}
}

string AnagramSet::getKey()
{
	return key;
}

bool AnagramSet::hasValue()
{
	for(int i = 0; i < 100; i++)
	{
		if(value[i] == key)
		{
			return true;
		}
	}
	return false;
}

void AnagramSet::insert(string t)
{
	int pos;

	for(int i = 0; i > pos; i--)
	{
		value[i+1] = value[i];
	}
	value[pos-1] = t;
}
//I want to edit 
