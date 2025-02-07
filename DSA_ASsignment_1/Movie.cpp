#include "Movie.h"
#include "Levenshtein.h"
#include "ChangeLog.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

Movie* movieRoot = nullptr;

Movie::Movie(int movieId, const string& movieTitle, const string& moviePlot, int releaseYear)
    : id(movieId), title(movieTitle), plot(moviePlot), year(releaseYear),
    rating(0.0), ratingCount(0), left(nullptr), right(nullptr) {}

void loadMoviesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;

    // Skip header line
    if (!getline(file, line)) {
        cerr << "Error: CSV file is empty or missing header." << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, title, plot, yearStr;

        // Read Movie ID
        if (!getline(ss, idStr, ',')) continue;

        // Read Title (handle quotes correctly)
        if (ss.peek() == '"') {
            ss.get();
            getline(ss, title, '"');
            ss.get(); // Remove comma after closing quote
        }
        else {
            getline(ss, title, ',');
        }

        // Read Plot (handle quotes correctly)
        if (ss.peek() == '"') {
            ss.get();
            getline(ss, plot, '"');
            ss.get();
        }
        else {
            getline(ss, plot, ',');
        }

        // Read Year
        if (!getline(ss, yearStr)) continue;

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
                *current = new Movie(id, title, plot, year);
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid data in CSV line: " << line << " (" << e.what() << ")" << endl;
        }
        catch (const out_of_range& e) {
            cerr << "Out of range data in CSV line: " << line << " (" << e.what() << ")" << endl;
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
    if (root == nullptr) return;

    // In-order traversal (left → root → right)
    displayMovies(root->left);

    // Display movie details in a clean list format
    cout << "ID: " << root->id
        << ",  Title: " << root->title
        << ",  Plot: " << root->plot
        << ",  Year: " << root->year << "\n";

    // Continue traversal
    displayMovies(root->right);
}




//==================================== Raeann Tai Yu Xuan S10262832J -  ====================================
//this is the BSL tree ( binary search tree)

Movie* addMovie(Movie* root, int id, const string& title, const string& plot, int year) {
    if (root == nullptr) {
        return new Movie(id, title, plot, year);
    }

    if (id < root->id) {
        root->left = addMovie(root->left, id, title, plot, year);
    }
    else if (id > root->id) {
        root->right = addMovie(root->right, id, title, plot, year);
    }
    else {
        cout << "Error: Movie with ID " << id << " already exists.\n";
    }

    return root;
}



//==================================== Raeann Tai Yu Xuan S10262832J -  ====================================
void addMovieWrapper() {
    int id, year;
    string title, plot;

    // Get Movie ID
    while (true) {
        cout << "Enter movie ID: ";
        if (!(cin >> id)) {
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (id == 0) {
            cout << "Movie addition canceled.\n";
            return;
        }

        if (searchMovieByID(movieRoot, id)) {
            cout << "Error: Movie with this ID already exists. Try again.\n";
        }
        else {
            cin.ignore(1000, '\n');
            break;
        }
    }

    // Get Movie Title
    while (true) {
        cout << "Enter movie title: ";
        getline(cin, title);
        if (!title.empty() && title.find_first_not_of(' ') != string::npos) {
            break;
        }
        cout << "Error: Title cannot be empty. Try again.\n";
    }

    // Get Movie Plot
    while (true) {
        cout << "Enter movie plot: ";
        getline(cin, plot);
        if (!plot.empty() && plot.find_first_not_of(' ') != string::npos) {
            break;
        }
        cout << "Error: Plot cannot be empty. Try again.\n";
    }

    // Get Year of Release
    while (true) {
        cout << "Enter year of release: ";
        if (!(cin >> year)) {
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (year >= 1900 && year <= 2025) {
            break;
        }
        cout << "Error: Please enter a valid year between 1900 and 2025.\n";
    }

    // Add the Movie
    movieRoot = addMovie(movieRoot, id, title, plot, year);

    // Show only the newly added movie
    cout << "\nMovie added successfully!\n";
    cout << "\n========= New Movie Details =========\n";
    cout << "Movie ID: " << id
        << ", Title: \"" << title
        << "\", Plot: " << plot
        << ", Year: " << year << endl;
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

    // Store the previous version before updating (for undo feature)
    pushChange("Movie", id, movie->title, movie->year);

    string newTitle, newPlot;
    int newYear;

    cin.ignore();
    cout << "Enter new title (leave blank to keep unchanged): ";
    getline(cin, newTitle);

    if (!newTitle.empty()) {
        movie->title = newTitle;
    }

    cout << "Enter new release year (or 0 to keep unchanged): ";
    cin >> newYear;
    cin.ignore();

    if (newYear >= 1900 && newYear <= 2025) {
        movie->year = newYear;
    }
    else if (newYear != 0) {
        cout << "Invalid year! Keeping previous value.\n";
    }

    cout << "Enter new plot (leave blank to keep unchanged): ";
    getline(cin, newPlot);

    if (!newPlot.empty()) {
        movie->plot = newPlot;
    }

    cout << "\nMovie updated successfully!\n";
    cout << "========= Updated Movie Details =========\n";
    cout << "Movie ID: " << movie->id
        << ", Title: \"" << movie->title
        << "\", Year: " << movie->year
        << ", Plot: " << movie->plot << endl;
}



//==================================== Raeann Tai Yu Xuan S10262832J - Function to Display Movies from the Last 3 Years ====================================

// Structure for linked list node
struct MovieNode {
    Movie* movie;
    MovieNode* next;
};

// Insert movie into sorted linked list (ascending order by year)
void insertSorted(MovieNode*& head, Movie* movie) {
    MovieNode* newNode = new MovieNode{ movie, nullptr };

    // If list is empty or movie should be inserted at the head
    if (!head || movie->year < head->movie->year) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Find position to insert
    MovieNode* current = head;
    while (current->next && current->next->movie->year <= movie->year) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Collect movies from BST that fall within the past 3 years
void collectMovies(Movie* root, int currentYear, MovieNode*& head) {
    if (!root) return;

    collectMovies(root->left, currentYear, head);

    if (root->year >= currentYear - 3 && root->year <= currentYear) {
        insertSorted(head, root);  // Insert movie into sorted linked list
    }

    collectMovies(root->right, currentYear, head);
}


/*
Displays movies released in the past 3 years in ascending order.
This function performs an in-order traversal of the movie BST
and filters movies that were released within the last 3 years.
Pointer to the root of the BST.
currentYear The current year to calculate the 3-year range.
 */
 // Display movies in sorted order from the linked list
void displayMoviesByRecentYears(Movie* root, int currentYear) {
    MovieNode* head = nullptr;  // Head of linked list

    // Collect and sort movies
    collectMovies(root, currentYear, head);

    // Display sorted movies
    MovieNode* current = head;
    while (current) {
        cout << "Movie ID: " << current->movie->id
            << ", Title: \"" << current->movie->title
            << "\", Year: " << current->movie->year << endl;
        current = current->next;
    }

    // Free allocated memory
    while (head) {
        MovieNode* temp = head;
        head = head->next;
        delete temp;
    }
}



//========== Raeann Tai Yu Xuan S10262832J - advance (ratings) ============

/*
Allows a user to rate a movie.
Prompts for movie ID and rating, then updates the average rating.
 */


// Function to compute Levenshtein Distance (Edit Distance)

// Find top 3 similar movies based on plot similarity
void findSimilarMovies(Movie* root, const Movie* targetMovie, Movie* recommendations[3], int distances[3]) {
    if (root == nullptr) return;

    // Ignore the target movie itself
    if (root->id != targetMovie->id) {
        int distance = levenshteinDistance(targetMovie->plot, root->plot);

        // Insert into the top 3 recommendations if it's a better match
        for (int i = 0; i < 3; i++) {
            if (distance < distances[i]) {
                // Shift lower-ranked movies down
                for (int j = 2; j > i; j--) {
                    distances[j] = distances[j - 1];
                    recommendations[j] = recommendations[j - 1];
                }
                // Insert new recommendation
                distances[i] = distance;
                recommendations[i] = root;
                break;
            }
        }
    }

    // Recursive traversal (in-order to ensure sorted traversal)
    findSimilarMovies(root->left, targetMovie, recommendations, distances);
    findSimilarMovies(root->right, targetMovie, recommendations, distances);
}

// Rate a movie and show recommendations based on plot similarity
void rateMovie(Movie* root) {
    if (root == nullptr) {
        cout << "Error: No movies available to rate.\n";
        return;
    }

    char showList;
    cout << "Would you like to see the full list of movies before rating? (Y/N): ";
    cin >> showList;

    if (showList == 'Y' || showList == 'y') {
        cout << "\n========= List of Movies =========\n";
        displayMovies(root);
        cout << "==================================\n";
    }

    int movieID;
    cout << "Enter Movie ID to rate: ";
    if (!(cin >> movieID)) {
        cout << "Invalid input. Please enter a numeric Movie ID.\n";
        cin.clear();
        cin.ignore(1000, '\n');
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
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (rating < 0.0 || rating > 5.0) {
            cout << "Invalid rating! Please enter a value between 0 and 5.\n";
        }
        else {
            break;
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
    fullStars = std::min(fullStars, 5);

    for (int i = 0; i < fullStars; ++i) cout << "*";
    for (int i = fullStars; i < 5; ++i) cout << ".";

    cout << " (" << movie->rating << "/5 from " << movie->ratingCount << " ratings)" << endl;

    // Find top 3 similar movies based on plot similarity
    Movie* recommendations[3] = { nullptr, nullptr, nullptr };
    int distances[3] = { numeric_limits<int>::max(), numeric_limits<int>::max(), numeric_limits<int>::max() };

    findSimilarMovies(root, movie, recommendations, distances);

    // Display recommendations
    cout << "\n========= Recommended Movies Based on Similar Plot =========\n";
    for (int i = 0; i < 3; i++) {
        if (recommendations[i] != nullptr) {
            cout << i + 1 << ". " << recommendations[i]->title << " (Year: " << recommendations[i]->year
                << ", Similarity Score: " << distances[i] << ")\n";
        }
    }
    cout << "========================================================\n";
}