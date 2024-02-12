#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

/**
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */
string cleanToken(string s) {
    // TODO_STUDENT
    return "";
}

/**
 * Returns a set of the cleaned tokens in the given text.
 */
set<string> gatherTokens(string text) {
    // TODO_STUDENT
    return {};
}

/**
 * Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>>& index) {
    // TODO_STUDENT
    return 0;
}

/**
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    // TODO_STUDENT
    return {};
}

/**
 * Runs the main command loop for the search program
 */
void searchEngine(string filename) {
    // TODO_STUDENT
}
