#include <iostream>
#include <vector>
#include <string>
#include <utility> // for pair

using namespace std;

string getEasyModeHint(const vector<pair<int, int>>& cards) {
    // First convert all cards to possible values (A=1/11, J/Q/K=10)
    vector<vector<int>> possibleValues;
    for (const auto& card : cards) {
        int value = card.first; // Using the first element of the pair
        if (value == 1) {
            possibleValues.push_back({1, 11}); // Ace can be 1 or 11
        } else if (value >= 11) {
            possibleValues.push_back({10}); // Face cards are 10
        } else {
            possibleValues.push_back({value}); // Number cards
        }
    }

    // Try to find a promising addition or subtraction hint
    for (size_t i = 0; i < possibleValues.size(); i++) {
        for (int a : possibleValues[i]) {
            for (size_t j = 0; j < possibleValues.size(); j++) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Prefer additions that get close to 12 (half of 24)
                    if (a + b >= 10 && a + b <= 14) {
                        return "Try starting with: " + to_string(a) + " + ?";
                    }
                    // Then subtractions that get close to 6 (quarter of 24)
                    if (a - b >= 4 && a - b <= 8) {
                        return "Try starting with: " + to_string(a) + " - ?";
                    }
                    if (b - a >= 4 && b - a <= 8) {
                        return "Try starting with: " + to_string(b) + " - ?";
                    }
                }
            }
        }
    }

    // Fallback hint if no ideal operations found
    return "Try combining " + to_string(possibleValues[0][0]) + " with another number using + or -";
}

int hint_easy() {
    vector<pair<int, int>> cards;
  
    // cards defined in another function in generated 
    cout << "\nEasy Mode Hint:\n";
    cout << "--------------\n";
    cout << getEasyModeHint(cards) << "\n\n";
    cout << "Remember:\n";
    cout << "- Aces can be 1 or 11\n";
    cout << "- Jack/Queen/King = 10\n";
    cout << "- Only use addition (+) and subtraction (-)\n";
    
    return 0;
}

string getClassicModeHint(const vector<pair<int, int>>& cards) {
    // First convert all cards to possible values (A=1/11, J/Q/K=10)
    vector<vector<int>> possibleValues;
    for (const auto& card : cards) {
        int value = card.first; // Using the first element of the pair
        if (value == 1) {
            possibleValues.push_back({1, 11}); // Ace can be 1 or 11
        } else if (value >= 11) {
            possibleValues.push_back({10}); // Face cards are 10
        } else {
            possibleValues.push_back({value}); // Number cards
        }
    }

    // Try to find the most promising first operation
    for (size_t i = 0; i < possibleValues.size(); i++) {
        for (int a : possibleValues[i]) {
            for (size_t j = 0; j < possibleValues.size(); j++) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Check all four operations
                    vector<pair<char, int>> operations;
                    
                    // Addition
                    int sum = a + b;
                    if (sum > 0 && sum <= 24) {
                        operations.emplace_back('+', sum);
                    }
                    
                    // Subtraction (both orders)
                    if (a - b > 0) {
                        operations.emplace_back('-', a - b);
                    }
                    if (b - a > 0) {
                        operations.emplace_back('-', b - a);
                    }
                    
                    // Multiplication
                    int product = a * b;
                    if (product > 0 && product <= 24) {
                        operations.emplace_back('*', product);
                    }
                    
                    // Division (both orders, if exact)
                    if (b != 0 && a % b == 0) {
                        operations.emplace_back('/', a / b);
                    }
                    if (a != 0 && b % a == 0) {
                        operations.emplace_back('/', b / a);
                    }

                    // Prefer operations that create useful intermediate numbers
                    for (const auto& op : operations) {
                        // Numbers that are factors of 24 are most useful
                        if (24 % op.second == 0) {
                            return "Try starting with: " + to_string(a) + " " + op.first + " ?";
                        }
                        // Then numbers close to factors
                        if (abs(op.second - 6) <= 2 || abs(op.second - 8) <= 2 || 
                            abs(op.second - 12) <= 2) {
                            return "Try starting with: " + to_string(a) + " " + op.first + " ?";
                        }
                    }
                }
            }
        }
    }

    // Fallback hint
    return "Try combining any two numbers with +, -, ×, or ÷";
}

int hint_classic() {
    vector<pair<int, int>> cards;
    // cards would be defined in another function
    
    cout << "\nClassic Mode Hint:\n";
    cout << "----------------\n";
    cout << getClassicModeHint(cards) << "\n\n";
    cout << "Remember:\n";
    cout << "- Aces can be 1 or 11\n";
    cout << "- Jack/Queen/King = 10\n";
    cout << "- Use all operations: +, -, ×, ÷\n";
    
    return 0;
}
