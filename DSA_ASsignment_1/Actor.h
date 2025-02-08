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

    //========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ============
    float rating;     
    int ratingCount;
    
    Actor(int actorId, string actorName, int birthYear);
};

//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Searches for a duplicate actor ID in the AVL tree.
 * Returns true if the ID exists, otherwise returns false.
 */
bool searchDuplicateID(Actor* root, int id);


//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Wrapper function to prompt the user to enter a new actor's details.
 * Validates user input before adding the actor to the AVL tree.
 */
void addActorWrapper();


//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Inserts a new actor into the AVL tree while maintaining balance.
 * If the tree becomes unbalanced, performs necessary rotations.
 */
Actor* addActor(Actor* root, int id, const string& name, int yearOfBirth);


//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Loads actor data from a CSV file and inserts them into the AVL tree.
 * Ensures proper storage of actor details for later retrieval.
 */
void loadActorsFromCSV(const string& filename);


//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Displays all actors stored in the AVL tree using an in-order traversal.
 * Ensures actors are listed in ascending order based on their ID.
 */
void displayActors(Actor* root);

extern Actor* actorRoot; // Global pointer to the root of the Actor AVL tree



//========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ============
void rateActor(Actor* root);



//==================================== Raeann Tai Yu Xuan S10262832J - search for an actor by ID ====================================
/*
 Searches for an actor in the AVL tree by ID.
 root Pointer to the root node of the AVL tree.
 id Unique ID of the actor to search.
 Pointer to the found actor, or nullptr if not found.
 */
Actor* searchActorByID(Actor* root, int id);  


//==================================== Raeann Tai Yu Xuan S10262832J - Update Actor Details ====================================
/*
 Allows an administrator to update an actor's details.
 This function prompts for a new name and/or birth year.
 If invalid input is given, the old details are kept.
 */
void updateActorDetails();

//==================================== Raeann Tai Yu Xuan S10262832J - Update Actor Details by Age ====================================
/*
Displays actors within a specified age range in ascending order.
Performs an in-order traversal of the AVL tree to display actors
whose ages fall between x and y (inclusive).
root Pointer to the root of the AVL tree.
minAge Minimum age (x).
maxAge Maximum age (y).
 */
void displayActorsByAgeRange(Actor* root, int minAge, int maxAge);

//==================================== Raeann Tai Yu Xuan S10262832J - Update Actor Details wrapper ====================================
/*
Prompts user for an age range and displays matching actors.
This function asks the user to enter the minimum (x) and maximum (y) age values,
validates the input, and calls displayActorsByAgeRange() to show actors within
the specified range in ascending order.
 */
void displayActorsByAgeRangeWrapper();


void displayActors(Actor* root); 
