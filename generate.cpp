#include "generate.h"
#include "asciiart.h"
#include "takeinput.h"
#include "displaymessage.h"
#include "timeattackmode.h"
#include "hint.h"
#include <ncursesw/ncurses.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

// this is for mapping the numbers to the asciicards 
string* getDiamondCard(int number) {
    switch(number) {
        case 1: return diamondA;
        case 2: return diamond2;
        case 3: return diamond3;
        case 4: return diamond4;
        case 5: return diamond5;
        case 6: return diamond6;
        case 7: return diamond7;
        case 8: return diamond8;
        case 9: return diamond9;
        case 10: return diamond10;
        case 11: return diamondJ;
        case 12: return diamondQ;
        case 13: return diamondK;
        default: return nullptr;
    }
}

// Function to get club card
string* getClubCard(int number) {
    switch(number) {
        case 1: return clubA;
        case 2: return club2;
        case 3: return club3;
        case 4: return club4;
        case 5: return club5;
        case 6: return club6;
        case 7: return club7;
        case 8: return club8;
        case 9: return club9;
        case 10: return club10;
        case 11: return clubJ;
        case 12: return clubQ;
        case 13: return clubK;
        default: return nullptr;
    }
}

// Function to get heart card
string* getHeartCard(int number) {
    switch(number) {
        case 1: return heartA;
        case 2: return heart2;
        case 3: return heart3;
        case 4: return heart4;
        case 5: return heart5;
        case 6: return heart6;
        case 7: return heart7;
        case 8: return heart8;
        case 9: return heart9;
        case 10: return heart10;
        case 11: return heartJ;
        case 12: return heartQ;
        case 13: return heartK;
        default: return nullptr;
    }
}

// Function to get spade card
string* getSpadeCard(int number) {
    switch(number) {
        case 1: return spadeA;
        case 2: return spade2;
        case 3: return spade3;
        case 4: return spade4;
        case 5: return spade5;
        case 6: return spade6;
        case 7: return spade7;
        case 8: return spade8;
        case 9: return spade9;
        case 10: return spade10;
        case 11: return spadeJ;
        case 12: return spadeQ;
        case 13: return spadeK;
        default: return nullptr;
    }
}

// General function to get any card based on suit and number
// call getCard function to display the cards
//retrieve the string function from the above according to the number and suit index

string* getCard(int number, int suitIndex) {
    switch(suitIndex) {
        case 0: return getDiamondCard(number);
        case 1: return getClubCard(number);
        case 2: return getHeartCard(number);
        case 3: return getSpadeCard(number);
        default: return nullptr;
    }
}

// random generate 4 numbers and random suits for them and store them into cards 
// cards should be an array containing values and suits for 4 numbers 
vector<pair<int, int>> generateOrigCards() {
    vector<pair<int, int>> cards; // Pair: <value, suitIndex>
    for (int i = 0; i < 4; ++i) {
        int value = rand() % 13 + 1; // 1-13 (A=1, J=11, Q=12, K=13)
        int suit = rand() % 4; // Random suit: 0=Diamond, 1=Club, 2=Heart, 3=Spade
        cards.push_back({value, suit});
    }
    return cards;
}

// Convert raw card values to game values (A=1 or 11, J/Q/K=10)
vector<double> getGameValues(const vector<pair<int, int>>& cards, vector<int>& aceChoices) {
    vector<double> values;
    aceChoices.clear();
    for (auto [val, suit] : cards) {
        if (val >= 11) {
            values.push_back(10.0); // J, Q, K = 10
            aceChoices.push_back(-1); // No Ace choice, -1 here just for checking the number is 1 or not 
        } else if (val == 1) {
            int choice = rand() % 2; // Randomly pick 1 or 11 for Ace
            values.push_back(choice ? 11.0 : 1.0);
            aceChoices.push_back(choice); // Store choice (0=1, 1=11)
        } else {
            values.push_back(static_cast<double>(val)); // 2-10
            aceChoices.push_back(-1); // No Ace choice
        }
    }
    return values; // only return only game values in this step 
}


// This solve24 function is to check whether the random generated cards have a solution, serving for the easy mode and classic mode 

const double TARGET = 24.0;
const double EPSILON = 1e-6; // For floating point comparison

bool solve24(vector<double>& nums, bool easyMode = false) {
    // Base case: if only one number left, check if it's approximately 24
    if (nums.size() == 1) {
        return abs(nums[0] - TARGET) < EPSILON;
    }

    // Try all pairs of numbers
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < nums.size(); ++j) {
            if (i == j) continue; // Skip using the same number twice

            double num1 = nums[i];
            double num2 = nums[j];

            // Create a new vector with remaining numbers
            vector<double> remainingNumbers;
            for (size_t k = 0; k < nums.size(); ++k) {
                if (k != i && k != j) {
                    remainingNumbers.push_back(nums[k]);
                }
            }

            // Try all possible operations
            vector<double> paths;
            
            // Always try addition
            paths.push_back(num1 + num2);
            
            // Always try subtraction (both orders)
            paths.push_back(num1 - num2);
            paths.push_back(num2 - num1);

            // In classic mode, also try multiplication and division

            // if it is classic mode, the bool easymode will be set as False 
            if (!easyMode) {
                paths.push_back(num1 * num2);
                
                // Only try division if not dividing by zero
                if (abs(num2) > EPSILON) {
                    paths.push_back(num1 / num2);
                }
                if (abs(num1) > EPSILON) {
                    paths.push_back(num2 / num1);
                }
            }

            // Try each operation result
            for (double result : paths) {
                remainingNumbers.push_back(result);
                if (solve24(remainingNumbers, easyMode)) {
                    return true;
                }
                remainingNumbers.pop_back(); // Backtrack
            }
        }
    }
    return false;
}

// just for handling Ace condition since Ace condition could be considered as 1 or 11
bool isSolvableWithAces(const vector<pair<int, int>>& cards, bool easyMode = false) {
    // First, convert all cards to their base values
    // Aces will be temporarily set to 0 (to be handled later)
    // Face cards (J/Q/K = 11/12/13) become 10
    vector<double> cardValues;
    vector<int> acePositions; // Stores positions of Aces in the cardValues vector
    
    for (size_t i = 0; i < cards.size(); ++i) {
        int cardValue = cards[i].first;
        
        if (cardValue >= 11) { // Face card (Jack, Queen, King)
            cardValues.push_back(10.0);
        } 
        else if (cardValue == 1) { // Ace
            cardValues.push_back(0.0); // Temporary placeholder
            acePositions.push_back(i); // Remember this is an Ace
        } 
        else { // Number card (2-10)
            cardValues.push_back(static_cast<double>(cardValue));
        }
    }

    // If there are no Aces, just check normally
    if (acePositions.empty()) {
        return solve24(cardValues, easyMode);
    }

    // For each Ace, it can be either 1 or 11
    // We need to try all possible combinations
    int numberOfAces = acePositions.size();
    int totalCombinations = 1 << numberOfAces; // 2^numberOfAces possibilities
    
    for (int combination = 0; combination < totalCombinations; ++combination) {
        vector<double> currentValues = cardValues;
        
        // Set each Ace to either 1 or 11 based on the combination
        for (int aceIndex = 0; aceIndex < numberOfAces; ++aceIndex) {
            bool useHighValue = combination & (1 << aceIndex);
            currentValues[acePositions[aceIndex]] = useHighValue ? 11.0 : 1.0;
        }
        
        // Check if this combination works
        if (solve24(currentValues, easyMode)) {
            return true;
        }
    }
    
    // None of the Ace combinations worked
    return false;
}

// Display cards using ncurses //this part is modifed
void displayCards(const vector<pair<int, int>>& cards) {
    clear();
    
    // Get dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(2, (max_x-15)/2, "Cards Dealt: ");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    int card_width = 11; // Width of each card
    int card_height = 9; // Height of each card
    int spacing_x = 3;  // Horizontal space between cards
    int spacing_y = 2;  // Vertical space between cards
    
    // Center the 2x2 grid
    int grid_width = 2 * card_width + spacing_x;
    int grid_height = 2 * card_height + spacing_y;
    int start_x = (max_x - grid_width) / 2;
    int start_y = 5;
    
    // Display the cards
    for (int i = 0; i < 4; ++i) {
        int row = i / 2;     // 0 for top row, 1 for bottom row
        int col = i % 2;     // 0 for left column, 1 for right column
        int pos_x = start_x + col * (card_width + spacing_x);
        int pos_y = start_y + row * (card_height + spacing_y);
        
        string* card = getCard(cards[i].first, cards[i].second);
        if (card) {
            for (int line = 0; line < 9; ++line) {
                mvprintw(pos_y + line, pos_x, "%s", card[line].c_str());
            }
        }
    }
    
    // Display card value information
    int info_x = start_x + grid_width + 10; // Position for value information
    int info_y = start_y + 2;               // Start a bit down from the cards
    
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(2));
    mvprintw(info_y, info_x, "Card Value:");
    mvprintw(info_y + 2, info_x, "2-10  : its value");
    mvprintw(info_y + 3, info_x, "J,Q,K : 10");
    mvprintw(info_y + 4, info_x, "A     : 1 or 11");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(2));
}

//step_2 timeattack, no need to check the issivable //this part is modified
void generateCards(string mode) { //mode = "easy", "classic", "timeattack"
    srand(time(0));
    vector<pair<int, int>> cards;

    clear();
    // Get dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display loading message
    if (mode != "timeattack") {
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(max_y/2, (max_x-25)/2, "Generating CHILL cards..."); //"Generating valid 24-game combination..."
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        refresh();
        napms(500); // Slight delay
    }
    if (mode == "timeattack") {
        DisplayTimeAttackScreen();
        //return;
    } else {
        int attempts = 0;
        const int MAX_ATTEMPTS = 100;
        bool easyMode = (mode == "easy");
        int intmode = 1; //intmode 1:easy mode; intmode 2:classic mode; intmode 4&5:tutorial
        double cardsnumsindouble[4];
        int errorCase = -1;
        bool correct = false;
        string themessage, hints;
        if (mode == "classic") {
            intmode = 2;
        }
        // Generate cards until a solvable set is found
        do{
            cards = generateOrigCards();
        }while(!isSolvableWithAces(cards, easyMode));
        int i=0;
        //converting the data type to evaluate the answer
        for (const auto& p : cards) {
            if (p.first >= 10){
                cardsnumsindouble[i] = 10;
            }
            else{
                cardsnumsindouble[i] = p.first;
            }
            i++;
        }
        while (attempts < MAX_ATTEMPTS) {
            clear();
            attempts++;

            displayCards(cards);
            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(1));
            mvprintw(25 + 3, (max_x-50)/2, "[h] for a hint, [q] to quit");
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(1));

            mvprintw(25 + 5, (max_x-50)/2, "Attempt %d of %d", attempts, MAX_ATTEMPTS);
            takeinputpanel(cardsnumsindouble,intmode,errorCase,correct); //errorCase -1: typed 'q'; errorCase -2: typed 'h'; errorCase -3: typed 's'; errorCase 1-8: different syntax error

            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(3));
            if (errorCase == -1) {
                attroff(A_BOLD);
                if (has_colors()) attroff(COLOR_PAIR(3));
                return;
            } 
            else if (errorCase == -2) { //hints
                if (intmode == 1) {
                    hints = getEasyModeHint(cards);
                }
                else if (intmode == 2) {
                    hints = getClassicModeHint(cards);
                }
                if (has_colors()) attroff(COLOR_PAIR(3));
                if (has_colors()) attron(COLOR_PAIR(2));
                mvprintw(25+10, (max_x-50)/2, hints.c_str());
                if (has_colors()) attroff(COLOR_PAIR(2));
                refresh();
            }
            else if (errorCase == -3) { //skipping question ONLY in time attack mode (reusability)
                continue;
            }
            else if (errorCase == 0) { //not syntax error
                if (correct) {
                    if (has_colors()) attroff(COLOR_PAIR(3));
                    if (has_colors()) attron(COLOR_PAIR(1));
                    mvprintw(25+10, (max_x-50)/2, "CORRECT! You made 24!");
                    if (has_colors()) attroff(COLOR_PAIR(1));
                    refresh();
                    getch();
                    return;
                }
                else {
                    themessage = displayincorrectmessage();
                    mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                    refresh();
                }
            }
            else if (errorCase >= 1) { //syntax error
                themessage = displayinvalidmessage(errorCase);
                mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                refresh();
            }
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(3));
            getch();
        }
    }
    return;
}

// Main entry points
int generate_easy() { 
    generateCards("easy"); 
    return 0; 
}

int generate_classic() { 
    generateCards("classic"); 
    return 0; 
}

int generate_timeattack() { 
    generateCards("timeattack"); 
    return 0; 
}
