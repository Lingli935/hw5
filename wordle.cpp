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
void wordleHelper(const std::string& in, const std::string& floating,
                  const std::set<std::string>& dict, int pos, int len, std::set<std::string>* words);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int length = in.size();
    std::set<std::string> wordSet;
    wordleHelper(in, floating, dict, 1, length, &wordSet);
    return wordSet;
}

// Define any helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, int pos, int len, std::set<std::string>* words)
{
    
    if (pos > len)
    {
        if (words->find(in) != words->end())
        {
            return;
        }
        
        if (floating.size() == 0)
        {
            if (dict.find(in) != dict.end())
            {
                words->insert(in);
                return;
            }
        }
        return;
    }
    
    if (in[pos - 1] != '-')
    {
        wordleHelper(in, floating, dict, pos + 1, len, words);
        return;
    }
    
    int count = 0;
    for (int i = pos - 1; i < len; i++)
    {
        if (in[i] == '-')
        {
            count += 1;
        }
    }
    
    if (count < floating.size())
    {
        return;
    }
    
    if (count == floating.size())
    {
        string newIn;
        for (int i = 0; i < floating.size(); i++)
        {
            string floatNew = floating;
            newIn = in;
            newIn[pos - 1] = floatNew[i];
            floatNew.erase(floatNew.begin() + i);
            wordleHelper(newIn, floatNew, dict, pos + 1, len, words);
        }
        newIn[pos - 1] = '-';
    }
    else
    {
        std::set<char> floatLetters;
        string newIn;
        if (floating.size() != 0)
        {
            for (int i = 0; i < floating.size(); i++)
            {
                string floatNew = floating;
                newIn = in;
                newIn[pos - 1] = floatNew[i];
                floatNew.erase(floatNew.begin() + i);
                floatLetters.insert((char)(i + 97));
                wordleHelper(newIn, floatNew, dict, pos + 1, len, words);
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (floatLetters.find((char)(i + 97)) != floatLetters.end())
            {
                continue;
            }
            else
            {
                newIn = in;
                newIn[pos - 1] = (char)(i + 97);
                wordleHelper(newIn, floating, dict, pos + 1, len, words);
            }
        }
        newIn[pos - 1] = '-';
    }
}
