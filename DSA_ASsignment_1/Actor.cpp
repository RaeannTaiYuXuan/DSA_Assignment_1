#include "Actor.h"
#include"ChangeLog.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Actor* actorRoot = nullptr;

Actor::Actor(int actorId, string actorName, int birthYear)
    : id(actorId), name(actorName), yearOfBirth(birthYear),
    height(1), left(nullptr), right(nullptr),
    rating(0.0), ratingCount(0) {  
}


/**
 * Returns the height of a given node in the AVL tree.
 * If the node is null, returns 0.
 */
int getHeight(Actor* node) {
    return node ? node->height : 0;
}


/**
 * Calculates the balance factor of a given node in the AVL tree.
 * A positive value means left-heavy, a negative value means right-heavy.
 */
int getBalanceFactor(Actor* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}


/**
 * Performs a right rotation on a given node in the AVL tree.
 * Used for balancing the tree when the left subtree is too tall.
 */
Actor* rotateRight(Actor* y) {
    Actor* x = y->left;
    Actor* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}


/**
 * Performs a left rotation on a given node in the AVL tree.
 * Used for balancing the tree when the right subtree is too tall.
 */
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
/**
 * Loads actors from a CSV file and inserts them into the AVL tree.
 * If an actor has an invalid format, an error is displayed.
 */
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


//====================================  Tam Shi Ying s10257952 - Search for duplicate ID ====================================
/**
 * Searches for a duplicate actor ID in the AVL tree.
 * Returns true if the ID exists, otherwise false.
 */
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


//====================================  Tam Shi Ying s10257952 - Add actor function ====================================
/**
 * Inserts a new actor into the AVL tree while maintaining balance.
 * Performs necessary rotations if the tree becomes unbalanced.
 */
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

void clearInputBuffer() {
    cin.clear();  
    while (cin.get() != '\n');  
}

void addActorWrapper() {
    int id;
    string name;
    int yearOfBirth;

    while (true) {
        cout << "Enter actor ID: ";

        if (!(cin >> id)) {
            cout << "Error: Invalid input. Please enter a numeric ID.\n";
            clearInputBuffer();  
            continue;
        }

        if (id == 0) {
            cout << "Exiting add actor process..." << endl;
            return;
        }

        if (searchDuplicateID(actorRoot, id)) {
            cout << "Error: Actor with this ID already exists. Please try again.\n";
        }
        else {
            break;
        }
    }

    clearInputBuffer(); 

    while (true) {
        cout << "Enter actor name: ";
        getline(cin, name);

        if (name == "0") {
            cout << "Exiting add actor process...\n";
            return;
        }

        if (!name.empty() && name.find_first_not_of(" \t") != string::npos) {
            break;
        }

        cout << "Error: Name cannot be empty or spaces only. Please try again.\n";
    }

    while (true) {
        cout << "Enter year of birth: ";

        if (!(cin >> yearOfBirth)) {
            cout << "Error: Invalid input. Please enter a valid year.\n";
            clearInputBuffer();
            continue;
        }

        if (yearOfBirth == 0) {
            cout << "Exiting add actor process...\n";
            return;
        }

        if (yearOfBirth >= 1900 && yearOfBirth <= 2025) {
            break;
        }

        cout << "Error: Please enter a valid year of birth (between 1900 and 2025).\n";
    }

    actorRoot = addActor(actorRoot, id, name, yearOfBirth);



    //NEWLY ADDED FOR DISPLAYING ONLY THE NEWLY ADDED ONE
    cout << "\nActor added successfully!\n" << endl;
    cout << "\n========= New Actor Details =========\n";
    cout << "Actor ID: " << id
        << ", Name: \"" << name
        << "\", Year of Birth: " << yearOfBirth << endl;
}



//====================================  Tam Shi Ying s10257952 - Display actors ====================================
/**
 * Displays all actors in ascending order based on their IDs.
 */
void displayActors(Actor* root) {
    if (root == nullptr) return;

    // In-order traversal (left → root → right)
    displayActors(root->left);

    // Display actor details in a clean list format
    cout << "ID: " << root->id
        << ",  Name: " << root->name
        << ",  Year of Birth: " << root->yearOfBirth
        << ",  Age: " << (2025 - root->yearOfBirth) << "\n";

    // Continue traversal
    displayActors(root->right);
}





//====================================  Raeann Tai Yu Xuan s10262832 - search for an actor by ID ====================================

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


//====================================  Raeann Tai Yu Xuan s10262832 -  function to update the actor details ====================================

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



    // Tam Shi Ying S10257952 - Additional feature (Change history & undo change) ====
    // Store the previous version before updating
    pushChange("Actor", id, actor->name, actor->yearOfBirth);
    // ===============================================================================


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


    //only displays the updated actor instead of the full list.
    cout << "\nActor details updated successfully!\n";
    cout << "========= Updated Actor Details =========\n";
    cout << "Actor ID: " << actor->id
        << ", Name: \"" << actor->name
        << "\", Year of Birth: " << actor->yearOfBirth << endl;
}

//====================================  Raeann Tai Yu Xuan s10262832 -  Function to Display Actors by Age Range ====================================

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

//====================================  Raeann Tai Yu Xuan s10262832 -  Wrapper Function to Get User Input ====================================



void countActorsByAgeRange(Actor* root, int minAge, int maxAge, int& count) {
    if (root == nullptr) return;

    // Traverse left subtree first (to maintain order)
    countActorsByAgeRange(root->left, minAge, maxAge, count);

    // Calculate actor's age
    int actorAge = 2025 - root->yearOfBirth; // Assuming the current year is 2025

    // Check if actor falls within the age range
    if (actorAge >= minAge && actorAge <= maxAge) {
        count++;
    }

    // Traverse right subtree
    countActorsByAgeRange(root->right, minAge, maxAge, count);
}

void displayActorsByAgeRangeWrapper() {
    int minAge, maxAge;

    // Prompt user for age range
    cout << "Enter minimum age (x): ";
    cin >> minAge;

    cout << "Enter maximum age (y): ";
    cin >> maxAge;

    if (minAge > maxAge) {
        cout << "Error: Minimum age cannot be greater than maximum age. Try again.\n";
        return;
    }

    int count = 0;

    // Count the number of actors within the age range
    countActorsByAgeRange(actorRoot, minAge, maxAge, count);

    cout << "\nTotal number of actors aged between " << minAge << " and " << maxAge << ": " << count << endl;

    // Prompt user if they want to see the details
    char choice;
    cout << "Would you like to see the details? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cout << "\n===== Actors Aged Between " << minAge << " and " << maxAge << " =====\n";
        displayActorsByAgeRange(actorRoot, minAge, maxAge);
    }
    else {
        cout << "Returning to menu...\n";
    }
}



//========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ============


/*
Allows a user to rate an actor.
Prompts for actor ID and rating, then updates the average rating.
 */
void rateActor(Actor* root) {
    if (root == nullptr) {  // Check if the tree is empty
        cout << "Error: No actors available to rate.\n";
        return;
    }

    int actorID;
    cout << "Enter Actor ID to rate: ";
    cin >> actorID;

    // Search for the actor by ID safely
    Actor* actor = searchActorByID(root, actorID);
    if (actor == nullptr) {
        cout << "Error: Actor with ID " << actorID << " not found.\n";
        return;
    }

    // Get rating input
    float rating;
    cout << "Enter your rating for " << actor->name << " (0 - 5): ";
    cin >> rating;

    // Validate rating
    if (rating < 0.0 || rating > 5.0) {
        cout << "Invalid rating! Please enter a value between 0 and 5.\n";
        return;
    }

    // Update average rating
    actor->rating = ((actor->rating * actor->ratingCount) + rating) / (actor->ratingCount + 1);
    actor->ratingCount++;

    // Confirm rating submission
    cout << "Rating submitted successfully for " << actor->name << "!\n";

    // Display the rated actor's updated information
    cout << "\n========= Rated Actor Details =========" << endl;
    cout << "ID:" << actor->id
        << "\nName: " << actor->name
        << "\nYear of Birth: " << actor->yearOfBirth
        << "\nRating: ";

    // Display stars based on average rating
    int fullStars = static_cast<int>(actor->rating);
    for (int i = 0; i < fullStars; ++i) {
        cout << "*";
    }
    for (int i = fullStars; i < 5; ++i) {
        cout << ".";
    }


    cout << " (" << actor->rating << "/5 from " << actor->ratingCount << " ratings)" << endl;
}



