#include <iostream>
#include "Actor.h"
using namespace std;

bool isRunning = true; 


// display main menu ==============================================================
void displayMainMenu() {
    cout << "========= Movie Application Menu =========" << endl;
    cout << "1 : Administrator menu" << endl;
    cout << "2 : User menu" << endl;
    cout << "0 : Exit" << endl;
    cout << "Enter your choice: ";
}

// display admin menu ==============================================================
void displayAdminMenu() {
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
            cout << "Option to add a new movie selected." << endl;
            break;
        case 3:
            cout << "Option to add an actor to a movie selected." << endl;
            break;
        case 4:
            cout << "Option to update actor details selected." << endl;
            break;
        case 5:
            cout << "Option to update movie details selected." << endl;
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
            cout << "Option to display actors between a certain age selected." << endl;
            break;
        case 2:
            cout << "Option to display movies made within the past 3 years selected." << endl;
            break;
        case 3:
            cout << "Option to display all movies an actor starred in selected." << endl;
            break;
        case 4:
            cout << "Option to display all the actors in a particular movie selected." << endl;
            break;
        case 5:
            cout << "Option to display a list of all actors that a particular actor knows selected." << endl;
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
    const string actorCSV = "actors.csv";
    loadActorsFromCSV(actorCSV);

    while (isRunning) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            displayAdminMenu();
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
