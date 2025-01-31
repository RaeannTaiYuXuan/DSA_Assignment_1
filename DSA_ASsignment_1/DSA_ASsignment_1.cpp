#include <iostream>
#include "Actor.h"
#include "Movie.h"
#include "Cast.h"
using namespace std;

bool isRunning = true; 
void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot);


// display main menu ==============================================================
void displayMainMenu() {
    cout << "========= Movie Application Menu =========" << endl;
    cout << "1 : Administrator menu" << endl;
    cout << "2 : User menu" << endl;
    cout << "0 : Exit" << endl;
    cout << "Enter your choice: ";
}

// display admin menu ==============================================================
void displayAdminMenu(Movie* movieRoot, Actor* actorRoot) {
    int adminChoice;
    do {
        cout << "\n========= Administrator Menu =========" << endl;
        cout << "1 : Add new actor" << endl;
        cout << "2 : Add new movie" << endl;
        cout << "3 : Add an actor to a movie" << endl;
        cout << "4 : Update actor details" << endl;
        cout << "5 : Update movie details" << endl;
        cout << "0 : Exit" << endl;
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            cout << "\n========= Add new actor ========= " << endl;
            cout << "To exit, enter 0 at any point" << endl;
            addActorWrapper();
            displayActors(actorRoot);
            break;
        case 2:
            cout << "\n========= Add new movie ========= " << endl;
            break;
        case 3:
            cout << "\n========= Add actor to a movie ========= " << endl;
            displayCasts();
            addActorToMovieWrapper(movieRoot, actorRoot);
            displayCasts();
            break;
        case 4:
            cout << "\n========= Update actor details ========= " << endl;
            break;
        case 5:
            cout << "\n========= Update movie details ========= " << endl;
            break;
        case 0:
            cout << "Exiting application. Goodbye!" << endl;
            isRunning = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (isRunning);
}

// display user menu ==============================================================
void displayUserMenu() {
    int userChoice;
    do {
        cout << "\n========= User Menu =========" << endl;
        cout << "1 : Display actors between a certain age" << endl;
        cout << "2 : Display movies made within the past 3 years" << endl;
        cout << "3 : Display all movies an actor starred in" << endl;
        cout << "4 : Display all the actors in a particular movie" << endl;
        cout << "5 : Display a list of all actors that a particular actor knows" << endl;
        cout << "0 : Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            cout << "\n========= Display actors between a certain age ========= " << endl;
            break;
        case 2:
            cout << "\n========= Display movies made within the past 3 years ========= " << endl;
            break;
        case 3:
            cout << "\n========= Display all movies an actor starred in ========= " << endl; 
            displayActors(actorRoot);
            displayMoviesByActor(castHead, movieRoot, actorRoot);
            break;
        case 4:
            cout << "\n========= Display all the actors in a particular movie ========= " << endl; 
            displayMovies(movieRoot);
            displayActorsByMovie(castHead, actorRoot);
            
            break;
        case 5:
            cout << "\n========= Display a list of all actors that a particular actor knows ========= " << endl;
            displayKnownActors(castHead, actorRoot);
            break;
        case 0:
            cout << "Exiting application. Goodbye!" << endl;
            isRunning = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (isRunning);
}

int main() {
    int choice;

    // load data from csv files
    const string actorCSV = "actors.csv";
    const string movieCSV = "movies.csv";
    const string castCSV = "cast.csv";

    loadActorsFromCSV(actorCSV);
    loadMoviesFromCSV(movieCSV);
    loadCastsFromCSV(castCSV);

    while (isRunning) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            displayAdminMenu(movieRoot, actorRoot);
            break;
        case 2:
            displayUserMenu();
            break;
        case 0:
            cout << "Exiting application. Goodbye!" << endl;
            isRunning = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } 

    return 0;
}
