#pragma once
#include <string>
using namespace std;


//====================================  Tam Shi Ying s10257952 - Additional feature (undoing change & change history) ====================================

/**
 * Structure to store the previous version of an Actor or Movie.
 */
struct ChangeLog {
    string entityType;  // "Actor" or "Movie"
    int id;
    string oldName;
    int oldYear;
    ChangeLog* next;

    // Constructor
    ChangeLog(const string& type, int entityId, const string& name, int year);
};

// Stack for storing change history
extern ChangeLog* changeHistory;

/**
 * Pushes an actor/movie update into the change log.
 */
void pushChange(const string& entityType, int id, const string& oldName, int oldYear);

/**
 * Pops the last change from the stack and restores the previous version.
 */
void undoLastChange();

/**
 * Displays the change history log.
 */
void displayChangeHistory();
