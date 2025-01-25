#include "Movie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

Movie* movieRoot = nullptr;

Movie::Movie(int movieId, const string& movieTitle, int releaseYear)
    : id(movieId), title(movieTitle), year(releaseYear), left(nullptr), right(nullptr) {}


void loadMoviesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;

    // skip header line
    if (!getline(file, line)) {
        cerr << "Error: CSV file is empty or missing header." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, yearStr;

        if (getline(ss, idStr, ',') && getline(ss, title, ',') && getline(ss, yearStr)) {
            try {
                int id = stoi(idStr);
                int year = stoi(yearStr);

                Movie** current = &movieRoot;

                while (*current != nullptr) {
                    if (id < (*current)->id) {
                        current = &(*current)->left;
                    }
                    else if (id > (*current)->id) {
                        current = &(*current)->right;
                    }
                    else {
                        cerr << "Error: Duplicate movie ID detected. Skipping movie: " << id << endl;
                        break;
                    }
                }

                if (*current == nullptr) {
                    *current = new Movie(id, title, year);
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Invalid data in CSV line: " << line << " (" << e.what() << ")" << endl;
            }
            catch (const out_of_range& e) {
                cerr << "Out of range data in CSV line: " << line << " (" << e.what() << ")" << endl;
            }
        }
        else {
            cerr << "Malformed line in CSV: " << line << endl;
        }
    }

    file.close();
}


bool searchMovieByID(Movie* root, int id) {
    if (root == nullptr) {
        return false;
    }

    if (root->id == id) {
        return true;
    }
    else if (id < root->id) {
        return searchMovieByID(root->left, id);
    }
    else {
        return searchMovieByID(root->right, id);
    }
}

void displayMovies(Movie* root) {
    if (root != nullptr) {
        displayMovies(root->left);
        cout << "Movie ID: " << root->id << ", Title: " << root->title << ", Year: " << root->year << endl;
        displayMovies(root->right);
    }
}