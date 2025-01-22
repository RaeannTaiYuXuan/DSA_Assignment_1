#include <iostream>
#include <string>

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

void adminMenu();
void userMenu();

int main() {
    int choice;

    std::cout << "====================================\n";
    std::cout << "       Movie Application Menu       \n";
    std::cout << "====================================\n";
    std::cout << "1. Administrator Menu\n";
    std::cout << "2. User Menu\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        adminMenu();
        break;
    case 2:
        userMenu();
        break;
    case 3:
        std::cout << "Exiting the program. Goodbye!\n";
        break;
    default:
        std::cout << "Invalid choice. Please restart the program and try again.\n";
    }

    return 0;
}

void adminMenu() {
    int adminChoice;

    std::cout << "\n========== Administrator Menu ==========" << std::endl;
    std::cout << "1. Add New Actor" << std::endl;
    std::cout << "2. Add New Movie" << std::endl;
    std::cout << "3. Add Actor to a Movie" << std::endl;
    std::cout << "4. Update Actor Details" << std::endl;
    std::cout << "5. Update Movie Details" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> adminChoice;

    switch (adminChoice) {
    case 1:
        addActor();
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
        std::cout << "Invalid choice. Returning to main menu.\n";
    }
}

void userMenu() {
    int userChoice;

    std::cout << "\n============= User Menu =============" << std::endl;
    std::cout << "1. Display Actors by Age Range" << std::endl;
    std::cout << "2. Display Movies from the Last 3 Years" << std::endl;
    std::cout << "3. Display Movies by an Actor" << std::endl;
    std::cout << "4. Display Actors in a Movie" << std::endl;
    std::cout << "5. Display Actors Known by an Actor" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> userChoice;

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
        std::cout << "Invalid choice. Returning to main menu.\n";
    }
}

// Placeholder functions (implement these based on your data structures)
void addActor() {
    std::cout << "Adding a new actor... (To be implemented)\n";
}

void addMovie() {
    std::cout << "Adding a new movie... (To be implemented)\n";
}

void addActorToMovie() {
    std::cout << "Adding an actor to a movie... (To be implemented)\n";
}

void updateActorDetails() {
    std::cout << "Updating actor details... (To be implemented)\n";
}

void updateMovieDetails() {
    std::cout << "Updating movie details... (To be implemented)\n";
}

void displayActorsByAgeRange() {
    std::cout << "Displaying actors by age range... (To be implemented)\n";
}

void displayRecentMovies() {
    std::cout << "Displaying movies from the last 3 years... (To be implemented)\n";
}

void displayMoviesByActor() {
    std::cout << "Displaying movies by an actor... (To be implemented)\n";
}

void displayActorsByMovie() {
    std::cout << "Displaying actors in a movie... (To be implemented)\n";
}

void displayActorsKnownByActor() {
    std::cout << "Displaying actors known by an actor... (To be implemented)\n";
}
