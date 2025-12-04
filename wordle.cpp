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
		// vector<char> yellows(floating.begin(), floating.end());
		int yellows[26] = {0};
		for(char c : floating) yellows[c-'a']++;
		string word = in;
		wordleHelper(word, 0, yellows, floating.size(), possibleWords, dict);
		// std::cout << "counter: " << counter << std::endl;
		return possibleWords;
}

// Define any helper functions here
void wordleHelper(
			string& in, size_t index, int yellows[26], size_t numYellows, 
			set<string>& words, const set<string>& dict)
{
	// counter++;
	// base cases
	// if(in.size()==0) return;
	if(index==in.size())
	{
		// word is in dictionary and have the yellow chars
		// if(dict.find(in)!=dict.end() && yellows.empty())
		if(numYellows==0 && dict.find(in)!=dict.end()) 
				words.insert(in);
		return;
	}

	// if(yellows.size()>in.size()-index) return;
	if(numYellows>in.size()-index) return;

	if(in[index]!='-') return wordleHelper(in, index+1, yellows, numYellows, words, dict);

	// going through all the letters for this index
	for(int let=0; let<26; let++)
	{
		// // setting the bool for if this is a yellow letter
		// vector<char>::iterator it = find(yellows.begin(), yellows.end(), ('a'+let));
		// bool found = it != yellows.end();
		// // removing it from the vector for the base case check
		// if(found) yellows.erase(it);

		// bool found = yellows[let]!=0;
		yellows[let]--;
		bool found = yellows[let]>=0;
		if(found) 
		{
			numYellows--;
		}
		

		// inserting it to in to keep trying combos
		in[index] = (char)('a'+let);

		if(numYellows<=in.size()-index-1)
			wordleHelper(in, index + 1, yellows, numYellows, words, dict);
		
		// combos failed, resetting changed vals
		// if(found) yellows.push_back('a'+let);
		if(found)
		{
			numYellows++;
		}
		yellows[let]++;

		
	}
	// resorting to original char 		
	in[index] = '-';
}