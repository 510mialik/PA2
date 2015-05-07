// for hash function
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int hash (string s, int size);
void normalize (string &s);

const int MAX_SIZE = 10000;

int main ()
{
	ifstream in;
	in.open ("words.txt");
	if (!in)
	{
		cout << "ERROR OPENING FILE!" << endl;
		return -1;
	}
	string s;
	int words = 0;
	while (!in.eof())
	{
		in >> s;
		normalize (s);
	}
	return 0;
}

int hash (string s, int size)
{
	int h = 0;

	return h;
}


void normalize (string &s)
{
	string t = "";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] <= 'Z' && s[i] >= 'A')
		{
			s[i] += ('a' - 'A');
		}
		if (s[i] <= 'z' && s[i] >= 'a')
		{
			t+= s[i];
		}
	}
	s = t;
}