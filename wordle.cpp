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
void findWord(int index,string& in, int dashes, std::string& floating, const std::set<std::string>& dict,
const std::string& seeds, std::set<std::string>& possibleGusse);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::string current = in;
		std::string floattingCopy = floating;
		std::set<std::string> dictCopy = dict;
    std::set<std::string> word;
		std::set<std::string> possibleGusse;

    int dashes;
			for(int i = 0;i < in.size();i++)
			{
					if(in[i] == '-')
					dashes++;
			}
		std::string seeds = "abcdefghijklmnopqrstuvwxyz";
    findWord(0,current,dashes, floattingCopy, dictCopy, seeds, possibleGusse);
    return possibleGusse;
}

// Define any helper functions here
void findWord(int index,string& in, int dashes, std::string& floating, const std::set<std::string>& dict,
const std::string& seeds, std::set<std::string>& possibleGusse)
{
    
		if(index == in.size())
		{
			 if(dict.find(in) != dict.end() && floating.empty())
			 {
				 possibleGusse.insert(in);
			 }
			 return;
		}
		if(dashes < floating.size())
		{
			return;
		}
		if (in[index] != '-'){
			findWord(index+1, in, dashes, floating, dict, seeds, possibleGusse);
			return;
		}
		// TODO: for loop over floats if dashes == floats.size() 
		// instead of looping over alphabet
		// if dashes == floaiting
		  // loop through floating
				// remove that letter from floating
				// recurse
				// add letter back
			// return
      
	
			char letter;
			if(dashes == floating.size())
			{
				// loop i over 0->size float
				std::string float_copy = floating;
				std::string used;
				for(int i = 0;i <floating.size();i++)
				{
					letter = floating[i];
					if (used.find(letter) == std::string::npos){
						used.push_back(letter);
						in[index] = letter;
						floating.erase(i, 1);
						findWord(index+1, in, dashes - 1, floating, dict, seeds, possibleGusse);
						floating = float_copy;
					}
				}
				in[index] = '-';
        return;
			}

    //have if statement for check for if you have more  -- than floating cha 

		for(int i = 0; i < seeds.size(); i++)
		{
			char letter = seeds[i];
			in[index] = seeds[i];
				size_t f_index = floating.find(in[index]);
				if(f_index != std::string::npos)
				{
					floating.erase(f_index, 1);
					findWord(index+1, in, dashes - 1, floating, dict, seeds, possibleGusse);
					floating.push_back(letter);
				}
				else
				{
					findWord(index+1, in, dashes - 1, floating, dict, seeds, possibleGusse);
				}
				// set in[index] back to "-"
				in[index] = '-';
			}
}
