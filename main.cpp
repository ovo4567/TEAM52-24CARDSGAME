#include <ncursesw/ncurses.h> // Uses ncurses library for terminal UI
#include <locale.h>            // For displaying suit symbols (unicode support)
#include <string>
#include <cstdlib>
#include "generate.h"          // Card generation functions
#include "24cardgame.h"        // Game logic and leaderboard functions
#include "tutorial.h"          // Tutorial display functions

// Function prototypes
void DisplayStartScreen();    // Displays initial welcome screen
void DisplayMenuScreen();     // Displays main menu
void DisplayPlayScreen();     // Displays play mode selection menu

/**
Main entry point for the 24 Cipher game
parameters:
arc: Number of command line arguments
argv: Command line arguments
return:
Exit status (0 for normal exit)

Initializes ncurses, sets up color pairs, and starts the game flow
 */
int main(int arc, char **argv) {
    // Set locale to the system's default (for unicode symbol support)
    setlocale(LC_ALL, "");

    // Initialize ncurses
    initscr();               // Initialize screen
    cbreak();                // Line buffering disabled
    noecho();                // Don't echo input
    keypad(stdscr, TRUE);    // Enable special keys
    curs_set(0);             // Hide cursor
    
    // Initialize color support if available
    if (has_colors()) {
        start_color();
        // Define color pairs (foreground, background):
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Pair 1: Green text
        init_pair(2, COLOR_CYAN, COLOR_BLACK);   // Pair 2: Cyan text
        init_pair(3, COLOR_RED, COLOR_BLACK);    // Pair 3: Red text
    }
    
    // Start game flow with the welcome screen
    DisplayStartScreen();
    
    // Clean up ncurses before exit
    endwin();
    return 0;
}

/**
Displays the initial welcome screen

 Shows game title and waits for any key press before proceeding
        to the main menu. Uses color pair 1 for the title.
 */
void DisplayStartScreen() {
    clear();
    // Get terminal dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display game title with bold and color
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/3, (max_x-11)/2, "The 24 Cipher");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Display prompt
    mvprintw(max_y/2, (max_x-25)/2, "Press any key to start...");
    refresh();
    getch(); // Wait for user input
    
    // Proceed to main menu
    DisplayMenuScreen();
}

/**
Displays and handles the main menu

Provides four options:
        1. Play - Goes to play mode selection
        2. Rules and Tutorial - Shows game instructions
        3. Leaderboard - Displays player rankings
        4. Exit Game - Saves leaderboard and quits
  Uses color pair 2 for menu options.
 */
void DisplayMenuScreen() {
    while (true) {
        clear();
        
        // Get terminal dimensions
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        // Display menu title
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(max_y/5, (max_x-10)/2, "MAIN MENU");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        // Display menu options with color
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(max_y/3 + 0, (max_x-20)/2, "1. Play");
        mvprintw(max_y/3 + 2, (max_x-20)/2, "2. Rules and Tutorial");
        mvprintw(max_y/3 + 4, (max_x-20)/2, "3. Leaderboard");
        mvprintw(max_y/3 + 6, (max_x-20)/2, "4. Exit Game");
        if (has_colors()) attroff(COLOR_PAIR(2));
        
        // Prompt for user choice
        mvprintw(max_y - 5, (max_x-32)/2, "Please enter your choice (1-4): ");
        refresh();
        
        // Get and process user input
        int choice = getch() - '0';  // Convert char to int
        
        switch (choice) {
            case 1:  // Play
                DisplayPlayScreen();
                break;
            case 2:  // Tutorial
                displayTutorial(); // From tutorial.cpp
                break;
            case 3:  // Leaderboard
                displayLeaderboard(); // From 24cardgame.cpp
                break;
            case 4:  // Exit
                saveLeaderboardToFile(); // Save before exiting
                return;
            default: // Invalid input
                mvprintw(max_y - 3, (max_x-30)/2, "Invalid choice! Try again.");
                refresh();
                napms(1000); // Show error for 1 second
                break;
        }
    }
}

/**
Displays and handles the play mode selection menu

Provides four options:
        1. Easy Mode - Simplified game version
        2. Classic Mode - Standard game rules
        3. Time-Attack Mode - Timed challenge
        4. Return to Main Menu - Goes back
  Uses color pair 2 for menu options.
 */
void DisplayPlayScreen() {
    while (true) {
        clear();
        
        // Get terminal dimensions
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        // Display menu title
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(max_y/5, (max_x-10)/2, "PLAY MENU");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        // Display play options with color
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(max_y/3 + 0, (max_x-20)/2, "1. Easy Mode");
        mvprintw(max_y/3 + 2, (max_x-20)/2, "2. Classic Mode");
        mvprintw(max_y/3 + 4, (max_x-20)/2, "3. Time-Attack Mode");
        mvprintw(max_y/3 + 6, (max_x-20)/2, "4. Return to Main Menu");
        if (has_colors()) attroff(COLOR_PAIR(2));
        
        // Prompt for user choice
        mvprintw(max_y - 5, (max_x-32)/2, "Please enter your choice (1-4): ");
        refresh();
        
        // Get and process user input
        int choice = getch() - '0';
        
        switch (choice) {
            case 1:  // Easy Mode
                generate_easy(); // From generate.cpp
                break;
            case 2:  // Classic Mode
                generate_classic(); // From generate.cpp
                break;
            case 3:  // Time-Attack
                generate_timeattack(); // From generate.cpp
                break;
            case 4:  // Return to main menu
                return;
            default: // Invalid input
                mvprintw(max_y - 3, (max_x-30)/2, "Invalid choice! Try again.");
                refresh();
                napms(1000); // Show error for 1 second
                break;
        }
    }
}
