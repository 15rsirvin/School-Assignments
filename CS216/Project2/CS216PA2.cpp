/*
 * Course: CS216-00x
 * Project: Lab 10 (as part of Project 2)
 * Purpose: repeatedly ask the user to type prefix to match
 *          then generate at maximum THREE matched terms 
 *          and display the matched terms in descending order by weight.
 ***** PLEASE DO NOT CHANGE THIS FILE *****
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv) {
    const int ARGUMENTS = 3;
    
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS)
    {
        cout << "Usage: " << argv[0] << " <filename>" << " number" << endl;
        return 1;
    }    
    
    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 2;
    }

    // Get Number of Results to be displayed and make sure it is a positive integer
    int numResults = atoi(argv[2]);

    if( numResults <= 0)
    {
        cout << "The number of matching terms needs to be a positive number!" << endl;
        return 3;
    }
      
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }    
    } 

    // Sort input file Lexographically
    autocomplete.sort();

    // Get User Search Term
    string input;
    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = input;
    while (prefix != "exit")
    {
        int currNumResults= numResults;
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        
        if (matchedTerms.size() == 0)
        {    
            cout << "No matched query!" << endl;
        }
        else
        {
            // Print Results for the specificed number of results
            cout << "Data items in the list: " << endl;

            if (currNumResults > matchedTerms.size())
                currNumResults = matchedTerms.size();

            for(size_t i = 0; i < currNumResults; i++)
            {
                cout << matchedTerms[i] << endl;
            }
        }

        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, input);
        prefix = input;
    }    
    return 0;
}

