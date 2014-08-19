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
	// your code here
	string str;
	infile >> str;
	nonterminal = str;
	while (str != "}") {
		vector<string> words;
		while (infile >> str) {
			if (str != ";") {
				words.push_back(str);
			} else
				break;
		}
		Production prod(words);
		possibleExpansions.push_back(prod);
	}

	cout << endl;
	cout << "non-terminal name: " << nonterminal << endl << "Productions: "
			<< endl;
	for (auto it = possibleExpansions.begin(); it < possibleExpansions.end();
			++it) {
		for (auto iterator = it->begin(); iterator < it->end(); ++iterator)
			cout << *iterator << " ";
		cout << endl;
	}
}

/**
 * Method: getRandomProduction
 * ---------------------------
 * Returns a const reference to one of the embedded Productions.
 */

const Production& Definition::getRandomProduction() const {
	// your code here
	return *(new Production()); // bogus
}
