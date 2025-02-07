#pragma once
#include <string>
using namespace std;

const int MAX_CAST_SIZE = 1000;

struct Movie;  
struct Actor;

struct Cast {
	int person_id;
	int movie_id;
	Cast* next;

	Cast(int personId, int movieId);
};

//====================================  Tam Shi Ying s10257952 ====================================

/**
 * Loads cast data from a CSV file and inserts them into the linked list.
 * Ensures proper storage of actor-movie relationships for later retrieval.
 */
void loadCastsFromCSV(const string& filename);


/**
 * Inserts a new actor-movie pair into the linked list while maintaining sorted order.
 * Prevents duplicate entries from being added.
 */
bool addCastSorted(Cast*& head, int personId, int movieId);

/**
 * Displays all actor-movie relationships stored in the linked list.
 * Prints each actor and the corresponding movie they are associated with.
 */
void displayCasts();

/**
 * Allows an administrator to link an actor to a movie through user input.
 * Ensures both the actor and the movie exist before adding the cast entry.
 */
void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot);

/**
 * Checks whether a specific actor-movie pair exists in the linked list.
 * Returns true if the pair is found, otherwise returns false.
 */
bool doesCastExist(int personId, int movieId);

/**
 * Displays all movies that a given actor has appeared in.
 * Uses the cast list to find and print the actor's filmography.
 */
void displayMoviesByActor(Cast* castHead, Movie* movieRoot, Actor* actorRoot);

/**
 * Displays all actors who have appeared in a given movie.
 * Uses the cast list to find and print the actors for the specified movie.
 */
void displayActorsByMovie(Cast* castHead, Movie* movieRoot, Actor* actorRoot);


/**
 * Displays actors who have worked with a given actor.
 * Finds actors who have appeared in the same movies and prints them.
 */
void displayKnownActors(Cast* castHead, Actor* actorRoot);


/**
 * Performs a binary search on the cast index to find a specific actor-movie pairing.
 * Returns a pointer to the cast entry if found, otherwise returns nullptr.
 */
Cast* binarySearchCast(int personId, int movieId);

/**
 * Builds an indexed array for fast searching of cast members.
 * Optimizes the searching process by sorting cast entries in an array.
 */
void buildCastIndex(Cast* head);


// Global variables for cast storage
extern Cast* castHead;                      // Head of the cast linked list
extern Cast* castIndex[MAX_CAST_SIZE];      // Indexed array for fast searching
extern int castCount;                       // Count of cast entries in the index




