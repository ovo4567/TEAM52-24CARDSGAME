#ifndef GENERATE_H
#define GENERATE_H

#include <vector>
#include <utility>
#include <string>
#include <locale.h> // new libary for suit symbols

// Function declarations
std::vector<std::pair<int, int> > generateOrigCards();
void displayCards(const std::vector<std::pair<int, int> >& cards);
bool solve24(std::vector<double>& nums, bool easyMode);
bool isSolvableWithAces(const std::vector<std::pair<int, int> >& cards, bool easyMode);
void generateCards(std::string mode);
int generate_easy();
int generate_classic();
int generate_timeattack();

// Card retrieval functions
std::string* getDiamondCard(int number);
std::string* getClubCard(int number);
std::string* getHeartCard(int number);
std::string* getSpadeCard(int number);
std::string* getCard(int number, int suitIndex);

#endif // GENERATE_H