//AnagramSet.cpp

#include<iostream>
#include "AnagramSet.h"
using namespace std;

AnagramSet::AnagramSet()
{
	key = "";
	for(int i = 0; i < 100; i++)//change 100
	{
		value[i] = "";
	}
}
//hash it and search for value. return 
string AnagramSet::getKey()
{
	return key;
}
//hash it and search if it has the value. 
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
// hash it then search if it has a value if not add new pointer
// if it has a value then chain it. 
void AnagramSet::insert(string t)
{
	int pos;

	for(int i = 0; i > pos; i--)
	{
		value[i+1] = value[i];
	}
	value[pos-1] = t;
}
