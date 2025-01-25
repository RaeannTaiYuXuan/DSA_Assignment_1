#pragma once
#include <string>
using namespace std;

struct Actor {
    int id;
    string name;
    int yearOfBirth;
    int height;
    Actor* left;
    Actor* right;

    Actor(int actorId, string actorName, int birthYear);
};

bool searchDuplicateID(Actor* root, int id);
void addActorWrapper();
Actor* addActor(Actor* root, int id, const string& name, int yearOfBirth);
void loadActorsFromCSV(const string& filename);
void displayActors(Actor* root);

extern Actor* actorRoot;  