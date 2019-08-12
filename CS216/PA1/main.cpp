/*
 * Course: CS216-01
 * Project: Project 1
 * Purpose: it reads data from an input file which passes as command line argument
 *          then stores in an object of IMDB class (to represent imdb database)
 *          it then allowes user to search for actors in either one, exclusivley one, or both movies
 *          from the user-input. Also allows User to see movies an actor is in and coactors in movie.
 *          All of these choices are made via menues until user decised to quit.
 * Author: (Robert Irvin)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <sstream>
#include "imdb.h"

using namespace std;

void analyzeMovies(const IMDB& imdb);
void analyzeCoActors(const IMDB& imdb);
void analyzeMoviesHelper(const IMDB& imdb,string movie1, string movie2);

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments is exactly one 
    if (argc != 2)
    {
        cout << "Warning: need exactly one command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[1]);

    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    }

    // Read data from the input file, assume "good data" from the input file
    // each line of the input file: actor name, movie1, movie2, ..., movien
    // read one line at a time then tokenize it:
    // create a pair <actor_name, the set of movieTitles which the actor was in>
    //        and insert to IMDB object
    IMDB cs216_imdb;

    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;
        istringstream iss(line);
        getline(iss, actorName,',');

        // Extract extra white space
        iss>>ws;

        // Create a new set of movies associated with name
        set<string> movies;

        while (getline(iss, movieTitle, ','))
        {
            movies.insert(movieTitle);
            // extract white space 
            iss>>ws;
        }
        // insert the pair to IMDB object: cs216_imdb
        cs216_imdb.insert_an_actor(actorName, movies);
    }
    // close the input file
    in_file.close();

    int option;
    while (true)
    {

        cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            string input_to_check;
            cin >> input_to_check;
            cin.ignore(256,'\n');

            if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Invalid option!" << endl;
                
                continue;
            }
        }

        cin.ignore(256, '\n');
        switch (option)
        {
            case 1: analyzeMovies(cs216_imdb);
                    break;
            case 2: analyzeCoActors(cs216_imdb);
                    break;
            default:
                    cout << "Invalid option!" << endl;
        }
        
    }
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}

// this function asks the user to input two movie titles
// then finds the matched two movies from the database
// and displays all the actors in either of the two movies
// if no matched movie then display "Invalid movie title" and do nothing
// note that using const call by reference is for efficiency purpose:
//           no copy of IMDB object is made and the argument has been protected
void analyzeMovies(const IMDB& imdb)
{
    // Ask the user to input two movie titles to search for
    string movie1, movie2;
    cout << "Please input the first movie title: ";
    getline(cin,movie1);
    cout << "Please input the second movie title: ";
    getline(cin,movie2);
    // Check if both movie1 and movies can be matched with movies in the database
    // If either one is not, quit the program
    // Otherwise display all the actors in either of two movies
    //                   which are actually the union of two sets
    string matchedMovie1, matchedMovie2;
    matchedMovie1 = imdb.matchExistingMovie(movie1);
    matchedMovie2 = imdb.matchExistingMovie(movie2);
    if ((matchedMovie1.length() > 0) && (matchedMovie2.length() > 0))
    {
        cout << "Your input matches the following two movies: " <<endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, please continue..." << endl;

        analyzeMoviesHelper(imdb, matchedMovie1, matchedMovie2);
        
    }
    else
    {
        cout << "Invalid movie title." << endl;
        return;
    }
}


// The function asks the user to type an actor's name
// then check if the user-input name is valid(it is valid if it is in the database stored in the passing in object
// if it is valid, display in each movie which this actor is in, the co-actors who appeared in the same movie
void analyzeCoActors(const IMDB& imdb)
{
    string actor_name;
    cout << "Finding the co-actors of the actor by typing his/her name: ";
    getline(cin, actor_name);
    if (!imdb.isExistingActor(actor_name))
    {
        cout << "The actor name you entered is not in the database." << endl;
        return;
    }   

    set<string> movies_of_actor;
    movies_of_actor = imdb.find_movies_for_an_actor(actor_name);
    for (auto i = movies_of_actor.begin(); i != movies_of_actor.end(); i++)
    {
        cout << "The co-actors of " << actor_name << " in the movie \"" << *i << "\" are: " << endl;
        // Display all the co-actors in one movie
        set<string> coactors = imdb.find_actors_in_a_movie(*i);
        for (auto j = coactors.begin(); j != coactors.end(); j++)
        {
                cout << *j << endl;
        }    
        cout << "***********************************" << endl;
    }
}

// The function helps analyzeMovies and takes two valid input movies and IMDB data,
// The user is then sent to a reapeted menu to print actors in both movies, either of the movies
// or exclusivly one of the movies. Quits when user enters Q or q.
void analyzeMoviesHelper(const IMDB& imdb, string movie1, string movie2)
{
    string usrInput;
    bool isDone = false;

    do
    {
        // Menu Prompt
        cout << "Please input your menu option (enter Q or q to quit)" << endl
             << "A --to print all the actors in either of the two movies." << endl
             << "C -- to print all the common actors in both of the movies." << endl
             << "O -- to print all the actors who are in one movie, but not both." << endl;

        cin >> usrInput;

        // Find actors in either movie
        if (usrInput == "a" || usrInput == "A")
        {
            set<string> all;   // to store the union of actors_in_movie1 and actors_in_movie2
            all = imdb.find_actors_in_a_movie(movie1);
            set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(movie2);
            for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
                all.insert(*i);

            // Display all the actors in either one movie
            cout << "All the actors in either of the two movies:" << endl;
            for (auto i = all.begin(); i != all.end(); i++)
                cout << *i << endl;
        }

        // Find actors in both movies
        else if (usrInput == "c" || usrInput == "C")
        {
            // Create sets.
            set<string> first, second, both;
            first = imdb.find_actors_in_a_movie(movie1);
            second = imdb.find_actors_in_a_movie(movie2);

            for (auto i = first.begin(); i != first.end(); i++)
            {
                int found;
                found = second.count(*i);
                if (found != 0) // if this item is also in the second set, add to a set of things in both
                {
                    both.insert(*i);
                }
            }

            cout << "Common actors in both movies: " << endl;
            for (auto i = both.begin(); i != both.end(); i++)
                cout << *i << endl;

        }

        // Find actors exclusivley in one of the movies
        else if (usrInput == "o" || usrInput == "O")
        {
            set<string> first, second, onlyOne;
            first = imdb.find_actors_in_a_movie(movie1);
            second = imdb.find_actors_in_a_movie(movie2);

            for (auto i = first.begin(); i != first.end(); i++) // Loop over first set and if not in second add to onlyOne
            {
                int found;
                found = second.count(*i);
                if (found == 0)
                {
                    onlyOne.insert(*i);
                }
            }

            for (auto i = second.begin(); i != second.end(); i++)// Loop over second set and if not in first and to onlyOne
            {
                int found;
                found = first.count(*i);
                if (found == 0)
                {
                    onlyOne.insert(*i);
                }
            }

            cout << "Actors only in one of the two movies: " << endl;
            for (auto i = onlyOne.begin(); i != onlyOne.end(); i++)
                cout << *i << endl;
            
        }
        else if(usrInput == "q" || usrInput == "Q")
        {
            isDone = true;
        }
        else
        {
            cout << "Invlaid option" << endl;
        }

    }while(!isDone);
}

