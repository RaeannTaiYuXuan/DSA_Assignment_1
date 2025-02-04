#include "Movie.h"
#include "ChangeLog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

Movie* movieRoot = nullptr;

Movie::Movie(int movieId, const string& movieTitle, int releaseYear)
    : id(movieId), title(movieTitle), year(releaseYear),
    rating(0.0), ratingCount(0),  // Initialize rating and rating count
    left(nullptr), right(nullptr) {
}


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

//====================================  Tam Shi Ying s10257952 - search movie by ID ====================================
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


//====================================  Tam Shi Ying s10257952 - Display movies ====================================
void displayMovies(Movie* root) {
    if (root != nullptr) {
        displayMovies(root->left);
        cout << "ID: " << root->id << ", Title: " << root->title
            << ", Year: " << root->year
            << ", Rating: " << (root->ratingCount > 0 ? to_string(root->rating) : "No ratings yet")
            << endl;
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

    // Get Movie ID
    while (true) {
        cout << "Enter movie ID (or 0 to cancel): ";
        if (!(cin >> id)) {  // Check if input is valid
            cout << "Invalid input, try again.\n";
            cin.clear();                // Clear the error flag
            cin.ignore(1000, '\n');     // Clear any invalid input
            continue;
        }

        if (id == 0) {
            cout << "Movie addition canceled.\n";
            return;
        }

        if (searchMovieByID(movieRoot, id)) {
            cout << "Error: Movie with this ID already exists. Try again.\n";
        } else {
            cin.ignore(1000, '\n');  // Clear newline after valid numeric input
            break;
        }
    }

    // Get Movie Title
    while (true) {
        cout << "Enter movie title: ";
        getline(cin, title);  // Read the entire line including spaces
        if (!title.empty() && title.find_first_not_of(' ') != string::npos) { 
            break;  // Title is valid if it's not just spaces
        }
        cout << "Error: Title cannot be empty. Try again.\n";
    }

    // Get Year of Release
    while (true) {
        cout << "Enter year of release: ";
        if (!(cin >> year)) {  // Validate numeric input
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');  // Clear any invalid input
            continue;
        }

        if (year >= 1900 && year <= 2025) {
            break;
        }
        cout << "Error: Please enter a valid year between 1900 and 2025.\n";
    }

    // Add the Movie
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

    // Tam Shi Ying S10257952 - Additional feature (Change history & undo change) ====
// Store the previous version before updating
    pushChange("Movie", id, movie->title, movie->year);
    // ===============================================================================

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
    if (root == nullptr) {
        return;  // Base case: if the node is null, exit the function
    }

    // Traverse the left subtree (smaller years)
    displayMoviesByRecentYears(root->left, currentYear);

    // Check if the movie's year is within the last 3 years
    if (root->year >= currentYear - 3 && root->year <= currentYear) {
        cout << "Movie ID: " << root->id 
             << ", Title: \"" << root->title 
             << "\", Year: " << root->year << endl;
    }

    // Traverse the right subtree (larger years)
    displayMoviesByRecentYears(root->right, currentYear);
}



//========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ============

/*
Allows a user to rate a movie.
Prompts for movie ID and rating, then updates the average rating.
 */
void rateMovie(Movie* root) {
    if (root == nullptr) {
        cout << "Error: No movies available to rate.\n";
        return;
    }

    int movieID;
    cout << "Enter Movie ID to rate: ";
    if (!(cin >> movieID)) {
        cout << "Invalid input. Please enter a numeric Movie ID.\n";
        cin.clear();               // Clear error flag
        cin.ignore(1000, '\n');    // Discard invalid input
        return;
    }

    Movie* movie = searchMovieByIDNode(root, movieID);
    if (movie == nullptr) {
        cout << "Error: Movie with ID " << movieID << " not found.\n";
        return;
    }

    float rating;
    while (true) {
        cout << "Enter your rating for \"" << movie->title << "\" (0 - 5): ";

        if (!(cin >> rating)) {
            cout << "Invalid input. Please enter a number between 0 and 5.\n";
            cin.clear();               // Clear error flag
            cin.ignore(1000, '\n');    // Discard invalid input
            continue;                  // Prompt again
        }

        if (rating < 0.0 || rating > 5.0) {
            cout << "Invalid rating! Please enter a value between 0 and 5.\n";
        }
        else {
            break;  // Valid rating, exit loop
        }
    }

    // Update average rating
    movie->rating = ((movie->rating * movie->ratingCount) + rating) / (movie->ratingCount + 1);
    movie->ratingCount++;

    cout << "Rating submitted successfully for \"" << movie->title << "\"!\n";

    // Display updated movie details
    cout << "\n========= Rated Movie Details =========" << endl;
    cout << "ID: " << movie->id
        << "\nTitle: " << movie->title
        << "\nYear: " << movie->year
        << "\nRating: ";

    int fullStars = static_cast<int>(movie->rating);
    fullStars = std::min(fullStars, 5);  // Cap the stars at 5

    for (int i = 0; i < fullStars; ++i) {
        cout << "*";
    }
    for (int i = fullStars; i < 5; ++i) {
        cout << ".";
    }


    cout << " (" << movie->rating << "/5 from " << movie->ratingCount << " ratings)" << endl;
}



