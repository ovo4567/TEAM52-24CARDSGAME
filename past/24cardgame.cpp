#include "24cardgame.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <limits>

using namespace std;

// Initialize the global players vector
vector<Player_info> players;

// Helper function to add score to player's dynamic array
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

// Find player by name, returns nullptr if not found
Player_info* findPlayer(const string& name) {
    for (auto& player : players) {
        if (player.name == name) {
            return &player;
        }
    }
    return nullptr;
}

// Add a new player with initial score
void addNewPlayer(const string& name, double score) {
    Player_info newPlayer;
    newPlayer.name = name;
    newPlayer.scores = new double[1]; // Start with capacity 1
    newPlayer.scores[0] = score;
    newPlayer.scoreCount = 1;
    newPlayer.capacity = 1;
    players.push_back(newPlayer);
}

// Display leaderboard in ascending order (lower score is better)
void displayLeaderboard() {
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

    cout << "\n=== LEADERBOARD (Score/Second - Lower is Better) ===\n";
    cout << left << setw(5) << "Rank" << setw(20) << "Player Name" << "Best Score/Second\n";
    cout << "--------------------------------------------\n";
    
    int rank = 1;
    for (const auto& player : players) {
        if (player.scoreCount > 0) {
            double best = player.scores[0];
            for (int i = 1; i < player.scoreCount; i++) {
                if (player.scores[i] < best) best = player.scores[i];
            }
            cout << left << setw(5) << rank++ << setw(20) << player.name << best << endl;
        }
    }
    
    // Leaderboard menu
    while (true) {
        cout << "\n1. Search player history\n";
        cout << "2. Save leaderboard to file\n";
        cout << "3. Back to main menu\n";
        cout << "Choose an option: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                searchPlayerHistory();
                break;
            case 2:
                saveLeaderboardToFile();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Search for a player's history
void searchPlayerHistory() {
    string name;
    cout << "Enter player name to search: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);
    
    Player_info* player = findPlayer(name);
    if (player) {
        cout << "\nScore/Second history for " << name << ":\n";
        for (int i = 0; i < player->scoreCount; i++) {
            cout << player->scores[i] << " ";
        }
        cout << "\nBest Score/Second: ";
        if (player->scoreCount > 0) {
            double best = player->scores[0];
            for (int i = 1; i < player->scoreCount; i++) {
                if (player->scores[i] < best) best = player->scores[i];
            }
            cout << best;
        }
        cout << endl;
    } else {
        cout << "Player not found.\n";
    }
}

// Play the classic game
void playClassicGame() {
    string name;
    cout << "Enter your name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);
    
    // Simulate game time and score
    srand(time(0));
    double gameTime = 5 + (rand() % 60); // Random game time 5-64 seconds
    double score = 1 + (rand() % 100);   // Random score 1-100
    double scorePerSecond = score / gameTime;
    
    cout << "Game completed in " << gameTime << " seconds with score: " << score << endl;
    cout << "Your Score/Second: " << fixed << setprecision(2) << scorePerSecond << endl;
    
    Player_info* player = findPlayer(name);
    if (player) {
        addScoreToPlayer(player, scorePerSecond);
        cout << "Welcome back, " << name << "! Your new Score/Second has been recorded." << endl;
    } else {
        addNewPlayer(name, scorePerSecond);
        cout << "Welcome, " << name << "! Your first Score/Second has been recorded." << endl;
    }
    
    cout << "Press enter to return to menu...";
    cin.ignore();
    cin.get(); // Wait for user to press enter
}

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
    fout << left << setw(5) << "Rank" << setw(20) << "Player Name" << "Best Score/Second\n";
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

// Display main menu
void displayMenu() {
    while (true) {
        system("cls"); // Clear screen (Windows)
        // system("clear"); // For Linux/Mac
        
        cout << "=== 24 CARD GAME ===\n";
        cout << "1. Classic Game\n";
        cout << "2. Leaderboard\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                playClassicGame();
                break;
            case 2:
                displayLeaderboard();
                break;
            case 3:
                saveLeaderboardToFile();
                // Clean up dynamic memory
                for (auto& player : players) {
                    delete[] player.scores;
                }
                cout << "Thanks for playing!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
