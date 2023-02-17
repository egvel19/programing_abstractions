/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;


void findSubsets(string protein, Map<char, Set<string> >& codons, string& result, Set<string>& resultsSet){
		char c = protein[0];
		Set<string> curCodons = codons.get(c);
		int size = curCodons.size();
		for(int i=0; i<size; i++){
			result+=curCodons.first();
			curCodons.remove(curCodons.first());
			if(protein.length()>1){
				findSubsets(protein.substr(1), codons, result, resultsSet);
			}
			//base case
			if(protein.length()==1){
				resultsSet.add(result);
			}
			result = result.substr(0,result.length()-3);
		}
}

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Set<string> resultsSet;
	string res = "";
	findSubsets(protein, codons, res, resultsSet);
	foreach(string combination in resultsSet){
		cout<<combination<<endl;
	}
}

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

    /* [TODO: Implement this!] */
	string name = "KWS";
	listAllRNAStrandsFor(name, codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
