#pragma once

struct ActorHashNode {
    int key;
    ActorHashNode* next;
    ActorHashNode(int k) : key(k), next(nullptr) {}
};

class ActorsKnownHashTable {
private:
    static const int TABLE_SIZE = 100; 
    ActorHashNode* table[TABLE_SIZE];

    int hashFunction(int key) const {
        return key % TABLE_SIZE;
    }

public:
    ActorsKnownHashTable();
    ~ActorsKnownHashTable();
    void insert(int key);
    bool exists(int key) const;
    void clear();
};
