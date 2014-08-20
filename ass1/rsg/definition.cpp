/**
 * Provides the implementation of the Definition class, which is really
 * nothing more than an ordered pair: a nonterminal attached to a string.
 */

#include "definition.h"
#include "random.h"

/**
 * Constructor: Definition
 * -----------------------
 * Constructs an instance of a Definition object based on the content of the specified file.
 */

Definition::Definition(ifstream& infile) {
	string str;
	infile >> str;
	nonterminal = str;
	infile >> str;
	// here I use a less-OO way to initialize Production, a better way is to
	// init it using Production(ifstream& infile) constructor
	while (str != "}") {
		vector<string> words;
		while (str != ";") {
			words.push_back(str);
			infile >> str;
		}
		infile >> str;

		Production prod(words);
		possibleExpansions.push_back(prod);
	}

//	cout << "non-terminal name: " << nonterminal << endl << "Productions: "
//			<< endl;
//	for (auto it = possibleExpansions.begin(); it < possibleExpansions.end();
//			++it) {
//		for (auto iterator = it->begin(); iterator < it->end(); ++iterator)
//			cout << *iterator << " ";
//		cout << endl;
//	}
//	cout << endl;
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the embedded Productions.
 */

const Production& Definition::getRandomProduction() const {

	RandomGenerator rand = RandomGenerator();
	int i = rand.getRandomInteger(0, possibleExpansions.size() - 1);
	return possibleExpansions[i];
//	return *(new Production()); // bogus
}
