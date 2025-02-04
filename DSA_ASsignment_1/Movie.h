#pragma once
#include <string>
using namespace std;

struct Movie {
	int id;
	string title;
	int year;
	Movie* left;
	Movie* right;

	Movie(int movieId, const string& movieTitle, int releaseYear);
};

void loadMoviesFromCSV(const string& filename);
bool searchMovieByID(Movie* root, int id);
void displayMovies(Movie* root);
extern Movie* movieRoot;

//==================================== Raeann Tai Yu Xuan S10262832J ====================================
void addMovieWrapper();
Movie* addMovie(Movie* root, int id, const string& title, int year);

//==================================== Raeann Tai Yu Xuan S10262832J ====================================
/*
 Searches for a movie in the BST by ID.
 Pointer to the root node of the BST.
 Unique ID of the movie to search.
 Pointer to the found movie, or nullptr if not found.
 */
Movie* searchMovieByIDNode(Movie* root, int id);

//==================================== Raeann Tai Yu Xuan S10262832J ====================================
/**
 Allows an administrator to update a movie's details.
 This function prompts for a new title and/or release year.
 If invalid input is given, the old details are kept.
 */
void updateMovieDetails();


//==================================== Raeann Tai Yu Xuan S10262832J ====================================
/*
Displays movies released in the past 3 years in ascending order.
This function performs an in-order traversal of the movie BST
and filters movies that were released within the last 3 years.
Parameters:
root: Pointer to the root of the BST.
currentYear: The current year to calculate the 3-year range.
*/
void displayMoviesByRecentYears(Movie* root, int currentYear);

//==================================== Raeann Tai Yu Xuan S10262832J ====================================
/*
Displays movies released in the past 3 years.
This function calculates the current year and filters movies that
were released within the last 3 years using an in-order traversal.
*/
void displayMoviesByRecentYearsWrapper();



