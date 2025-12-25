#ifndef TAKEINPUT_H
#define TAKEINPUT_H

#include <string>
#include <vector>

/**
 * Gets input from the player via ncurses input field
 * Strips whitespaces, converts uppercase to lowercase,
 * Special card handling: J/Q/K converted to 10, A converted to 1
 * @return std::string Modified user input ready for evaluation
 */
std::string getInput();

/**
 * Calculates the result of a mathematical expression
 * Supports: +, -, *, / operations and parentheses
 * @param expression The mathematical expression as a string
 * @return double The calculated result
 */
double calculate(std::string expression);

/**
 * Evaluates if the input is valid based on game rules
 * @param input The player's input string
 * @param cards Array of 4 card values
 * @param mode Game mode (1=easy, 2=classic, 4/5=tutorial)
 * @return int Error code (0=valid, other values=specific errors)
 */
int evalInput(std::string input, double cards[4], int mode);

/**
 * Checks if the player's input equals 24
 * Handles Ace cards that can be 1 or 11
 * @param input The player's input string
 * @param cards Array of 4 card values 
 * @param mode Game mode (1=easy, 2=classic, 4/5=tutorial)
 * @return bool True if correct, false if incorrect
 */
bool ansCheck(std::string input, double cards[4], int mode);

/**
 * Displays the input panel for players to make their guess
 * Uses ncurses for display
 */
void takeinputpanel(double cards[4], int mode, int& errorCase, bool& correct);

#endif // TAKEINPUT_H