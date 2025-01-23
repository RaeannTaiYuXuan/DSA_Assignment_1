#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Actor* loadCSV(const string& filename, int& actorCount) {
    ifstream file(filename);
    actorCount = 0;

    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return nullptr;
    }

    // Count the number of lines in the file (excluding the header)
    string line;
    getline(file, line); // Skip the header line
    while (getline(file, line)) {
        actorCount++;
    }

    // Allocate memory for the array of actors
    Actor* actors = new Actor[actorCount];

    // Reset file to the beginning
    file.clear();
    file.seekg(0);

    // Skip the header line again
    getline(file, line);

    // Read the file line by line and populate the array
    int index = 0;
    while (getline(file, line) && index < actorCount) {
        istringstream ss(line);
        string temp;

        // Parse the ID
        getline(ss, temp, ',');
        actors[index].id = stoi(temp);

        // Parse the Name
        getline(ss, actors[index].name, ',');

        // Parse the Birth Year
        getline(ss, temp, ',');
        actors[index].birth = stoi(temp);

        index++;
    }

    file.close();
    return actors;
}

void displayActors(const Actor* actors, int actorCount) {
    cout << "Actors loaded from the file:\n";
    for (int i = 0; i < actorCount; i++) {
        cout << "ID: " << actors[i].id
            << ", Name: " << actors[i].name
            << ", Birth Year: " << actors[i].birth << endl;
    }
}
