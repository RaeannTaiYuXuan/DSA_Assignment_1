#include "Cast.h"
#include "Movie.h"
#include "Actor.h"
#include "ActorsKnownHashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Cast* castHead = nullptr;
Cast* castIndex[MAX_CAST_SIZE] = { nullptr };
int castCount = 0;

Cast::Cast(int personId, int movieId) : person_id(personId), movie_id(movieId), next(nullptr) {}

// build cast index ==============================================================
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

bool doesCastExist(int personId, int movieId) {
    return binarySearchCast(personId, movieId) != nullptr;
}

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


void displayCasts() {
    for (int i = 0; i < castCount; ++i) {
        cout << "Actor ID: " << castIndex[i]->person_id
            << ", Movie ID: " << castIndex[i]->movie_id << endl;
    }
}



void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot) {
    int actorId, movieId;

    cout << "\n========= Actor List =========" << endl;
    displayActors(actorRoot);

    cout << "\n========= Movie List =========" << endl;
    displayMovies(movieRoot);

    while (true) {
        cout << "\nEnter 0 to exit at any point" << endl;
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

    if (addCastSorted(castHead, actorId, movieId)) {
        cout << "Actor successfully added to the movie!" << endl;
    }
}

void displayMoviesByActor(Cast* castHead, Movie* movieRoot, Actor* actorRoot) {
    int actorId;

    while (true) {
        cout << "\nEnter Actor ID (or 0 to exit): ";
        cin >> actorId;

        if (actorId == 0) {
            cout << "Exiting display movies by actor process..." << endl;
            return;
        }

        if (searchDuplicateID(actorRoot, actorId)) {
            break; 
        }

        cout << "Error: Actor ID " << actorId << " does not exist in the database! Please try again." << endl;
    }

    struct SortedMovieNode {
        string title;
        int id;
        int year;
        SortedMovieNode* next;

        SortedMovieNode(const string& title, int id, int year)
            : title(title), id(id), year(year), next(nullptr) {}
    };

    SortedMovieNode* sortedMoviesHead = nullptr;

    Cast* current = castHead;
    while (current != nullptr) {
        if (current->person_id == actorId) {
            Movie* movie = movieRoot;
            while (movie != nullptr) {
                if (current->movie_id == movie->id) {
                    SortedMovieNode* newNode = new SortedMovieNode(movie->title, movie->id, movie->year);

                    if (!sortedMoviesHead || newNode->title < sortedMoviesHead->title) {
                        newNode->next = sortedMoviesHead;
                        sortedMoviesHead = newNode;
                    }
                    else {
                        SortedMovieNode* temp = sortedMoviesHead;
                        while (temp->next && temp->next->title < newNode->title) {
                            temp = temp->next;
                        }
                        newNode->next = temp->next;
                        temp->next = newNode;
                    }
                    break;
                }
                else if (current->movie_id < movie->id) {
                    movie = movie->left; 
                }
                else {
                    movie = movie->right; 
                }
            }
        }
        current = current->next;
    }

    if (sortedMoviesHead) {
        SortedMovieNode* temp = sortedMoviesHead;
        cout << "\nMovies for Actor ID " << actorId << ":\n";
        while (temp) {
            cout << "Movie ID: " << temp->id << ", Title: " << temp->title << ", Year: " << temp->year << endl;
            temp = temp->next;
        }

        while (sortedMoviesHead) {
            SortedMovieNode* toDelete = sortedMoviesHead;
            sortedMoviesHead = sortedMoviesHead->next;
            delete toDelete;
        }
    }
    else {
        cout << "No movies found for Actor ID: " << actorId << endl;
    }
}




void displayActorsByMovie(Cast* castHead, Actor* actorRoot) {
    int movieId;

    while (true) {
        cout << "\nEnter Movie ID (or 0 to exit): ";
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
            cout << "Error: Movie ID " << movieId << " does not exist in the database! Please try again." << endl;
        }
        else {
            break; 
        }
    }

    struct SortedActorNode {
        string name;
        int id;
        int yearOfBirth;
        SortedActorNode* next;

        SortedActorNode(const string& name, int id, int yearOfBirth)
            : name(name), id(id), yearOfBirth(yearOfBirth), next(nullptr) {}
    };

    SortedActorNode* sortedActorsHead = nullptr;

    Cast* current = castHead;
    while (current != nullptr) {
        if (current->movie_id == movieId) {
            Actor* actor = actorRoot;
            while (actor != nullptr) {
                if (current->person_id == actor->id) {
                    SortedActorNode* newNode = new SortedActorNode(actor->name, actor->id, actor->yearOfBirth);

                    if (!sortedActorsHead || newNode->name < sortedActorsHead->name) {
                        newNode->next = sortedActorsHead;
                        sortedActorsHead = newNode;
                    }
                    else {
                        SortedActorNode* temp = sortedActorsHead;
                        while (temp->next && temp->next->name < newNode->name) {
                            temp = temp->next;
                        }
                        newNode->next = temp->next;
                        temp->next = newNode;
                    }
                    break; 
                }
                else if (current->person_id < actor->id) {
                    actor = actor->left; 
                }
                else {
                    actor = actor->right; 
                }
            }
        }
        current = current->next;
    }

    if (sortedActorsHead) {
        cout << "\nActors for Movie ID " << movieId << " in alphabetical order:\n";
        SortedActorNode* temp = sortedActorsHead;
        while (temp) {
            cout << "Actor ID: " << temp->id << ", Name: " << temp->name
                << ", Year of Birth: " << temp->yearOfBirth << endl;
            temp = temp->next;
        }

        while (sortedActorsHead) {
            SortedActorNode* toDelete = sortedActorsHead;
            sortedActorsHead = sortedActorsHead->next;
            delete toDelete;
        }
    }
    else {
        cout << "No actors found for Movie ID: " << movieId << endl;
    }
}



void displayKnownActors(Cast* castHead, Actor* actorRoot) {
    int actorId;

    while (true) {
        cout << "Enter Actor ID (or 0 to exit): ";
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

    Cast* current = castHead;
    while (current != nullptr) {
        if (current->person_id == actorId) {
            Cast* inner = castHead;
            while (inner != nullptr) {
                if (inner->movie_id == current->movie_id && inner->person_id != actorId) {
                    if (!knownActors.exists(inner->person_id)) {
                        knownActors.insert(inner->person_id);
                        cout << "Actor ID: " << inner->person_id << " (Known)" << endl;
                    }
                }
                inner = inner->next;
            }
        }
        current = current->next;
    }

    current = castHead;
    while (current != nullptr) {
        if (knownActors.exists(current->person_id)) {
            Cast* inner = castHead;
            while (inner != nullptr) {
                if (inner->movie_id == current->movie_id && !knownActors.exists(inner->person_id) &&
                    !extendedKnownActors.exists(inner->person_id) && inner->person_id != actorId) {
                    extendedKnownActors.insert(inner->person_id);
                    cout << "Actor ID: " << inner->person_id << " (Extended)" << endl;
                }
                inner = inner->next;
            }
        }
        current = current->next;
    }
}
