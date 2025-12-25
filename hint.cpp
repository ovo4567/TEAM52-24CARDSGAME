#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


// this is to get the card values, used for checking the user input
vector<int> getCardValues(int cardValue) {
    if (cardValue == 1) {  // Ace
        return {1, 11};
    } else if (cardValue > 10) {  // Face cards (J, Q, K)
        return {10};
    } else {
        return {cardValue};
    }
}


// the hints function gave the user the first number and first operator by trying all the combinition 
pair<string, string> EasyHint(const vector<pair<int, int>>& cards) {
    vector<vector<int>> possibleValues;
    for (const auto& card : cards) {
        possibleValues.push_back(getCardValues(card.first));
    }

    // Try all combinations of 2 cards
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Check for perfect solutions first
                    if (a + b == 24) return {to_string(a), "+"};
                    if (a - b == 24) return {to_string(a), "-"};
                    
                    // Then check for operations that get close to 12 (half of 24)
                    if (abs(a + b - 12) <= 2) return {to_string(a), "+"};
                    if (a - b > 0 && abs(a - b - 12) <= 2) return {to_string(a), "-"};
                }
            }
        }
    }

    // Fallback to any valid addition
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    return {to_string(a), "+"};
                }
            }
        }
    }

    return {"any number", "+"};
}


// noted that all four operators could be used in the classic mode 
pair<string, string> ClassicHint(const vector<pair<int, int>>& cards) {
    vector<vector<int>> possibleValues;
    for (const auto& card : cards) {
        possibleValues.push_back(getCardValues(card.first));
    }

    // Try all combinations of 2 cards
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Check for perfect solutions first
                    if (a * b == 24) return {to_string(a), "*"};
                    if (a + b == 24) return {to_string(a), "+"};
                    if (a - b == 24) return {to_string(a), "-"};
                    if (b != 0 && a / b == 24) return {to_string(a), "/"};
                    
                    // Then check for factors of 24
                    if (24 % (a * b) == 0) return {to_string(a), "*"};
                    if (24 % (a + b) == 0) return {to_string(a), "+"};
                    
                    // Then check for useful intermediates
                    if (a * b < 24 && 24 % (a * b) == 0) return {to_string(a), "*"};
                    if (b != 0 && a % b == 0 && (a / b) < 24 && 24 % (a / b) == 0) {
                        return {to_string(a), "/"};
                    }
                }
            }
        }
    }

    // Fallback to multiplication as it's most likely to help reach 24
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    return {to_string(a), "*"};
                }
            }
        }
    }

    return {"any number", "*"};
}

string getEasyModeHint(const vector<pair<int, int>>& cards) {
    string temp;
    auto hint = EasyHint(cards);
    temp = "Easy Mode: Start with " + hint.first + " " + hint.second;
    return temp;
}

string getClassicModeHint(const vector<pair<int, int>>& cards) {
    string temp;
    auto hint = ClassicHint(cards);
    temp = "Classic Mode: Start with " + hint.first + " " + hint.second;
    return temp;
}

/*
void printCards(const vector<pair<int, int>>& cards) {
    cout << "Current cards: ";
    for (const auto& card : cards) {
        if (card.first == 1) cout << "A ";
        else if (card.first == 11) cout << "J ";
        else if (card.first == 12) cout << "Q ";
        else if (card.first == 13) cout << "K ";
        else cout << card.first << " ";
    }
    cout << endl;
}
*/
