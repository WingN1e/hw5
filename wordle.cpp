// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

#define blank '-'

// Add prototypes of helper functions here
void completeWord(string partial, string prefix, const set<string>& dict, set<string>& list, string& alphabet) {
    if(partial.length() == 0) {
        if(dict.find(prefix) != dict.end()) list.insert(prefix);
        return;
    }
    if(partial[0] == blank) {
        for(char c: alphabet) completeWord(partial.substr(1, partial.length()), prefix+c, dict, list, alphabet);
    }
    else {
        completeWord(partial.substr(1, partial.length()), prefix+partial[0], dict, list, alphabet);
    }
}

void makeWords(const string& in, set<string>& floats, set<string>& list, const set<string>& dict) {
    if(floats.empty()) return;
    string temp(in);
    string wordStruct(*(floats.begin()));
    floats.erase(wordStruct);
    string alphabet("abcdefghijklmnopqrstuvwxyz");
    for(int i = 0; i < (int)temp.length(); i++) if(temp[i] != blank) wordStruct = wordStruct.substr(0, i) + temp[i] + wordStruct.substr(i, wordStruct.length());
    completeWord(wordStruct, "", dict, list, alphabet);
    makeWords(in, floats, list, dict);
}

void swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

void permuteFloatings(string floating, set<string>& list, int start) {
    int n = floating.length() - 1;
    if(start == n) list.insert(floating);
    else {
        for(int i = start; i <= n; i++) {
            swap(floating[start], floating[i]);
            permuteFloatings(floating, list, start+1);
        }
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> list;
    set<string> wordStructs;
    int blankCount = 0;
    for(auto&c : in) if(c == blank) blankCount++;
    if(!blankCount && (dict.find(in) != dict.end())) {
        list.insert(in);
        return list;
    }
    string floatings(floating + string(blankCount-floating.length(), blank));
    permuteFloatings(floatings, wordStructs, 0);
    makeWords(in, wordStructs, list, dict);
    return list;
}

// Define any helper functions here
