#include "Cast.h"
#include "Movie.h"
#include "Actor.h"
#include "ActorsKnownHashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//====================================  Tam Shi Ying s10257952 - Cast.cpp ====================================

Cast* castHead = nullptr;
Cast* castIndex[MAX_CAST_SIZE] = { nullptr };
int castCount = 0;

Cast::Cast(int personId, int movieId) : person_id(personId), movie_id(movieId), next(nullptr) {}

// build cast index ==============================================================
/**
 * Builds an indexed array for binary search from the linked list of cast members.
 * This helps in optimizing the search for cast members in movies.
 */
void buildCastIndex(Cast* head) {
    Cast* current = head;
    int index = 0;
    while (current != nullptr && index < MAX_CAST_SIZE) {
        castIndex[index++] = current;
        current = current->next;
    }
    castCount = index;
}

// binary search cast ==============================================================
/**
 * Performs binary search on the indexed cast list to find a specific actor-movie pairing.
 * Returns a pointer to the Cast object if found, otherwise returns nullptr.
 */
Cast* binarySearchCast(int personId, int movieId) {
    int left = 0, right = castCount - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (castIndex[mid]->person_id == personId && castIndex[mid]->movie_id == movieId) {
            return castIndex[mid];
        }
        else if (personId < castIndex[mid]->person_id ||
            (personId == castIndex[mid]->person_id && movieId < castIndex[mid]->movie_id)) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return nullptr;
}

// load casts from csv ==============================================================
/**
 * Loads cast data from a CSV file and adds them to the linked list.
 * Also prevents duplicate cast pairs from being inserted.
 */
void loadCastsFromCSV(const string& filename) {
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
        string personIdStr, movieIdStr;

        if (getline(ss, personIdStr, ',') && getline(ss, movieIdStr)) {
            try {
                int personId = stoi(personIdStr);
                int movieId = stoi(movieIdStr);

                if (!doesCastExist(personId, movieId)) {
                    addCastSorted(castHead, personId, movieId);
                }
                else {
                    cerr << "Duplicate cast pair in CSV (Actor ID: " << personId
                        << ", Movie ID: " << movieId << "). Skipping..." << endl;
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
    buildCastIndex(castHead);
}


/**
 * Checks whether a cast (actor-movie pair) already exists in the index.
 */
bool doesCastExist(int personId, int movieId) {
    return binarySearchCast(personId, movieId) != nullptr;
}


/**
 * Adds a new cast entry (actor-movie pair) in sorted order.
 * If the actor is already associated with the movie, it prevents duplication.
 */
bool addCastSorted(Cast*& head, int personId, int movieId) {
    if (doesCastExist(personId, movieId)) {
        cout << "Error: This actor is already associated with this movie." << endl;
        return false;
    }

    Cast* newCast = new Cast(personId, movieId);

    if (head == nullptr || personId < head->person_id ||
        (personId == head->person_id && movieId < head->movie_id)) {
        newCast->next = head;
        head = newCast;

        buildCastIndex(head);
        return true;
    }

    Cast* current = head;
    while (current->next != nullptr &&
        (current->next->person_id < personId ||
            (current->next->person_id == personId && current->next->movie_id < movieId))) {
        current = current->next;
    }

    newCast->next = current->next;
    current->next = newCast;

    buildCastIndex(head);
    return true;
}


/**
 * Displays all actor-movie associations stored in the cast index.
 */
void displayCasts() {
    for (int i = 0; i < castCount; ++i) {
        cout << "Actor ID: " << castIndex[i]->person_id
            << ", Movie ID: " << castIndex[i]->movie_id << endl;
    }
}


//====================================  Tam Shi Ying s10257952 - Add actor to movie ====================================
/**
 * Adds an actor to a movie by taking input from the user.
 * Ensures that both the actor and movie exist before adding.
 */
void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot) {
    int actorId, movieId;
    char displayChoice;
    cout << "\nEnter 0 to exit at any point" << endl;

    // Ask if user wants to display the actor list
    cout << "Would you like to see the actor list? (Y/N): ";
    cin >> displayChoice;
    cin.ignore();  // Clear newline from buffer

    if (displayChoice == 'Y' || displayChoice == 'y') {
        cout << "\n========= Actor List =========" << endl;
        displayActors(actorRoot);
    }

    // Ask if user wants to display the movie list
    cout << "Would you like to see the movie list? (Y/N): ";
    cin >> displayChoice;
    cin.ignore();  // Clear newline from buffer

    if (displayChoice == 'Y' || displayChoice == 'y') {
        cout << "\n========= Movie List =========" << endl;
        displayMovies(movieRoot);
    }

    // Actor ID input
    while (true) {
        cout << "Enter actor ID: ";
        cin >> actorId;
        if (actorId == 0) {
            cout << "Exiting add actor to movie process..." << endl;
            return;
        }

        if (!searchDuplicateID(actorRoot, actorId)) {
            cout << "Error: Actor with ID " << actorId << " not found. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Movie ID input
    while (true) {
        cout << "Enter movie ID: ";
        cin >> movieId;
        if (movieId == 0) {
            cout << "Exiting add actor to movie process..." << endl;
            return;
        }

        if (!searchMovieByID(movieRoot, movieId)) {
            cout << "Error: Movie with ID " << movieId << " not found. Please try again." << endl;
        }
        else {
            break;
        }
    }

    // Add actor to movie
    if (addCastSorted(castHead, actorId, movieId)) {
        // Retrieve actor name
        Actor* actor = searchActorByID(actorRoot, actorId);
        string actorName = (actor != nullptr) ? actor->name : "Unknown Actor";

        // Retrieve movie title
        Movie* movie = searchMovieByIDNode(movieRoot, movieId);
        string movieTitle = (movie != nullptr) ? movie->title : "Unknown Movie";

        cout << "\nActor successfully added to the movie!" << endl;
        cout << "Actor ID:   " << actorId << "\n";
        cout << "Actor Name: " << actorName << "\n";
        cout << "Movie ID:   " << movieId << "\n";
        cout << "Movie Name: " << movieTitle << "\n";
        cout << "===========================" << endl;
    }
}



//====================================  Tam Shi Ying s10257952 - Display movies by actor ====================================
/**
 * Displays all movies associated with a given actor.
 * Uses binary search on the actor-movie list.
 */
void displayMoviesByActor(Cast* castHead, Movie* movieRoot, Actor* actorRoot) {
    int actorId;
    char displayChoice;

    // Ask if user wants to display actors who actually acted in movies
    cout << "Enter 0 at any point to exit" << endl;
    cout << "Would you like to see actors who have acted in movies? (Y/N): ";
    cin >> displayChoice;
    cin.ignore();

    if (displayChoice == 'Y' || displayChoice == 'y') {
        cout << "\n========= Actors Who Have Acted in Movies =========" << endl;

        Cast* castTemp = castHead;
        int lastActorId = -1;

        while (castTemp != nullptr) {
            if (castTemp->person_id != lastActorId) { // Prevent duplicate display
                Actor* actor = searchActorByID(actorRoot, castTemp->person_id);
                if (actor) {
                    cout << "Actor ID: " << actor->id << ", Name: " << actor->name << endl;
                    lastActorId = castTemp->person_id;
                }
            }
            castTemp = castTemp->next;
        }
    }

    while (true) {
        cout << "Enter Actor ID: ";
        cin >> actorId;

        if (actorId == 0) {
            cout << "Exiting display movies by actor process..." << endl;
            return;
        }

        if (searchDuplicateID(actorRoot, actorId)) {
            break;
        }

        cout << "Error: Actor ID " << actorId << " does not exist! Please try again." << endl;
    }

    int movieCount = 0;
    Cast* current = castHead;

    cout << "\nMovies for Actor ID " << actorId << ":\n";
    int lastMovieId = -1;

    while (current != nullptr) {
        if (current->person_id == actorId && current->movie_id != lastMovieId) {
            Movie* movie = searchMovieByIDNode(movieRoot, current->movie_id);
            if (movie) {
                cout << "Movie ID: " << movie->id << ", Title: " << movie->title << ", Year: " << movie->year << endl;
                movieCount++;
                lastMovieId = current->movie_id;
            }
        }
        current = current->next;
    }

    if (movieCount == 0) {
        cout << "No movies found for Actor ID: " << actorId << endl;
    }
}



//====================================  Tam Shi Ying s10257952 - Display actors by movie ====================================
/**
 * Displays all actors who starred in a given movie.
 */
void displayActorsByMovie(Cast* castHead, Movie* movieRoot, Actor* actorRoot) {
    int movieId;
    char displayChoice;
    cout << "Enter 0 at any point to exit" << endl;

    // Ask if user wants to display movies that actually have actors
    cout << "Would you like to see movies that have actors? (Y/N): ";
    cin >> displayChoice;
    cin.ignore();

    if (displayChoice == 'Y' || displayChoice == 'y') {
        cout << "\n========= Movies That Have Actors =========" << endl;

        Cast* castTemp = castHead;
        int lastMovieId = -1;

        while (castTemp != nullptr) {
            if (castTemp->movie_id != lastMovieId) { // Prevent duplicate display
                Movie* movie = searchMovieByIDNode(movieRoot, castTemp->movie_id);
                if (movie) {
                    cout << "Movie ID: " << movie->id << ", Title: " << movie->title << endl;
                    lastMovieId = castTemp->movie_id;
                }
            }
            castTemp = castTemp->next;
        }
    }

    while (true) {
        cout << "Enter Movie ID: ";
        cin >> movieId;

        if (movieId == 0) {
            cout << "Exiting display actors by movie process..." << endl;
            return;
        }

        bool movieExists = false;
        Cast* temp = castHead;

        while (temp != nullptr) {
            if (temp->movie_id == movieId) {
                movieExists = true;
                break;
            }
            temp = temp->next;
        }

        if (!movieExists) {
            cout << "Error: Movie ID " << movieId << " does not exist! Please try again." << endl;
        }
        else {
            break;
        }
    }

    int actorCount = 0;
    Cast* current = castHead;

    cout << "\nActors for Movie ID " << movieId << ":\n";
    int lastActorId = -1;

    while (current != nullptr) {
        if (current->movie_id == movieId && current->person_id != lastActorId) {
            Actor* actor = searchActorByID(actorRoot, current->person_id);
            if (actor) {
                cout << "Actor ID: " << actor->id << ", Name: " << actor->name << ", Year of Birth: " << actor->yearOfBirth << endl;
                actorCount++;
                lastActorId = current->person_id;
            }
        }
        current = current->next;
    }

    if (actorCount == 0) {
        cout << "No actors found for Movie ID: " << movieId << endl;
    }
}




//====================================  Tam Shi Ying s10257952 - Display known actors ====================================
/**
 * Displays actors who have worked with a given actor based on shared movies.
 * Also extends to find second-degree connections (actors who worked with known actors).
 */
void displayKnownActors(Cast* castHead, Actor* actorRoot) {
    int actorId;
    char displayChoice;
    cout << "Enter 0 at any point to exit" << endl;

    // Ask if user wants to display the actor list
    cout << "Would you like to see the actor list? (Y/N): ";
    cin >> displayChoice;
    cin.ignore();

    if (displayChoice == 'Y' || displayChoice == 'y') {
        cout << "\n========= Actor List =========" << endl;
        displayActors(actorRoot);
    }

    while (true) {
        cout << "Enter Actor ID: ";
        cin >> actorId;

        if (actorId == 0) {
            cout << "Exiting display known actors process..." << endl;
            return;
        }

        if (!searchDuplicateID(actorRoot, actorId)) {
            cout << "Error: Actor ID " << actorId << " does not exist in the database! Please try again." << endl;
        }
        else {
            break;
        }
    }

    ActorsKnownHashTable knownActors;
    ActorsKnownHashTable extendedKnownActors;
    int knownCount = 0;  // Count for directly known actors
    int extendedCount = 0; // Count for extended known actors

    // Find direct co-actors
    Cast* current = castHead;
    while (current != nullptr) {
        if (current->person_id == actorId) {
            Cast* inner = castHead;
            while (inner != nullptr) {
                if (inner->movie_id == current->movie_id && inner->person_id != actorId) {
                    if (!knownActors.exists(inner->person_id)) {
                        knownActors.insert(inner->person_id);
                        knownCount++;  // Increment known actor count
                        cout << "Actor ID: " << inner->person_id << endl;
                    }
                }
                inner = inner->next;
            }
        }
        current = current->next;
    }

    if (knownCount == 0) {
        cout << "No known actors found for Actor ID: " << actorId << endl;
    }

    // Find second-degree connections (actors who worked with known actors)
    current = castHead;
    while (current != nullptr) {
        if (knownActors.exists(current->person_id)) {
            Cast* inner = castHead;
            while (inner != nullptr) {
                if (inner->movie_id == current->movie_id && !knownActors.exists(inner->person_id) &&
                    !extendedKnownActors.exists(inner->person_id) && inner->person_id != actorId) {
                    extendedKnownActors.insert(inner->person_id);
                    extendedCount++; // Increment extended actor count
                    cout << "Extended Actor ID: " << inner->person_id << endl;
                }
                inner = inner->next;
            }
        }
        current = current->next;
    }

    if (extendedCount == 0) {
        cout << "No extended known actors found for Actor ID: " << actorId << endl;
    }
}
