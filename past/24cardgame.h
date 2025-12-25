#ifndef CARDGAME_H
#define CARDGAME_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;


struct Player_info {
    string name;
    double* scores;    // Dynamic array
    int scoreCount;    // Track number of scores
    int capacity;      // Track allocated capacity
};

// Global players vector (still using vector for players list)
extern vector<Player_info> players;

// Function declarations
Player_info* findPlayer(const string& name);
void addNewPlayer(const string& name, double score);
void displayLeaderboard();
void searchPlayerHistory();
void playClassicGame();
void displayMenu();
void saveLeaderboardToFile();
void addScoreToPlayer(Player_info* player, double score); // New helper function


#include <string>
#include <locale.h> // new libary for suit symbols

// Card declarations for Diamond suit
extern string diamondA[];
extern string diamond2[];
extern string diamond3[];
extern string diamond4[];
extern string diamond5[];
extern string diamond6[];
extern string diamond7[];
extern string diamond8[];
extern string diamond9[];
extern string diamond10[];
extern string diamondJ[];
extern string diamondQ[];
extern string diamondK[];

// Card declarations for Club suit
extern string clubA[];
extern string club2[];
extern string club3[];
extern string club4[];
extern string club5[];
extern string club6[];
extern string club7[];
extern string club8[];
extern string club9[];
extern string club10[];
extern string clubJ[];
extern string clubQ[];
extern string clubK[];

// Card declarations for Heart suit
extern string heartA[];
extern string heart2[];
extern string heart3[];
extern string heart4[];
extern string heart5[];
extern string heart6[];
extern string heart7[];
extern string heart8[];
extern string heart9[];
extern string heart10[];
extern string heartJ[];
extern string heartQ[];
extern string heartK[];

// Card declarations for Spade suit
extern string spadeA[];
extern string spade2[];
extern string spade3[];
extern string spade4[];
extern string spade5[];
extern string spade6[];
extern string spade7[];
extern string spade8[];
extern string spade9[];
extern string spade10[];
extern string spadeJ[];
extern string spadeQ[];
extern string spadeK[];


#include <vector>
#include <utility>



// Function declarations
vector<pair<int, int>> generateOrigCards();
void displayCards(const vector<pair<int, int>>& cards);
bool solve24(vector<double>& nums, bool easyMode);
bool isSolvableWithAces(const vector<pair<int, int>>& cards, bool easyMode);
void generateCards(string mode);
int generate_easy();
int generate_classic();
int generate_timeattack();

// Card retrieval functions
string* getDiamondCard(int number);
string* getClubCard(int number);
string* getHeartCard(int number);
string* getSpadeCard(int number);
string* getCard(int number, int suitIndex);


void displayinvalidmessage(int n);
void displayincorrectmessage();


void printtutorial();


#endif // CARDGAME_H
