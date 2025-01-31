#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Actor* actorRoot = nullptr;

Actor::Actor(int actorId, string actorName, int birthYear)
    : id(actorId), name(actorName), yearOfBirth(birthYear), height(1), left(nullptr), right(nullptr) {}

int getHeight(Actor* node) {
    return node ? node->height : 0;
}

int getBalanceFactor(Actor* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Actor* rotateRight(Actor* y) {
    Actor* x = y->left;
    Actor* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Actor* rotateLeft(Actor* x) {
    Actor* y = x->right;
    Actor* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// load actors from csv ====================================================
void loadActorsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;

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


// search for duplicate ID ALGORITHM ====================================================
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

    if (id < root->id) {
        root->left = addActor(root->left, id, name, yearOfBirth);
    }
    else if (id > root->id) {
        root->right = addActor(root->right, id, name, yearOfBirth);
    }
    else {
        cout << "Error: Duplicate ID detected during insertion. Actor not added to the tree." << endl;
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && id < root->left->id) {
        return rotateRight(root);
    }

    if (balance < -1 && id > root->right->id) {
        return rotateLeft(root);
    }

    if (balance > 1 && id > root->left->id) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && id < root->right->id) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void addActorWrapper() {
    int id;
    string name;
    int yearOfBirth;

    while (true) {
        cout << "Enter actor ID (or 0 to exit): ";
        cin >> id;
        if (id == 0) {
            cout << "Exiting add actor process..." << endl;
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


//==================================== raeann s10262832 - search for an actor by ID ====================================

/**
 Searches for an actor in the AVL tree by ID.
 root Pointer to the root of the AVL tree.
 The actor's unique ID to search for.
 Pointer to the actor if found, otherwise nullptr.
 */

Actor* searchActorByID(Actor* root, int id) {
    if (root == nullptr || root->id == id) {
        return root; // Found the actor or reached a null node
    }

    if (id < root->id) {
        return searchActorByID(root->left, id);
    }
    else {
        return searchActorByID(root->right, id);
    }
}

//==================================== raeann s10262832 -  function to update the actor details ====================================

/**
 Updates the details of an existing actor.
 This function prompts the user for a new name and/or year of birth.
 If the user enters a blank name or invalid birth year, the previous values remain unchanged.
 */

void updateActorDetails() {
    int id;
    cout << "Enter actor ID to update: ";
    cin >> id;

    Actor* actor = searchActorByID(actorRoot, id);
    if (actor == nullptr) {
        cout << "Error: Actor with ID " << id << " not found.\n";
        return;
    }

    string newName;
    int newYearOfBirth;

    cin.ignore();
    cout << "Enter new name (leave blank to keep unchanged): ";
    getline(cin, newName);

    if (!newName.empty()) {
        actor->name = newName;
    }

    cout << "Enter new year of birth (or 0 to keep unchanged): ";
    cin >> newYearOfBirth;

    if (newYearOfBirth >= 1900 && newYearOfBirth <= 2025) {
        actor->yearOfBirth = newYearOfBirth;
    }
    else if (newYearOfBirth != 0) {
        cout << "Invalid year! Keeping previous value.\n";
    }

    cout << "Actor details updated successfully!\n";
}

//==================================== raeann s10262832 -  Function to Display Actors by Age Range ====================================

/*
Displays actors within a specified age range in ascending order.
Performs an in-order traversal of the AVL tree to display actors
whose ages fall between x and y (inclusive).
Pointer to the root of the AVL tree.
minAge Minimum age (x).
maxAge Maximum age (y).
 */

void displayActorsByAgeRange(Actor* root, int minAge, int maxAge) {
    if (root == nullptr) return;

    // Traverse left subtree first (to maintain ascending order)
    displayActorsByAgeRange(root->left, minAge, maxAge);

    // Calculate actor's age
    int actorAge = 2025 - root->yearOfBirth; // Assuming current year is 2025

    // Check if actor falls within the age range
    if (actorAge >= minAge && actorAge <= maxAge) {
        cout << "ID: " << root->id << ", Name: " << root->name
            << ", Age: " << actorAge << ", Year of Birth: " << root->yearOfBirth << endl;
    }

    // Traverse right subtree
    displayActorsByAgeRange(root->right, minAge, maxAge);
}

//==================================== raeann s10262832 -  Wrapper Function to Get User Input ====================================

/*
Prompts user for an age range and displays matching actors.
This function asks the user to enter the minimum (x) and maximum (y) age values,
validates the input, and calls displayActorsByAgeRange() to show actors within
the specified range in ascending order.
 */

void displayActorsByAgeRangeWrapper() {
    int minAge, maxAge;

    cout << "Enter minimum age (x): ";
    cin >> minAge;

    cout << "Enter maximum age (y): ";
    cin >> maxAge;

    if (minAge > maxAge) {
        cout << "Error: Minimum age cannot be greater than maximum age. Try again.\n";
        return;
    }

    cout << "\n===== Actors Aged Between " << minAge << " and " << maxAge << " =====\n";
    displayActorsByAgeRange(actorRoot, minAge, maxAge);
}
