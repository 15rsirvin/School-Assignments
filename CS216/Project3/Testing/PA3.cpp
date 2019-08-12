#include <iostream>
#include <vector>
#include "Graph.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

bool openFile(string userInput, ifstream& infile, string defFileName);

int main()
{   
    const int NUM_FILES = 3;
    ifstream actorsFile,moviesFile,actorsMoviesFile;
    char input1[256],input2[256],input3[256];

    //1.) Open File for actors
    cout << "Please type the name of the file which contains actor IDs and" << endl
         << "names: (default file name is \"actors.txt\")"; 
    cin.getline(input1,256);
    string strInput1(input1);

    if(strInput1 == "")
    {
        actorsFile.open("actors.txt");
    }
    else
    {
        actorsFile.open(strInput1);
        if(!actorsFile.good())
        {
                return 2;
        }
    }
    

    //2.) Open File for Movies
    cout << "Please type the name of the file which contains movie IDs and" << endl
         << "titles: (default file name is \"movies.txt\")"; 
    cin.getline(input2,256);
    string strInput2(input2);

    if(strInput2 == "")
    {
        actorsFile.open("movies.txt");
    }
    else
    {
        moviesFile.open(strInput2);
        if(!moviesFile.good())
        {
                return 2;
        }
    }

    //3.) Open File for actors-movies
    cout << "Please type the name of the file which contains movie IDs and actor" << endl
         << "IDs: (default file name is \"movie-actor.txt\")"; 
    cin.getline(input3,256);
    string strInput3(input3);

    if(strInput3 == "")
    {
        actorsMoviesFile.open("movies-actor.txt");
    }
    else
    {
        actorsMoviesFile.open(strInput1);
        if(!actorsMoviesFile.good())
        {
                return 2;
        }
    }

    while(!actorsFile.eof()){
        string  a,b,c;
        actorsFile >> a >> b >>c;
        cout << a <<b <<c;
    }

    return 0;
}


bool openFile(string userInput, ifstream& infile, string defFileName)
{
    if(userInput == "") // if default
    {
        infile.open(defFileName);
    }
    else
    {
        infile.open(userInput);
        if (!infile.good()) // make sure the file exists/can be opend. Quit if no
        {
            return false; 
        }
    }
    return true; 
}