//Anagramset.h

#ifndef ANAGRAMSET_H
#define ANAGRAMSET_H
#include<iostream>
using namespace std;

class AnagramSet
{
	public:
		string key;
		string value[100];

		AnagramSet();
		string getKey();
		bool hasValue();
		void insert(string);
};
#endif
