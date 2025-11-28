#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool isValid(string in, string floating, string potential);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string> results;
		set<string>::iterator it; 
		// for all words in the dict, add if valid
		for(it=dict.begin(); it!=dict.end(); ++it)
		{
			// check if right length
			if((*it).size()!=in.size()) continue;
			if(isValid(in, floating, *it)) results.insert(*it);
		}

		return results;
}

// Define any helper functions here
bool isValid(string in, string floating, string potential)
{
	// essentially maps characters in floating to an array
	// first index is the # times it appears in potential
	//  second index is the # times it should be in potential
	map<char, int[2]> yellows;
	
	// setting up initial array for all keys
	for(unsigned int i= 0; i<floating.size(); i++)
	{
		yellows[floating[i]][0] = 0;
		if (yellows[floating[i]][1] != 0) 
			yellows[floating[i]][1] = yellows[floating[i]][1]+1;
		else 
			yellows[floating[i]][1] = 1;
	}

	for(unsigned int i=0; i<potential.size(); i++)
	{
		// checking for uppercase
		if(potential[i]>='A' && potential[i]<='Z') return false;
		// green letter is not in word
		if(in[i]!='-' && potential[i]!=in[i]) return false;
		// found a yellow letter, updating first index of array
		if(floating.find(potential[i])!=-1)
				yellows[potential[i]][0] = yellows[potential[i]][0] + 1;
	}

	// checking if yellows showed up the right number of times
	map<char, int[2]>::iterator it;
	for(it=yellows.begin(); it!=yellows.end(); ++it)
		if((*it).second[0]<(*it).second[1]) return false;
	
	return true;
}