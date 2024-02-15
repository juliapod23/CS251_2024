#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */
string cleanToken(string s) {
    int aCount = 0;
    string cleanTok;

    for(char x : s){ // checks how many letters in s
        if(isalpha(x)){
            aCount++;
        } 
    }

    if(aCount > 0){ // if there are letters, clean s
        int i = 0;
        int j = s.size() - 1;
    
        while(ispunct(s.at(i))){
            i++;
        }

        while(ispunct(s.at(j))){
            j--;
        }

        cleanTok = s.substr(i,j+1);

        for(char &x : cleanTok){
            x = tolower(x);
        }
    } else{ // if none, return empty string
        cleanTok = "";
    }

    return cleanTok;
}

/**
 * Returns a set of the cleaned tokens in the given text.
 */
set<string> gatherTokens(string text) {
    set<string> toks;
    istringstream my_stream(text);

    string str;

    while(my_stream >> str){
        int i = 0;
        int j = str.size() - 1;

        while (i < str.size() && !(isalpha(str[i]) || str[i] == '~')) { // creates front parameter for token
            i++; 
        }

        while (j >= 0 && !(isalpha(str[j]) || str[j] == ')')) { // creates back parameter for token
            j--;
        }

        if (i <= j) {
            toks.insert(cleanToken(str.substr(i, j - i + 1))); // inserts token based on parameters
        }
    }

    return toks;
}

/**
 * Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>>& index) {
    string url;
    string line;
    ifstream myFile(filename);

    if(!myFile.is_open()){
        cout << "Invalid file name." << endl;
        return 0;
    }

    int urlCount = 0;

    while(myFile){
        getline(myFile, url);
        if(url == ""){
            break;
        }

        getline(myFile, line);
        set<string> words = gatherTokens(line);
        urlCount++;

        for(string x : words){
            index[x].emplace(url); // feeds in urls into index
        }
    }

    return urlCount;
}

/**
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> matches;
    istringstream myFile(sentence);
    string curTok;
    
    while(myFile){
        
        set<string> placehold;
        myFile >> curTok; // feeds in query

        set<string> results = index[cleanToken(curTok)]; // cleans the user inputted query

        // based on the symbol(or no symbol), chooses correct operation
        if(curTok[0] == '+'){
            set_intersection(results.begin(), results.end(),matches.begin(), matches.end(), inserter(placehold,placehold.begin()));
        } else if(curTok[0] == '-'){
            set_difference(matches.begin(), matches.end(),results.begin(), results.end(), inserter(placehold,placehold.begin()));
        } else{
            set_union(matches.begin(), matches.end(),results.begin(), results.end(), inserter(placehold,placehold.begin()));
        }
        matches = placehold;
    }

    return matches;
}

/**
 * Runs the main command loop for the search program
 */
void searchEngine(string filename) {
    int webCount = 0;
    map<string, set<string>> index;
    
    webCount = buildIndex(filename, index);

    cout << "Stand by while building index..." << endl;

    cout << "Indexed " << webCount << " pages containing " << index.size() << " unique terms" << endl;

    while(true){
        cout << "\nEnter query sentence (press enter to quit):";
        string q;
        getline(cin,q);

        if(q.empty()){
            cout << " Thank you for searching!";
            break;
        }

        set<string> matches = findQueryMatches(index, q); // finds matching urls to user's input

        cout << " Found " << matches.size() << " matching pages" << endl;

        for(string x : matches){ // prints matching urls
            cout << x << endl;
        }
    }
}
