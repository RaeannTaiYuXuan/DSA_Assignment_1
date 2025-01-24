#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Actor* actorRoot = nullptr;
Actor::Actor(int actorId, string actorName, int birthYear)
    : id(actorId), name(actorName), yearOfBirth(birthYear), left(nullptr), right(nullptr) {}

// load actors from csv ====================================================
void loadActorsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;

    // Skip the header line
    if (!getline(file, line)) {
        cerr << "Error: CSV file is empty or missing header." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, birthYearStr;
        if (getline(ss, idStr, ',') && getline(ss, name, ',') && getline(ss, birthYearStr)) {
            try {
                int id = stoi(idStr);
                int birthYear = stoi(birthYearStr);
                actorRoot = addActor(actorRoot, id, name, birthYear);
            }
            catch (const exception& e) {
                cerr << "Error processing line: " << line << " - " << e.what() << endl;
            }
        }
    }

    file.close();
}


// search ID ALGORITHM ====================================================
bool searchDuplicateID(Actor* root, int id) {
    while (root != nullptr) {
        if (id == root->id) {
            return true; 
        }
        if (id < root->id) {
            root = root->left; 
        }
        else {
            root = root->right; 
        }
    }
    return false; 
}

// add actor function =======================================================
Actor* addActor(Actor* root, int id, const string& name, int yearOfBirth) {
    if (root == nullptr) {
        return new Actor(id, name, yearOfBirth);
    }

    if (id == root->id) {
        cout << "Error: Duplicate ID detected during insertion. Actor not added to the tree." << endl;
        return root;
    }

    if (id < root->id) {
        root->left = addActor(root->left, id, name, yearOfBirth);
    }
    else {
        root->right = addActor(root->right, id, name, yearOfBirth);
    }

    return root;
}
void addActorWrapper() {
    int id;
    string name;
    int yearOfBirth;

    while (true) {
        cout << "Enter actor ID: ";
        cin >> id;

        if (id == 0) {
            cout << "Exiting add actor process...\n" << endl;
            return;
        }

        if (searchDuplicateID(actorRoot, id)) {
            cout << "Error: Actor with this ID already exists. Please try again." << endl;
        }
        else {
            break; 
        }
    }

    cin.ignore(); 

    while (true) {
        cout << "Enter actor name: ";
        getline(cin, name);

        if (name == "0") {
            cout << "Exiting add actor process...\n" << endl;
            return;
        }

        if (!name.empty()) {
            break; 
        }

        cout << "Error: Name cannot be empty. Please try again." << endl;
    }

    while (true) {
        cout << "Enter year of birth: ";
        cin >> yearOfBirth;

        if (yearOfBirth == 0) {
            cout << "Exiting add actor process...\n" << endl;
            return;
        }

        if (yearOfBirth > 1900 && yearOfBirth <= 2025) {
            break; 
        }

        cout << "Error: Please enter a valid year of birth (between 1900 and 2025)." << endl;
    }

    actorRoot = addActor(actorRoot, id, name, yearOfBirth);
    cout << "Actor added successfully!" << endl;
}



// display actors ====================================================
void displayActors(Actor* root) {
    if (root != nullptr) {
        displayActors(root->left);
        cout << "ID: " << root->id << ", Name: " << root->name << ", Year of Birth: " << root->yearOfBirth << endl;
        displayActors(root->right);
    }
}
