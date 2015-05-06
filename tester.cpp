#include <iostream>
#include "AnagramSet.h"
#include "Dictionary.h"
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;
const int maxWords = 200000;
string words[maxWords], reversedWords[maxWords];

int tfine; // used for timer

void resetTimer() ;  // reset the timer
int getTime();  // get elapsed time

// read file into wordList. Return number of words read in
int readInWords(string wordList[],  int maxSize, string fileName) ;

// return the reverse of s
string reverse(const string & s);

// count the number of words in wordList that are in d
void countHits (string wordList[], int length,  Dictionary & d);

// write the dictionary to a file
void toFile(const Dictionary & d, const string & fileName) ;

// find palindromic words (bob) and palindrom pairs (live evil)
void findPalindromes(Dictionary & d, int numWords);

// count anagrams
void countAnagrams( Dictionary & d, int minimum, string wordList[], int length);

// remove words from dictionary
void removalTest( Dictionary & d, int numWords, int howMany) ;

// insert words to dictionary
void insertionTest( Dictionary & d, int numWords);

// find words whose letters match a given string
void unScramble(Dictionary & d);

int main() {

	int  tableSize;
	cout << "What is the hash table size? ";
	cin >> tableSize;
	resetTimer();
	
	cout << "Starting" << endl;
	int numWords = readInWords(words, maxWords,"words.txt");
	
	cout << "Read in " << numWords << " words " << endl;
	cout << "Done reading words, elapsed time = " << getTime() << endl << endl;
	
	resetTimer();
	Dictionary d(words, numWords, tableSize );
	cout << "Done creating dictionary, elapsed time = " << getTime() << endl;
	countHits(words,numWords,d);

	resetTimer();
	toFile(d, "full.txt");
	cout << "Done writing to file, elapsed time = " << getTime() << endl;
	
	findPalindromes(d,numWords);

	for (int i = 2; i <= 13; i++)
		countAnagrams(d,i,words,numWords);
	
	removalTest(d, numWords, numWords-30);
	removalTest(d, numWords, numWords);

	insertionTest(d, numWords);
	insertionTest(d, numWords);

	unScramble(d);
	cout << "Bye!" << endl;
	return 0;
}


void resetTimer() {
	tfine = clock();
}

int getTime() {
	return clock() - tfine;
}

int readInWords(string wordList[],  int maxSize, string fileName) {
    int i = 0;
	ifstream infile;
	infile.open(fileName.c_str());
	if (!infile) cout <<"Failed to open file" << endl;
    while (infile && i < maxSize) {
        string s;
        infile >> s;
        if (infile) {
            wordList[i] = s;
            i++;
        }
    }
    return i;  // the number of words read in
}

void countHits (string wordList[], int length,  Dictionary & d) {
	resetTimer();	 
	int count = 0;
	for (int i = 0; i < length; i++) 
		if (d.contains(wordList[i]) )
			count++;
	cout << "Hit count = " << count
		<< ",  elapsed time = " << getTime() << endl << endl;
}

string reverse(const string & s) {
	string t;
	for (int i = s.length()-1; i >= 0; i--)
		t.push_back(s[i]);
	return t;
}

void toFile(const Dictionary & d, const string & fileName) {
	ofstream out;
	out.open(fileName.c_str());
	out << d << endl;
	out.close();
}

void countAnagrams( Dictionary & d, int howMany, string wordList[], int length) {
	// There's a faster way of counting if we know d contains the same words
	// as wordList, but for the sake of testing we'll ignore that fact.
	resetTimer();
	int sum = 0;
	for (int i = 0; i < length; i++)  {
		AnagramSet * a = d.getSet(wordList[i]);
		if (a != NULL && a->getSize() == howMany)   
			sum++;
	}
	cout	<< "Found " << setw(5) << sum 
			<< " words with  " << setw(3) << howMany << " anagramatic forms. Elapsed time = " 
			<< getTime() << endl;
}

void findPalindromes(Dictionary & d, int numWords) {
	Dictionary pal(2000);
	cout << "Creating reversed word list...";
	for (int i = 0; i < numWords; i++) 
		reversedWords[i] = reverse(words[i]);
	cout << endl << "Counting palindromes.";
	countHits(reversedWords, numWords, d);
	cout <<  "Creating palindrome dictionary...";
	for (int i = 0; i < numWords; i++)  {
		if (d.contains(reversedWords[i])) {
			pal.insert(words[i]);
			pal.insert(reversedWords[i]);
		}
	}
	cout << "done.  " << endl;
	toFile(pal, "palindromes.txt");

	cout << endl << endl;
}

void removalTest( Dictionary & d, int numWords, int howMany) {
	resetTimer();
	for (int i = 0, j = 0; j < howMany; i  = ( i + 22079) % numWords, j++) 
			d.remove(words[i]);
	cout << endl << "Done removing " << howMany << ", elapsed time = " << getTime() << endl << endl;
	cout <<"Current dictionary = " << endl <<  d;
	countHits(words,numWords,d);


}


void insertionTest( Dictionary & d, int numWords) {
	resetTimer();
	for (int i = numWords-1; i >= 0; i--)
		d.insert(words[i]);
	cout << "Done inserting, elapsed time = " << getTime() << endl;
	countHits(words,numWords,d);

}


void unScramble(Dictionary & d) {
	string s;
	do {
		cout << "Enter an anagram or q to quit: ";
		cin >> s;
		if (s != "q") {
			AnagramSet * a = d.getSet(s);
			if (a == NULL)
				cout << "Not found " << endl;
			else
				cout << "Found it: " << *a << endl;
		}
	} while (s != "q");
}