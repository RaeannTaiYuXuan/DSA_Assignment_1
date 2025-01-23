#pragma once
#include <string>
using namespace std;

struct Actor {
    int id;
    string name;
    int birth;
};

Actor* loadCSV(const string& filename, int& actorCount);
void displayActors(const Actor* actors, int actorCount);
void addActor(const string& filename);