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
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// Global variables
set<string> wordFounded;
bool isFindShortest = false;
int shortestLadderLength = 0;

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

	return EXIT_SUCCESS;
}

/**
 *
 * @param	startWord
 * @param	destWord
 * @param	lexicon
 */
void searchWord(string startWord, string destWord, const Lexicon & lexicon) {

	vector<string> vec { startWord };
	queue<vector<string>> wordQueue;

	wordQueue.push(vec);
	wordFounded.insert(startWord);

	bool isFindWord = false;
	bool isFindNewWord = false;
	int ladderSize = 0;
	int searchDepth = 1;

	while (!wordQueue.empty()) {
		vector<string> currWords = wordQueue.front();
		wordQueue.pop();

		/* Result ladders have been found in the previous level, stop further search. */
		if (isFindWord && currWords.size() >= ladderSize)
			break;

		/* It's going one level deeper, append the inUse with inUseCurLvl. */
//		if (searchDepth < currWords.size()) {
//			for (auto it = inUseCurLvl.begin(); it != inUseCurLvl.end(); ++it)
//				inUse.add(*it);
//			inUseCurLvl.clear();
//			++searchDepth;
//		}
	}
}

/**
 *
 */
vector<string> findOneHopWords(const Lexicon & lexicon, vector<string> & ladder,
		string destWord) {
	string word = ladder.back();
	vector<string> oneHopWords;
	vector<string> vc;
	vc.push_back(destWord);

	for (int i = 0; i < word.size(); ++i) {
		char tmp = word[i];
		for (char c = 'a'; c <= 'z'; ++c) {
			if (tmp == c)
				continue;
			word[i] = c;

			if (lexicon.containsWord(word)
					&& wordFounded.find(word) != wordFounded.end()) {
//				vector<string> newLadder = ladder;
//				newLadder.push_back(word);
				oneHopWords.push_back(word);
				if (word == destWord) {
					oneHopWords.push_back(word);
					isFindShortest = true;
					shortestLadderLength = ladder.size() + 1;
					return vc;
				}
			}

		}
	}
	return oneHopWords;
}
