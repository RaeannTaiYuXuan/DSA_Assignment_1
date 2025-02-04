#include "ActorsKnownHashTable.h"
#include <iostream>
//====================================  Tam Shi Ying s10257952 - Hash Table for tracking which actors know each other ====================================
// for display a list of actors that a particular actor knows

ActorsKnownHashTable::ActorsKnownHashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

/**
 * Destructor: Clears the hash table to free memory.
 * Calls the `clear()` function to delete all nodes.
 */
ActorsKnownHashTable::~ActorsKnownHashTable() {
    clear();
}


/**
 * Inserts a new actor ID into the hash table if it doesn't already exist.
 * Uses separate chaining for handling collisions.
 */
void ActorsKnownHashTable::insert(int key) {
    int index = hashFunction(key);
    ActorHashNode* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return; 
        }
        current = current->next;
    }
    // Insert new node
    ActorHashNode* newNode = new ActorHashNode(key);
    newNode->next = table[index];
    table[index] = newNode;
}

/**
 * Checks whether a given actor ID exists in the hash table.
 * Returns `true` if the key is found, otherwise returns `false`.
 */
bool ActorsKnownHashTable::exists(int key) const {
    int index = hashFunction(key);
    ActorHashNode* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}


/**
 * Clears the hash table by deleting all nodes in each linked list.
 * Ensures no memory leaks occur when the program ends or table is reset.
 */
void ActorsKnownHashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        ActorHashNode* current = table[i];
        while (current != nullptr) {
            ActorHashNode* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}
