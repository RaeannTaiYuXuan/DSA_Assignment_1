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


//==================================== Raeann Tai Yu Xuan S10262832J -  ====================================
//this is the BSL tree ( binary search tree)

Movie* addMovie(Movie* root, int id, const string& title, int year) {
    if (root == nullptr) {
        return new Movie(id, title, year);
    }

    if (id < root->id) {
        root->left = addMovie(root->left, id, title, year);
    }
    else if (id > root->id) {
        root->right = addMovie(root->right, id, title, year);
    }
    else {
        cout << "Error: Movie with ID " << id << " already exists.\n";
    }

    return root;
}



//==================================== Raeann Tai Yu Xuan S10262832J -  ====================================
void addMovieWrapper() {
    int id, year;
    string title;

    while (true) {
        cout << "Enter movie ID (or 0 to cancel): ";
        cin >> id;
        if (id == 0) {
            cout << "Movie addition canceled.\n";
            return;
        }

        if (searchMovieByID(movieRoot, id)) {
            cout << "Error: Movie with this ID already exists. Try again.\n";
        }
        else {
            break;
        }
    }

    cin.ignore();
    while (true) {
        cout << "Enter movie title: ";
        getline(cin, title);
        if (!title.empty()) {
            break;
        }
        cout << "Error: Title cannot be empty. Try again.\n";
    }

    while (true) {
        cout << "Enter year of release: ";
        cin >> year;
        if (year >= 1900 && year <= 2025) {
            break;
        }
        cout << "Error: Please enter a valid year between 1900 and 2025.\n";
    }

    movieRoot = addMovie(movieRoot, id, title, year);
    cout << "Movie added successfully!\n";
}

//==================================== Raeann Tai Yu Xuan S10262832J - Search for a Movie by ID  ====================================

/*
Searches for a movie in the BST by ID.
Pointer to the root node of the BST.
Unique ID of the movie to search.
Pointer to the found movie, or nullptr if not found.
 */
Movie* searchMovieByIDNode(Movie* root, int id) {
    if (root == nullptr || root->id == id) {
        return root; // Found the movie or reached a null node
    }

    if (id < root->id) {
        return searchMovieByIDNode(root->left, id);
    }
    else {
        return searchMovieByIDNode(root->right, id);
    }
}

//==================================== Raeann Tai Yu Xuan S10262832J - Function to Update Movie Details ====================================

/*
Updates the details of an existing movie.
This function prompts the user for a new title and/or release year.
If the user enters a blank title or invalid release year, the previous values remain unchanged.
 */
void updateMovieDetails() {
    int id;
    cout << "Enter movie ID to update: ";
    cin >> id;

    Movie* movie = searchMovieByIDNode(movieRoot, id);
    if (movie == nullptr) {
        cout << "Error: Movie with ID " << id << " not found.\n";
        return;
    }

    string newTitle;
    int newYear;

    cin.ignore();
    cout << "Enter new title (leave blank to keep unchanged): ";
    getline(cin, newTitle);

    if (!newTitle.empty()) {
        movie->title = newTitle;
    }

    cout << "Enter new release year (or 0 to keep unchanged): ";
    cin >> newYear;

    if (newYear >= 1900 && newYear <= 2025) {
        movie->year = newYear;
    }
    else if (newYear != 0) {
        cout << "Invalid year! Keeping previous value.\n";
    }

    cout << "Movie details updated successfully!\n";
}

//==================================== Raeann Tai Yu Xuan S10262832J - Function to Display Movies from the Last 3 Years ====================================

/*
Displays movies released in the past 3 years in ascending order.
This function performs an in-order traversal of the movie BST
and filters movies that were released within the last 3 years.
Pointer to the root of the BST.
currentYear The current year to calculate the 3-year range.
 */
void displayMoviesByRecentYears(Movie* root, int currentYear) {
    if (root == nullptr) return;

    // Traverse left subtree first (to maintain ascending order)
    displayMoviesByRecentYears(root->left, currentYear);

    // Check if the movie was released within the last 3 years
    if (root->year >= (currentYear - 3)) {
        cout << "Movie ID: " << root->id << ", Title: " << root->title
            << ", Year: " << root->year << endl;
    }

    // Traverse right subtree
    displayMoviesByRecentYears(root->right, currentYear);
}

//==================================== Raeann Tai Yu Xuan S10262832J - Wrapper Function to Call Filtering Logic ====================================

/*
Displays movies released in the past 3 years.
This function calculates the current year and filters movies that
were released within the last 3 years using an in-order traversal.
*/
void displayMoviesByRecentYears(Movie* root, int currentYear) {
    if (root == nullptr) return;

    // Traverse left subtree first (to maintain ascending order)
    displayMoviesByRecentYears(root->left, currentYear);

    // Correct filtering: Only show movies from the past 3 years
    if (root->year >= (currentYear - 3) && root->year <= currentYear) {
        cout << "Movie ID: " << root->id << ", Title: \"" << root->title
            << "\", Year: " << root->year << endl;
    }

    // Traverse right subtree
    displayMoviesByRecentYears(root->right, currentYear);
}