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

