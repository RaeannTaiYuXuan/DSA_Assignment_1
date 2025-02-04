#pragma once
#include <string>
using namespace std;

struct Movie {
	int id;
	string title;
	int year;
	Movie* left;
	Movie* right;

	float rating;
	int ratingCount;

	Movie(int movieId, const string& movieTitle, int releaseYear);
};


/**
 * Loads movie data from a CSV file and inserts them into the BST.
 * Ensures proper storage of movie details for later retrieval.
 */
void loadMoviesFromCSV(const string& filename);

//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Searches for a movie in the BST by its unique ID.
 * Returns true if the movie is found, otherwise returns false.
 */
bool searchMovieByID(Movie* root, int id);

//====================================  Tam Shi Ying s10257952 ====================================
/**
 * Displays all movies stored in the BST using an in-order traversal.
 * Ensures movies are listed in ascending order based on their ID.
 */
void displayMovies(Movie* root);


extern Movie* movieRoot; // Global pointer to the root of the Movie BST



//==================================== Raeann Tai Yu Xuan S10262832J ====================================
void addMovieWrapper();
Movie* addMovie(Movie* root, int id, const string& title, int year);


/*
 Searches for a movie in the BST by ID.
 Pointer to the root node of the BST.
 Unique ID of the movie to search.
 Pointer to the found movie, or nullptr if not found.
 */
Movie* searchMovieByIDNode(Movie* root, int id);


/**
 Allows an administrator to update a movie's details.
 This function prompts for a new title and/or release year.
 If invalid input is given, the old details are kept.
 */
void updateMovieDetails();



/*
Displays movies released in the past 3 years in ascending order.
This function performs an in-order traversal of the movie BST
and filters movies that were released within the last 3 years.
Parameters:
root: Pointer to the root of the BST.
currentYear: The current year to calculate the 3-year range.
*/
void displayMoviesByRecentYears(Movie* root, int currentYear);

//========================================================================================================



//========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ===========================================
void rateMovie(Movie* root);
void displayMovies(Movie* root); 

//========================================================================================================