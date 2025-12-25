#include "24cardgame.h"
#include <ncursesw/ncurses.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

// Initialize the global players vector
vector<Player_info> players;

/**
Adds a score to a player's dynamic score array, resizing if needed
parameters:
player: Pointer to the player to add score to
score: The score to add
If the score array is full, it will double the capacity
 */
void addScoreToPlayer(Player_info* player, double score) {
    if (player->scoreCount == player->capacity) {
        // Need to resize
        int newCapacity = (player->capacity == 0) ? 1 : player->capacity * 2;
        double* newScores = new double[newCapacity];
        
        // Copy existing scores
        for (int i = 0; i < player->scoreCount; i++) {
            newScores[i] = player->scores[i];
        }
        
        // Delete old array and update
        delete[] player->scores;
        player->scores = newScores;
        player->capacity = newCapacity;
    }
    
    // Add the new score
    player->scores[player->scoreCount++] = score;
}

/**
Finds a player by name in the global players vector
parameter:
name: The name of the player to find
return: Pointer to Player_info if found, nullptr otherwise
 */
Player_info* findPlayer(const string& name) {
    for (auto& player : players) {
        if (player.name == name) {
            return &player;
        }
    }
    return nullptr;
}

/**
Adds a new player with initial score
parameters: 
name: Name of the new player
score: Initial score for the new player
Initializes the player's score array with capacity 1
 */
void addNewPlayer(const string& name, double score) {
    Player_info newPlayer;
    newPlayer.name = name;
    newPlayer.scores = new double[1]; // Start with capacity 1
    newPlayer.scores[0] = score;
    newPlayer.scoreCount = 1;
    newPlayer.capacity = 1;
    players.push_back(newPlayer);
}

/**
Displays leaderboard in ascending order (lower score is better)
Uses ncurses for display and provides interactive menu options:
        1. Search player history
        2. Save leaderboard to file
        3. Return to Main Menu
 */
void displayLeaderboard() {    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Sort players by their best score in ascending order
    sort(players.begin(), players.end(), [](const Player_info& a, const Player_info& b) {
        if (a.scoreCount == 0) return false;
        if (b.scoreCount == 0) return true;
        
        // Get best (lowest) score for each player
        double a_best = a.scores[0];
        double b_best = b.scores[0];
        for (int i = 1; i < a.scoreCount; i++) {
            if (a.scores[i] < a_best) a_best = a.scores[i];
        }
        for (int i = 1; i < b.scoreCount; i++) {
            if (b.scores[i] < b_best) b_best = b.scores[i];
        }
        
        return a_best < b_best;
    });

    while(true){
        clear();
        // Display header
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(1, (max_x - 45) / 2, "=== LEADERBOARD (Second/Question - Lower is Better) ===");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        // Column headers
        mvprintw(3, (max_x - 45) / 2, "Rank");
        mvprintw(3, (max_x - 45) / 2+10, "Player Name");
        mvprintw(3, (max_x - 45) / 2+35, "Best Second/Question");
        mvprintw(4, (max_x - 45) / 2, "-------------------------------------------------------");

        // Display player data
        int row = 5;
        int rank = 1;
        for (const auto& player : players) {
            if (player.scoreCount > 0) {
                double best = player.scores[0];
                for (int i = 1; i < player.scoreCount; i++) {
                    if (player.scores[i] < best) best = player.scores[i];
                }
                mvprintw(row, (max_x - 45) / 2, "%d", rank++);
                mvprintw(row, (max_x - 45) / 2+10, "%s", player.name.c_str());
                mvprintw(row, (max_x - 45) / 2+35, "%.2f", best);
                row++;
            
                // Prevent overflow
                if (row > max_y - 6) break;
            }
        }
    
        // Menu options
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(max_y - 10, (max_x-32)/2, "1. Search player history");
        mvprintw(max_y - 9, (max_x-32)/2, "2. Save leaderboard to file");
        mvprintw(max_y - 8, (max_x-32)/2, "3. Return to Main Menu");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(2));
        mvprintw(max_y - 5, (max_x-32)/2, "Please enter your choice (1-3): ");
        refresh();
    
        // Handle menu choices
        int choice = getch() - '0';  // Convert char to int
        switch (choice) {
            case 1:
                searchPlayerHistory();
                break;
            case 2:
                endwin(); // Temporarily exit ncurses
                saveLeaderboardToFile();
                // Re-initialize ncurses
                initscr();
                cbreak();
                noecho();
                keypad(stdscr, TRUE);
                break;
            case 3:
                return;
            default:
                mvprintw(max_y - 2, (max_x - 30) / 2, "Invalid choice! Try again.");
                refresh();
                napms(1000); // Pause for 1 second
                break;
        }
    }
    return;
}

/**
Searches for a player's history and displays it
Prompts user for player name, then displays all scores and best score
Uses ncurses for display and input
 */
void searchPlayerHistory() {
    // Initialize a new window for player search
    clear();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display prompt
    mvprintw(2, (max_x - 25) / 2, "=== PLAYER SEARCH ===");
    mvprintw(4, (max_x - 30) / 2, "Enter player name: ");
    echo(); // Enable echo for input
    curs_set(1); // Show cursor
    refresh();
    
    // Get player name
    char name_buffer[100];
    getstr(name_buffer);
    string name(name_buffer);
    noecho(); // Disable echo after input
    curs_set(0); // Hide cursor
    
    // Search for player
    Player_info* player = findPlayer(name);
    if (player) {
        mvprintw(6, (max_x - 40) / 2, "Second/Question history for %s:", name.c_str());
        
        string history = "";
        for (int i = 0; i < player->scoreCount; i++) {
            char score_str[20];
            sprintf(score_str, "%.2f ", player->scores[i]);
            history += score_str;
        }
        
        // Display history with word wrapping if needed
        int row = 8;
        int col = (max_x - 60) / 2;
        for (size_t i = 0; i < history.length(); i++) {
            if ((i > 0 && i % 60 == 0) || history[i] == '\n') {
                row++;
                col = (max_x - 60) / 2;
            }
            mvaddch(row, col++, history[i]);
        }
        
        // Find and display best score
        if (player->scoreCount > 0) {
            double best = player->scores[0];
            for (int i = 1; i < player->scoreCount; i++) {
                if (player->scores[i] < best) best = player->scores[i];
            }
            mvprintw(row + 2, (max_x - 30) / 2, "Best Second/Question: %.2f", best);
        }
    } else {
        mvprintw(6, (max_x - 20) / 2, "Player not found.");
    }
    
    mvprintw(max_y - 3, (max_x - 35) / 2, "Press any key to return to leaderboard");
    refresh();
    getch(); // Wait for key press
}

/**
Saves the current leaderboard to a file named "leaderboard.txt"
Includes timestamp and formats the output in columns
Sorts players by best score before saving
 */
void saveLeaderboardToFile() {
    ofstream fout("leaderboard.txt");
    if (!fout) {
        cerr << "Error opening leaderboard file for writing!\n";
        return;
    }

    // Get current date/time
    time_t now = time(0);
    char dt[100];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // Sort by best score (ascending)
    sort(players.begin(), players.end(), [](const Player_info& a, const Player_info& b) {
        if (a.scoreCount == 0) return false;
        if (b.scoreCount == 0) return true;
        
        double a_best = a.scores[0];
        double b_best = b.scores[0];
        for (int i = 1; i < a.scoreCount; i++) {
            if (a.scores[i] < a_best) a_best = a.scores[i];
        }
        for (int i = 1; i < b.scoreCount; i++) {
            if (b.scores[i] < b_best) b_best = b.scores[i];
        }
        return a_best < b_best;
    });

    fout << "Leaderboard saved at: " << dt << "\n\n";
    fout << left << setw(5) << "Rank" << setw(20) << "Player Name" << "Best Second/Question\n";
    fout << "--------------------------------------------\n";
    
    int rank = 1;
    for (const auto& player : players) {
        if (player.scoreCount > 0) {
            double best = player.scores[0];
            for (int i = 1; i < player.scoreCount; i++) {
                if (player.scores[i] < best) best = player.scores[i];
            }
            fout << left << setw(5) << rank++ << setw(20) << player.name 
                 << fixed << setprecision(2) << best << "\n";
        }
    }
    
    fout.close();
    cout << "Leaderboard saved to leaderboard.txt\n";
}
