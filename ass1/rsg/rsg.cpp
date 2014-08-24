/**
 * Provides the implementation of the full RSG application, which
 * relies on the services of the built-in string, ifstream, vector,
 * and map classes as well as the custom Production and Definition
 * classes provided with the assignment.
 */

#include <map>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "definition.h"
#include "production.h"

using namespace std;

/**
 * Takes a reference to a legitimate infile (one that's been set up
 * to layer over a file) and populates the grammar map with the
 * collection of definitions that are spelled out in the referenced
 * file. 
 *
 * @param infile  a valid reference to a flat text file storing the grammar.
 * @param grammar a reference to the STL map, which maps nonterminal strings
 *                to their definitions.
 */

static void readGrammar(ifstream& infile, map<string, Definition>& grammar) {

	string str;

	while (infile >> str) {
		// skip all junks before the CFG
		if (str == "{") {
			Definition def(infile);
			grammar.insert(pair<string, Definition>(def.getNonterminal(), def));
		}
	}
}

static void expendProduction(Production& production,
		const map<string, Definition>& grammar) {

	for (auto iterator = production.begin(); iterator < production.end();
			++iterator) {
		string str = *iterator;

		if (str.find('<') == std::string::npos) {
			cout << str << " ";
		} else {
			Definition def = grammar.at(str);
			Production prod = def.getRandomProduction();
			expendProduction(prod, grammar);
		}
	}
}

/**
 * Takes a const reference to a grammar stored in a map and prints
 * sentences produced by applying the grammar rules. The number of
 * sentences should be as specified by the second parameter.
 *
 * @param grammar            a reference to the STL map, which maps nonterminal
 *                           strings to their definitions.
 * @param numSentencesNeeded number of sentences to be produced
 */

static void generateRandomSentences(const map<string, Definition>& grammar,
		int numSentencesNeeded) {
	for (int i = 0; i < numSentencesNeeded; ++i) {
		Definition defin = grammar.at("<start>");

		Production prod = defin.getRandomProduction();
		expendProduction(prod, grammar);
		cout << endl;
	}
}

/**
 * Performs the rudimentary error checking needed to confirm that
 * the client provided a grammar file.  It then continues to
 * open the file, read the grammar into a map<string, Definition>,
 * and then print out the random expansions as required.
 *
 * @param argc the number of tokens making up the command that invoked
 *             the RSG executable.  There must be at least two arguments,
 *             and only the first two are used.
 * @param argv the sequence of tokens making up the command, where each
 *             token is represented as a '\0'-terminated C string.
 */

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cerr << "You need to specify the name of a grammar file." << endl;
		cerr << "Usage: rsg <path to grammar text file>" << endl;
		return EXIT_FAILURE;
	}

	ifstream grammarFile(argv[1]);
	if (grammarFile.fail()) {
		cerr << "Failed to open the file named \"" << argv[1] << "\". "
				"Check to ensure the file exists." << endl;
		return EXIT_FAILURE;
	}

// things are looking good...
	map<string, Definition> grammar;
	readGrammar(grammarFile, grammar);
	generateRandomSentences(grammar, 3);

	return EXIT_SUCCESS;
}
