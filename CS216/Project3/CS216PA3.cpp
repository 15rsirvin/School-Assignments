/*
 * Course: CS216-01
 * Project: Project 3
 * Purpose: Creates a graph of actors who have appeard in movies with the files choosen by the user. (default files are provided if they just hit enter)
 *          This graph is then traversed with breadth first search to find the distance of each actor from kevin bacon via other actors they have been in movies with. 
 *          The user is then repeatecly prompted to pick actors and their "bacon number" (distanc from bacon in graph) is reported as well as the path taken via movies this 
 *          person has been in with and so on until you reach kevin bacon. The program alos tells you if this person cannot reach kevin bacon or is not in the graph.
 *    
 * Sources:       
 * Author: (Robert Irvin)
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "Graph.h"
using namespace std;

bool openFile(string userInput, ifstream* infile, string defFileName);
int nameToVertex(string input, map<string,int> nameID, map<int,int> idVert);
string vertexToName(int input, map<int,int> vertxID, map<int,string> idName);
string removeExraSpace(string input);

int main()
{   
    //1.) Intialize variables and objects. Make 3 ifstream files and add their pointers to a vector
    const int NUM_FILES = 3;
    ifstream actors,movies,actorsMovies;
    vector<ifstream *> myFiles;
    myFiles.push_back(&actors);
    myFiles.push_back(&movies);
    myFiles.push_back(&actorsMovies);

    //2.) Make Vectors of text to in for loop for user file selection
    vector<string> defaultNames = {"actors.txt","movies.txt","movie-actor.txt"};
    vector<string> userPrompts = {  "actor IDs and \nnames: ",
                                    "movie IDs and \ntitles: ",
                                    "movies IDs and actor \nID's"};

    //3.)Loop over file inputs/opening, 0 = actors, 1 = movies, 2 = movies-actors
    for(int i =0; i <NUM_FILES; i++)
    {
        cout << "Please type the name of the file which contains " << userPrompts[i]
             << "(default file name is \"" << defaultNames[i] << "\") ";

        char chrInput[256]; // use char array to get input to capture users hitting just enter
        cin.getline(chrInput,256);
        string strInput(chrInput);

        if(!openFile(chrInput, myFiles[i], defaultNames[i]))
        {
            cout << "Warning: cannot open file named " << chrInput << "!" << endl;
            return 2;
        }
    }

    //4.) Make Maps of id to actor and id to movie
    map<int,string> idActorMap;
    map<string,int> actorIDMap;
    map<int,int> idVertexMap;
    map<int,int> vertexIDMap;
    int vert = 0;
    while(!actors.eof())
    {
        string name;
        int id;
        actors >> id >> ws;
        getline(actors,name);
        if (name != "")
        {
            idActorMap[id] = name;
            actorIDMap[name] = id;
            idVertexMap[id] = vert;
            vertexIDMap[vert] = id;
            vert++;
        }
    }
    actors.close();

    map<int,string> movieMap;
    while(!movies.eof())
    {
        string name;
        int id;
        movies >> id >> ws;
        getline(movies,name);
        if (name != "")
        {
            movieMap[id] = name;
        }
    }
    movies.close();

    // 5.) Initialize Graph object
    int VERTICES_NUM = idActorMap.size();
    Graph actorConnections(VERTICES_NUM);

    //6.) Loop over Movie-Actor file building map to vectors populated with actors who were in the same movie
    map<int,vector<int>> movActorsMap;
    while(!actorsMovies.eof())
    {
        int movieID, actorID;
        actorsMovies >> movieID >> ws >> actorID >> ws;

        if( movActorsMap.count(movieID) == 0 )
        {
            vector<int> tempVEC;
            tempVEC.push_back(actorID);
            movActorsMap[movieID] = tempVEC;
        }
        else{
            movActorsMap[movieID].push_back(actorID);
        }  
    }

    //7.) Loop over map of movies and build edges between everyone in the vector for this movie. The weight is equal to the id of the movie (the key of the map)
    for(auto it = movActorsMap.begin(); it != movActorsMap.end(); it++)
    {
        for(int i = 0; i < it->second.size() - 1; i++) // create an edge between each actor with the weight = movie ID
            {
                for(int j = i+1; j < it->second.size(); j++)
                {
                    int vertActor1 = idVertexMap[it->second.at(i)];
                    int vertActor2 = idVertexMap[it->second.at(j)];
                    actorConnections.addEdge(vertActor1, vertActor2,it->first);
                }
            }
    }
    actorsMovies.close();


    // Find distances of all Actors from kevin bacon in graph using bfs
    int baconVertex = nameToVertex("Kevin Bacon", actorIDMap , idVertexMap); // finds the vertex that has kevin bacon
    vector<int> distance(VERTICES_NUM, -1);
    vector<int> go_through(VERTICES_NUM, -1);  
    actorConnections.BFS(baconVertex, distance, go_through);

    //8.) Prompt user for search.
    string baconName = "";
    while(baconName != "exit")
    {
        cout << endl << "******************************************************************* " << endl;
        cout << "The Bacon number of an actor is the number of degrees of" << endl
             << "seperation he/she has from Bacon." << endl
             << "Those actors who have worked directly with Kevin Bacon in a movie" << endl
             << "have a bacon number of 1." << endl
             << "This application helps you find the Bacon number of an actor." << endl 
             << "Enter \"exit\" to quit the program." << endl
             << "Please enter an actor's name (case sensitive): ";

        getline(cin,baconName);
        cin.clear();
        string cleanName = removeExraSpace(baconName); // Clean name using function from old lab
        int target =  nameToVertex(cleanName,actorIDMap, idVertexMap); // returns vertex of this actor or -1 if not in graph

        // 9.) proceed based on user input
        if(cleanName == "exit") // Check if user wants to exit
        {   
            //do nothing
        }
        else if(target != -1) // if in graph, report results
        {
            cout << "You are looking up the Bacon Number for " << cleanName << " :" << endl;

            if(distance.at(target) != -1)
            {
                cout << "    " << "The bacon number for " << cleanName << " is: " << distance[target] << endl;

                int currNode = target;
                while(currNode != baconVertex)
                {
                    int next = go_through.at(currNode);
                    cout << "    " << vertexToName(currNode,vertexIDMap,idActorMap) << " appeard in " << movieMap[actorConnections.getEdge(currNode,next)] 
                        << " with " << vertexToName(next, vertexIDMap, idActorMap) << endl;

                    currNode = next;
                }
            }
            else
            {
                cout << "    " << "There is no path between Kevin Bacon and " << vertexToName(target,vertexIDMap,idActorMap) << endl;
            }

        }
        else //if not in graph and user did't type exit
        {
            cout << "The actor name: " << cleanName << " does not exist!" << endl;
        }
        
            

    }

    return 0;
}


bool openFile(string userInput, ifstream* infile, string defFileName)
{
    if(userInput == "") // if default
    {
        (*infile).open(defFileName);
    }
    else
    {
        (*infile).open(userInput);
        if (!(*infile).good()) // make sure the file exists/can be opend. Quit if no
        {
            return false; 
        }
    }
    return true; 
}

int nameToVertex(string input, map<string,int> nameID, map<int,int> idVert)
{
    if(nameID.count(input) == 0)
    {
        return -1;
    }
    else
    {
        int temp = nameID[input];
        temp = idVert[temp];

        return temp;
    }
}


string vertexToName(int input, map<int,int> vertxID, map<int,string> idName)
{
    int temp = vertxID[input];
    string output = idName[temp];

    return output;
}

string removeExraSpace(string input)
{
    bool hasSpace = true;
    string original = input;
    string result;
    for (int i=0; i < original.length(); i++)
    {
        // replace tab with a blank space before parsing
        if (original[i] == '\t')
            original[i] = ' ';

        // for the space(s) before the first non-space character, remove them;
        // for the space(s) in between two non-space characters, replace with only one space
        if (original[i] != ' ')
        {
            result = result + original[i];
            hasSpace = false;
        }
        else if (!hasSpace)
        {
            result = result + original[i];
            hasSpace = true;    
        }
        else
            hasSpace = true;
    }
    return result;
}