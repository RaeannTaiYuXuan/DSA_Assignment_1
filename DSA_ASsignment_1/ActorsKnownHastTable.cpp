#include "ActorsKnownHashTable.h"
#include <iostream>

ActorsKnownHashTable::ActorsKnownHashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

ActorsKnownHashTable::~ActorsKnownHashTable() {
    clear();
}

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
