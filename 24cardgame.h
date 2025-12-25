#ifndef CARDGAME_H
#define CARDGAME_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

/**
Player_info
Stores player information including name and score history
 */
struct Player_info {
    string name;
    double* scores;    // Dynamic array
    int scoreCount;    // Track number of scores
    int capacity;      // Track allocated capacity
};

// Global players vector (still using vector for players list)
extern vector<Player_info> players;

// Function declarations

/**
 Finds a player by name in the global players vector
 parameters: name The name of the player to find
 return: Pointer to Player_info if found, nullptr otherwise
 */
Player_info* findPlayer(const string& name);

/**
Adds a new player to the global players vector
parameters: 
name: Name of the new player
score: Initial score for the new player
 */
void addNewPlayer(const string& name, double score);

/**
Displays the leaderboard in ncurses window
 */
void displayLeaderboard();

/**
Searches for a player's score history and displays it
 */
void searchPlayerHistory();

/**
Saves the current leaderboard to a file
 */
void saveLeaderboardToFile();

/**
Adds a score to a player's score array, resizing if needed
parameters:
player: Pointer to the player to add score to
score: The score to add
 */
void addScoreToPlayer(Player_info* player, double score);

/**
Prints game tutorial/instructions
 */
void printtutorial();

#endif // CARDGAME_H
