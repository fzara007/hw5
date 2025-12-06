#ifndef RECCHECK
// For debugging
// #include <iostream>
// For std::remove
#include <algorithm>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// int counter;

// Add prototypes of helper functions here
void wordleHelper(
			string& in, size_t index, int yellows[26], size_t numYellows, 
			set<string>& words, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string> possibleWords; 
		// array for how many times a letter is in floating
		int yellows[26] = {0};
		for(char c : floating) yellows[c-'a']++;
		string word = in;
		wordleHelper(word, 0, yellows, floating.size(), possibleWords, dict);
		return possibleWords;
}

// Define any helper functions here
void wordleHelper(
			string& in, size_t index, int yellows[26], size_t numYellows, 
			set<string>& words, const set<string>& dict)
{
	// base cases
	if(index==in.size())
	{
		// word is in dictionary and have the yellow chars
		if(numYellows==0 && dict.find(in)!=dict.end()) 
				words.insert(in);
		return;
	}
	// there are more yellows than spaces 
	if(numYellows>in.size()-index) return;

  // found a green letter, move on
	if(in[index]!='-') return wordleHelper(in, index+1, yellows, numYellows, words, dict);

	// going through all the letters for this index
	for(int let=0; let<26; let++)
	{
		// setting the bool for if this is a yellow letter
		bool found = yellows[let]>0;
		if(found) 
		{
			// decreasing count for total yellows, and in the array
			yellows[let]--;
			numYellows--;
		}
		
		// inserting it to in to keep trying combos
		in[index] = (char)('a'+let);
		
		wordleHelper(in, index + 1, yellows, numYellows, words, dict);
		
		// combos failed, resetting changed vals
		if(found)
		{
			numYellows++;
			yellows[let]++;
		}
		
	}
	// resorting to original char 		
	in[index] = '-';
}