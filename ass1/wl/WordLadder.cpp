/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [Andrew WU]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */

#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>

using namespace std;

// Global variables
set<string> wordSet;						// Store all unique words found
vector<string> wordsInCurrentDepth;	// Store all words found under current depth
list<string> ladderList;
bool isLadderFound = false;
int shortestLadderLength = 0;

// Function declaration
void searchWord(string startWord, string destWord, Lexicon & lexicon);
vector<string> findOneHopWords(vector<string>, string, Lexicon & lexicon);

int main() {

	string startWord, destWord;

	cout << "Enter start word (RETURN to quit): ";
	cin >> startWord;
	cout << "Enter destination word: ";
	cin >> destWord;

	transform(startWord.begin(), startWord.end(), startWord.begin(), ::tolower);
	transform(destWord.begin(), destWord.end(), destWord.begin(), ::tolower);

	if (startWord.length() != destWord.length()) {
		cout << "No ladder found." << endl;
		return EXIT_FAILURE;
	}

	Lexicon lexicon("EnglishWords.dat");

	if (!lexicon.containsWord(startWord) || !lexicon.containsWord(destWord)) {
		cout << "No ladder found." << endl;
		return EXIT_FAILURE;
	}

	searchWord(startWord, destWord, lexicon);

	if (isLadderFound) {
		cout << "Found ladder: ";
		ladderList.sort();
		for (auto iter = ladderList.begin(); iter != ladderList.end(); ++iter)
			cout << *iter << endl;

	} else {
		cout << "No ladder found." << endl;
	}

	return EXIT_SUCCESS;
}

/**
 *
 * @param	startWord
 * @param	destWord
 * @param	lexicon
 */
void searchWord(string startWord, string destWord, Lexicon & lexicon) {

	int previousDepth = 1;

	queue<vector<string>> searchQueue;
	searchQueue.push( { startWord });
//	wordSet.insert(startWord);

	while (!searchQueue.empty()) {
		vector<string> currWords = searchQueue.front();
		searchQueue.pop();

		if (isLadderFound && (int) currWords.size() >= shortestLadderLength)
			break;

		if (previousDepth < (int) currWords.size()) {
			for (auto iter = wordsInCurrentDepth.begin(); iter != wordsInCurrentDepth.end();
					++iter) {
				wordSet.insert(*iter);
			}
			wordsInCurrentDepth.clear();
			++previousDepth;
		}

		// search one-hop words from the last of the currWords vector
		vector<string> oneHopWords = findOneHopWords(currWords, destWord, lexicon);
		for (auto iter = oneHopWords.begin(); iter != oneHopWords.end(); ++iter) {
			vector<string> newWords = currWords;
			newWords.push_back(*iter);
			searchQueue.push(newWords);
		}
	}

}

/**
 *
 * Find all one-hop words from given word
 *
 * @param	lexicon
 * @param	ladder
 * @param	destWord
 *
 */
vector<string> findOneHopWords(vector<string> currWords, string destWord, Lexicon & lexicon) {

	vector<string> oneHopWords;
	string orignWord = currWords.back();
	for (int i = 0; i < (int) orignWord.length(); ++i) {
		char tmp = orignWord[i];
		string w = orignWord;

		for (char c = 'a'; c <= 'z'; ++c) {
			if (tmp == c)
				continue;
			w[i] = c;
			// find new word that exist in the lexicon
			if (lexicon.containsWord(w) && wordSet.find(w) == wordSet.end()) {
				oneHopWords.push_back(w);
				if (w == destWord) {
					isLadderFound = true;
					string str;
					for (auto iter = currWords.begin(); iter != currWords.end(); ++iter)
						str += *iter + " ";
					str += w;
					ladderList.push_back(str);
					shortestLadderLength = (int) currWords.size() + 1;
					break;
				}
				wordsInCurrentDepth.push_back(w);
			}
		}
	}
	return oneHopWords;
}
