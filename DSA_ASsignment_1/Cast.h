#pragma once
#include <string>
using namespace std;

const int MAX_CAST_SIZE = 1000;

struct Movie;  
struct Actor;

struct Cast {
	int person_id;
	int movie_id;
	Cast* next;

	Cast(int personId, int movieId);
};

void loadCastsFromCSV(const string& filename);
bool addCastSorted(Cast*& head, int personId, int movieId);
void displayCasts();
void addActorToMovieWrapper(Movie* movieRoot, Actor* actorRoot);
bool doesCastExist(int personId, int movieId);
void displayMoviesByActor(Cast* castHead, Movie* movieRoot, Actor* actorRoot);
void displayActorsByMovie(Cast* castHead, Actor* actorRoot);
void displayKnownActors(Cast* castHead, Actor* actorRoot);

Cast* binarySearchCast(int personId, int movieId);
void buildCastIndex(Cast* head);

extern Cast* castHead;
extern Cast* castIndex[MAX_CAST_SIZE];
extern int castCount;


