/**
 * Provides the implementation of the Production class, which
 * is simply a wrapper for the sequence of items (where items are terminals
 * or nonterminals).  It also completes the implementation of the ifstream
 * constructor, which was really the only thing missing from the .h
 */

#include "production.h"

/**
 * Constructor Implementation: Production
 * --------------------------------------
 * Constructor that initializes the Production based on the content of a file.
 */

Production::Production(ifstream& infile) {
	// your code here
	string str;
	while (infile >> str) {
		if (str == ";") {
			break;
		}
		phrases.push_back(str);
	}
}
