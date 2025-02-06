#pragma once

//====================================  Tam Shi Ying s10257952 ====================================

/**
 * Represents a single node in the hash table's linked list (separate chaining).
 * Stores an actor's ID (`key`) and a pointer to the next node in case of collisions.
 */
struct ActorHashNode {
    int key;
    ActorHashNode* next;
    ActorHashNode(int k) : key(k), next(nullptr) {}
};


/**
 * Implements a hash table to store and efficiently retrieve actor relationships.
 * Uses separate chaining (linked lists) for collision handling.
 */
class ActorsKnownHashTable {
private:
    static const int TABLE_SIZE = 100;  // Size of the hash table
    ActorHashNode* table[TABLE_SIZE];   // Array of pointers to linked lists


    /**
     * Hash function that computes an index for a given actor ID.
     * Uses modulo operation to ensure index remains within table size.
     */
    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

public:
    /**
     * Constructor: Initializes the hash table with all entries set to nullptr.
     */
    ActorsKnownHashTable();

    /**
     * Destructor: Frees memory by clearing the hash table before deletion.
     */
    ~ActorsKnownHashTable();

    /**
     * Inserts an actor ID into the hash table if it doesn't already exist.
     * Uses separate chaining to handle collisions.
     */
    void insert(int key);

    /**
     * Checks whether a given actor ID exists in the hash table.
     * Returns `true` if the key is found, otherwise returns `false`.
     */
    bool exists(int key) const;

    /**
     * Clears the hash table by deleting all stored actor IDs.
     * Ensures no memory leaks occur when the program ends or the table is reset.
     */
    void clear();
};