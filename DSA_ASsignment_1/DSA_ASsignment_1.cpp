#include <iostream>
#include <string>
#include "Actor.h"
using namespace std;

// Function Prototypes (You will need to implement these functions)
void addActor();
void addMovie();
void addActorToMovie();
void updateActorDetails();
void updateMovieDetails();
void displayActorsByAgeRange();
void displayRecentMovies();
void displayMoviesByActor();
void displayActorsByMovie();
void displayActorsKnownByActor();
void adminMenu(const string& filename);
void userMenu();


// main program
int main() {
    const string actorfilename = "actors.csv";
    int actorCount = 0;

    // load actors from the CSV file
    Actor* actors = loadCSV(actorfilename, actorCount);

    if (!actors || actorCount == 0) {
        cout << "No data loaded from the file!" << endl;
        return 1;
    }

    // temporary here for testing and checking
    displayActors(actors, actorCount);
    cout << endl; 

    delete[] actors;

    int choice;

    cout << "====================================\n";
    cout << "       Movie Application Menu       \n";
    cout << "====================================\n";
    cout << "1. Administrator Menu\n";
    cout << "2. User Menu\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        adminMenu(actorfilename);
        break;
    case 2:
        userMenu();
        break;
    case 3:
        cout << "Exiting the program. Goodbye!\n";
        break;
    default:
        cout << "Invalid choice. Please restart the program and try again.\n";
    }

    return 0;
}

// adminMenu
void adminMenu(const string& actorfilename) {
    int adminChoice;
    cout << "\n========== Administrator Menu ==========" << endl;
    cout << "1. Add New Actor" << endl;
    cout << "2. Add New Movie" << endl;
    cout << "3. Add Actor to a Movie" << endl;
    cout << "4. Update Actor Details" << endl;
    cout << "5. Update Movie Details" << endl;
    cout << "Enter your choice: ";
    cin >> adminChoice;
    switch (adminChoice) {
    case 1:
        addActor(actorfilename);
        break;
    case 2:
        addMovie();
        break;
    case 3:
        addActorToMovie();
        break;
    case 4:
        updateActorDetails();
        break;
    case 5:
        updateMovieDetails();
        break;
    default:
        cout << "Invalid choice. Returning to main menu.\n";
    }
}

// userMenu
void userMenu() {
    int userChoice;

    cout << "\n============= User Menu =============" << endl;
    cout << "1. Display Actors by Age Range" << endl;
    cout << "2. Display Movies from the Last 3 Years" << endl;
    cout << "3. Display Movies by an Actor" << endl;
    cout << "4. Display Actors in a Movie" << endl;
    cout << "5. Display Actors Known by an Actor" << endl;
    cout << "Enter your choice: ";
    cin >> userChoice;

    switch (userChoice) {
    case 1:
        displayActorsByAgeRange();
        break;
    case 2:
        displayRecentMovies();
        break;
    case 3:
        displayMoviesByActor();
        break;
    case 4:
        displayActorsByMovie();
        break;
    case 5:
        displayActorsKnownByActor();
        break;
    default:
        cout << "Invalid choice. Returning to main menu.\n";
    }
}


// dont use these, temporary here else code cant run....
void addActor()
{

}
void addMovie() {
    cout << "Adding a new movie... (To be implemented)\n";
}

void addActorToMovie() {
    cout << "Adding an actor to a movie... (To be implemented)\n";
}

void updateActorDetails() {
    cout << "Updating actor details... (To be implemented)\n";
}

void updateMovieDetails() {
    cout << "Updating movie details... (To be implemented)\n";
}

void displayActorsByAgeRange() {
    cout << "Displaying actors by age range... (To be implemented)\n";
}

void displayRecentMovies() {
    cout << "Displaying movies from the last 3 years... (To be implemented)\n";
}

void displayMoviesByActor() {
    cout << "Displaying movies by an actor... (To be implemented)\n";
}

void displayActorsByMovie() {
    cout << "Displaying actors in a movie... (To be implemented)\n";
}

void displayActorsKnownByActor() {
    cout << "Displaying actors known by an actor... (To be implemented)\n";
}
