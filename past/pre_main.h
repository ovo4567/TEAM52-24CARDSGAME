#ifndef CARDGAME_H
#define CARDGAME_H

#include <vector>
#include <string>
#include <utility>
using namespace std;

// Card ASCII art declarations (from generateasciiart.cpp)
extern string diamondA[];
extern string diamond2[];
// ... (all other card declarations)

// Card retrieval functions
string* getDiamondCard(int number);
string* getClubCard(int number);
string* getHeartCard(int number);
string* getSpadeCard(int number);
string* getCard(int number, int suitIndex);

// Card generation and game logic
vector<pair<int, int>> generateOrigCards();
vector<double> getGameValues(const vector<pair<int, int>>& cards, vector<int>& aceChoices);
bool solve24(vector<double>& nums, bool easyMode = false);
bool isSolvableWithAces(const vector<pair<int, int>>& cards, bool easyMode = false);
void displayCards(const vector<pair<int, int>>& cards);
void generateCards(string mode);
int generate_easy();
int generate_classic();
int generate_timeattack();
int generate();

// Player info class
class Player_info {
public:
    string nick_name;
    double marks_per_second;
    double* marks_per_second_history;
    int history_size;
    int history_capacity;

    Player_info(string name, double mps = 0.0);
    ~Player_info();
    void addScore(double score);
    void displayScoreHistory();
    void displayInfo();
    void resizeHistory();
};

// Global variables and helper functions
extern vector<Player_info> all_players;
extern const double TARGET;
extern const double EPSILON;
Player_info* findPlayer(const string& name);
bool comparePlayers(const Player_info& a, const Player_info& b);
void displayLeaderboard();
void menu();
void time_attack_mode();

#endif
