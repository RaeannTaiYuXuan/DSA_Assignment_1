#pragma once
#include <string>
using namespace std;

// Struct to represent an actor
struct Actor {
    int id;
    string name;
    int birth;
};

// Function to load actors from a CSV file into a dynamically allocated array
Actor* loadCSV(const string& filename, int& actorCount);
void displayActors(const Actor* actors, int actorCount);
