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
void findWord(const std::string& in, const std::string& floating, const std::set<std::string>& dict, 
              int index, int length, std::set<std::string>& possibleGusse );

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int length = in.size();
    // std::string inCopy = in;
	// std::string floattingCopy = floating;
	// std::set<std::string> dictCopy = dict;
    std::set<std::string> possibleGusse;
     findWord(in, floating, dict, 0, length, possibleGusse);
    return possibleGusse;
}

// Define any helper functions here
void findWord(const std::string& in, const std::string& floating, const std::set<std::string>& dict, 
              int index, int length, std::set<std::string>& possibleGusse )
{   

        if(index == in.size())
		{
			 if(dict.find(in) != dict.end() && floating.empty())
			 {
				 possibleGusse.insert(in);
			 }
			 return;
		}
    
     if (in[index - 1] != '-')
    {
        findWord(in, floating, dict, index + 1, length, possibleGusse);
        return;
    }
    
    int dashes = 0;
    for (int i = index - 1; i < length; i++)
    {
        if (in[i] == '-')
        {
            dashes++;
        }
    }
    
    if (index < floating.size())
    {
        return;
    }
    
    if (index == floating.size())
    {
        string currentIn;
        for (int i = 0; i < floating.size(); i++)
        {
            string currentFloating = floating;
            currentIn = in;
            currentIn[index - 1] = currentFloating[i];
            currentFloating.erase(currentFloating.begin() + i);
            findWord(currentIn, currentFloating, dict, index + 1, length, possibleGusse);
        }
        currentIn[index - 1] = '-';
    }
    else
    {
        std::set<char> floatCharacter;
        string currentIn;
        if (floating.size() != 0)
        {
            for (int i = 0; i < floating.size(); i++)
            {
                string currentFloating = floating;
                currentIn = in;
                currentIn[index - 1] = currentFloating[i];
                currentFloating.erase(currentFloating.begin() + i);
                floatCharacter.insert((char)(i + 97));
                findWord(currentIn, currentFloating, dict, index + 1, length, possibleGusse);
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (floatCharacter.find((char)(i + 97)) != floatCharacter.end())
            {
                continue;
            }
            else
            {
                currentIn = in;
                currentIn[index - 1] = (char)(i + 97);
                findWord(currentIn, floating, dict, index + 1, length, possibleGusse);
            }
        }
        currentIn[index - 1] = '-';
    }
}

