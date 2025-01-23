#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// loadcsv --------------------------------------------------------------------------------
Actor* loadCSV(const string& filename, int& actorCount) {
    ifstream file(filename);
    actorCount = 0;

    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return nullptr;
    }

    string line;
    getline(file, line); // skip header of csv
    while (getline(file, line)) {
        actorCount++;
    }

    Actor* actors = new Actor[actorCount];

    // reset file to beginning
    file.clear();
    file.seekg(0);

    // skip the header of csv
    getline(file, line);

    // read line by line and add to array
    int index = 0;
    while (getline(file, line) && index < actorCount) {
        istringstream ss(line);
        string temp;

        // parse the ID
        getline(ss, temp, ',');
        actors[index].id = stoi(temp);

        // parse the Name
        getline(ss, actors[index].name, ',');

        // parse the Birth Year
        getline(ss, temp, ',');
        actors[index].birth = stoi(temp);

        index++;
    }

    file.close();
    return actors;
}

// display actors --------------------------------------------------------------------------------
void displayActors(const Actor* actors, int actorCount) {
    cout << "Actors loaded from the file:\n";
    for (int i = 0; i < actorCount; i++) {
        cout << "ID: " << actors[i].id
            << ", Name: " << actors[i].name
            << ", Birth Year: " << actors[i].birth << endl;
    }
}

// add actor --------------------------------------------------------------------------------
void addActor(Actor*& actors, int& actorCount) {
    cout << "\n============= Add Actor =============" << endl;

    int id, birth;
    string name;

    // user input: actor details
    cout << "Enter Actor ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Actor Name: ";
    getline(cin, name);
    cout << "Enter Actor Birth Year: ";
    cin >> birth;

    // create new array
    Actor* newActors = new Actor[actorCount + 1];

    // copy existing actors into new array
    for (int i = 0; i < actorCount; i++) {
        newActors[i] = actors[i];
    }

    // add new actor
    newActors[actorCount].id = id;
    newActors[actorCount].name = name;
    newActors[actorCount].birth = birth;

    actorCount++;

    // free old array, point to new array
    delete[] actors;
    actors = newActors;

    cout << "Actor added successfully to memory!" << endl;
}