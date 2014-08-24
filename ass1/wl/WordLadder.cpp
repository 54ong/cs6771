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


using namespace std;

// Global variables
set<string> wordSet;						// Store all unique words found
vector<string> wordsInCurrentDepth;	// Store all words found under current depth
list<string> ladderList;
bool isLadderFound = false;
int shortestLadderLength = 0;

// Function declaration
void searchWord(string startWord, string destWord, Lexicon & lexicon);
vector<string> findOneHopWords(string orignWord, string destWord,
		Lexicon & lexicon);

int main() {

	string startWord, destWord;

	cout << "Enter start word (RETURN to quit): " << endl;
	cin >> startWord;
	cout << "Enter destination word: " << endl;
	cin >> destWord;

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
	wordSet.insert(startWord);

	while (!searchQueue.empty()) {
		vector<string> currWords = searchQueue.front();
		string word = *(currWords.rbegin());
		searchQueue.pop();

		if (isLadderFound && currWords.size() >= shortestLadderLength)
			break;

		// search one-hop words from the last of the currWords vector
		vector<string> oneHopWords = findOneHopWords(word, destWord, lexicon);
		for (auto iterator = oneHopWords.begin(); iterator < oneHopWords.end();
				++iterator) {
			vector<string> newWords = currWords;
			newWords.push_back(*iterator);
			// expend the
			searchQueue.push(newWords);
		}

		if (previousDepth < currWords.size()) {
			for (auto iterator = wordsInCurrentDepth.begin();
					iterator != wordsInCurrentDepth.end(); ++iterator)
				wordSet.insert(*iterator);
//			wordsInCurrentDepth.clear();
			++previousDepth;
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
vector<string> findOneHopWords(string orignWord, string destWord,
		Lexicon & lexicon) {

	vector<string> oneHopWords;

	for (int i = 0; i < orignWord.size(); ++i) {
		char tmp = orignWord[i];
		string w = orignWord;

		for (char c = 'a'; c <= 'z'; ++c) {
			if (tmp == c)
				continue;

			w[i] = c;
			// find a new word that exist in the lexicon
			if (lexicon.containsWord(w) && wordSet.find(w) == wordSet.end()) {
				wordsInCurrentDepth.push_back(w);
				oneHopWords.push_back(w);

				// matches destWord, stop and return
				if (w == destWord) {
					isLadderFound = true;
//					shortestLadderLength = ladder.size() + 1;
					return oneHopWords;
				}
			}
		}
	}
	return oneHopWords;
}
