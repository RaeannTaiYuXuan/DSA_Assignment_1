#include "ChangeLog.h"
#include "Actor.h"
#include "Movie.h"
#include <iostream>
using namespace std;

//====================================  Tam Shi Ying s10257952 - Additional feature (undoing change & change history) ====================================

ChangeLog* changeHistory = nullptr; // Stack for storing changes

// Constructor for ChangeLog
ChangeLog::ChangeLog(const string& type, int entityId, const string& name, int year)
    : entityType(type), id(entityId), oldName(name), oldYear(year), next(nullptr) {}

/**
 * Pushes an actor/movie update into the change log.
 */
void pushChange(const string& entityType, int id, const string& oldName, int oldYear) {
    ChangeLog* newChange = new ChangeLog(entityType, id, oldName, oldYear);
    newChange->next = changeHistory;
    changeHistory = newChange;
}

/**
 * Pops the last change from the stack and restores the previous version.
 */
void undoLastChange() {
    if (changeHistory == nullptr) {
        cout << "No changes to undo.\n";
        return;
    }

    ChangeLog* lastChange = changeHistory;
    changeHistory = changeHistory->next;

    cout << "Undoing last change...\n";
    cout << "Restoring " << lastChange->entityType << " ID " << lastChange->id << " to previous version:\n";
    cout << "Name: " << lastChange->oldName << ", Year: " << lastChange->oldYear << endl;

    // Restore the previous version in the actual database (Actor or Movie)
    if (lastChange->entityType == "Actor") {
        Actor* actor = searchActorByID(actorRoot, lastChange->id);
        if (actor) {
            actor->name = lastChange->oldName;
            actor->yearOfBirth = lastChange->oldYear;
        }
    }
    else if (lastChange->entityType == "Movie") {
        Movie* movie = searchMovieByIDNode(movieRoot, lastChange->id);
        if (movie) {
            movie->title = lastChange->oldName;
            movie->year = lastChange->oldYear;
        }
    }

    delete lastChange;
}

/**
 * Retrieves the current name of an Actor or Movie by ID.
 */
string getCurrentName(const string& entityType, int id) {
    if (entityType == "Actor") {
        Actor* actor = searchActorByID(actorRoot, id);
        return actor ? actor->name : "Not Found";
    }
    else if (entityType == "Movie") {
        Movie* movie = searchMovieByIDNode(movieRoot, id);
        return movie ? movie->title : "Not Found";
    }
    return "Unknown";
}

/**
 * Displays the change history log.
 */
void displayChangeHistory() {
    ChangeLog* current = changeHistory;
    if (!current) {
        cout << "No change history available.\n";
        return;
    }

    cout << "\n========= Change History =========\n";
    while (current) {
        string currentName = getCurrentName(current->entityType, current->id);

        cout << current->entityType << " ID " << current->id << ":\n";
        cout << "  - Previous Name: " << current->oldName << "\n";
        cout << "  - Current Name: " << currentName << "\n";
        cout << "  - Previous Year: " << current->oldYear << "\n";

        current = current->next;
    }
    cout << "===================================\n";
}
