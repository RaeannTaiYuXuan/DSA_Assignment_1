#include <iostream>
#include "Actor.h"
#include "Movie.h"
#include "Cast.h"
#include "ChangeLog.h"
using namespace std;



// Global Variables
bool isRunning = true;
int currentYear = 0;

// Function Prototypes
void displayMainMenu();
void displayAdminMenu(Movie* movieRoot, Actor* actorRoot);
void displayUserMenu();
void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot);

// ============================= Main Function =============================
int main() {
    int choice;

    // Load data from CSV files
    const string actorCSV = "actors.csv";
    const string movieCSV = "movies.csv";
    const string castCSV = "cast.csv";

    loadActorsFromCSV(actorCSV);
    loadMoviesFromCSV(movieCSV);
    loadCastsFromCSV(castCSV);

    // Main Menu Loop
    while (isRunning) {
        displayMainMenu();

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {  // Check if input is not an integer
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear();              // Clear the error flag
            cin.ignore(1000, '\n');   // Discard invalid input
            continue;                 // Re-prompt the user
        }

        switch (choice) {
        case 1:
            displayAdminMenu(movieRoot, actorRoot);
            break;
        case 2:
            displayUserMenu();
            break;
        case 0:
            cout << "\nExiting application. Goodbye!\n";
            isRunning = false;
            break;
        default:
            cout << "\nInvalid choice. Please select a valid option from the menu.\n";
        }
    }

    return 0;
}


// ============================= Display Menus =============================

// Main Menu
void displayMainMenu() {

    cout << "\n========= Movie Application Menu =========\n";
    cout << "1 : Administrator menu\n";
    cout << "2 : User menu\n";
    cout << "0 : Exit\n";
    cout << "===========================================\n";

}

// Administrator Menu
void displayAdminMenu(Movie* movieRoot, Actor* actorRoot) {
    int adminChoice;

    do {
        cout << "\n========= Administrator Menu =========\n";
        cout << "1 : Add new actor\n";
        cout << "2 : Add new movie\n";
        cout << "3 : Add an actor to a movie\n";
        cout << "4 : Update actor details\n";
        cout << "5 : Update movie details\n";
        cout << "6 : Undo last change\n"; 
        cout << "7 : View change history\n"; 
        cout << "0 : Return to main menu\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            cout << "\n========= Add New Actor =========\n";
            cout << "To exit, enter 0 at any point.\n";
            addActorWrapper();
            /*cout << "\n========= Updated Actor List =========\n";*/
            /*displayActors(actorRoot);*/
            break;

        case 2:
            cout << "\n========= Add New Movie =========\n";
            cout << "To exit, enter 0 at any point.\n";
            addMovieWrapper();
            /*cout << "\n========= Updated Movie List =========\n";*/
           /* displayMovies(movieRoot);*/
            break;

        case 3:
            cout << "\n========= Add Actor to a Movie =========\n";
            addActorToMovieWrapper(movieRoot, actorRoot);
            break;

        case 4:
            cout << "\n========= Update Actor Details =========\n";
            updateActorDetails();
            /*cout << "\n========= Updated Actor Details =========\n";*/
            /*displayActors(actorRoot);*/
            break;

        case 5:
            cout << "\n========= Update Movie Details =========\n";
            updateMovieDetails();
            /*cout << "\n========= Updated Movie Details =========\n";*/
            /*displayMovies(movieRoot);*/
            break;
        case 6:
            cout << "\n========= Undo Last Change =========\n";
            undoLastChange();
            break;
        case 7:
            cout << "\n========= Display Change History =========\n";
            displayChangeHistory();
            break;
        case 0:
            cout << "\nReturning to Main Menu...\n";
            return;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (isRunning);
}

// User Menu
void displayUserMenu() {
    int userChoice;

    do {
        cout << "\n========= User Menu =========\n";
        cout << "1 : Display actors between a certain age\n";
        cout << "2 : Display movies made within the past 3 years\n";
        cout << "3 : Display all movies an actor starred in\n";
        cout << "4 : Display all the actors in a particular movie\n";
        cout << "5 : Display a list of all actors that a particular actor knows\n";
        cout << "6 : Rate an actor\n";
        cout << "7 : Rate a movie\n";
        cout << "0 : Return to main menu\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            cout << "\n========= Display Actors Between a Certain Age =========\n";
            displayActorsByAgeRangeWrapper();
            break;

        case 2:
            cout << "\n========= Display Movies Made Within the Past 3 Years =========\n";
            currentYear = 2025;  // Adjust current year as needed
            displayMoviesByRecentYears(movieRoot, currentYear);
            break;

        case 3:
            cout << "\n========= Display All Movies an Actor Starred In =========\n";
            displayMoviesByActor(castHead, movieRoot, actorRoot);
            break;

        case 4:
            cout << "\n========= Display All Actors in a Particular Movie =========\n";
            displayActorsByMovie(castHead, movieRoot, actorRoot);
            break;

        case 5:
            cout << "\n========= Display a List of All Actors That a Particular Actor Knows =========\n";
            displayKnownActors(castHead, actorRoot);
            break;

        case 6:
            cout << "\n========= Rated Actor =========\n";
            displayActors(actorRoot);
            cout << "\n";
            rateActor(actorRoot);
            break;
        case 7:
            cout << "\n========= Rated Movie =========\n";
            displayMovies(movieRoot);
            cout << "\n";
            rateMovie(movieRoot);
            break;

        case 0:
            cout << "\nReturning to Main Menu...\n";
            return;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (isRunning);
}
