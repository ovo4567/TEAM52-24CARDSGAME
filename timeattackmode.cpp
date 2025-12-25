#include "generate.h"
#include "24cardgame.h"
#include "takeinput.h"
#include "displaymessage.h"
#include <ncursesw/ncurses.h>
#include <string>

/**
Time-attack game mode function
parameter:
minutes: Duration of the game in minutes
 */
void timeattack(int minutes);

/**
Displays the time-attack mode selection screen
Provides menu options for different game durations:
 *       1. 1-minute Challenge
 *       2. 3-minute Challenge
 *       3. 5-minute Challenge
 *       4. Return to Play Menu
 * Uses ncurses for display and handles user input
 */
void DisplayTimeAttackScreen() {
    while (true) {
        clear();
        
        // Get screen dimensions
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        // Display menu title
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(max_y/5, (max_x-10)/2, "TIME-ATTACK MENU");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(max_y/3 + 0, (max_x-20)/2, "1. 1-minute Challenge");
        mvprintw(max_y/3 + 2, (max_x-20)/2, "2. 3-minute Challenge");
        mvprintw(max_y/3 + 4, (max_x-20)/2, "3. 5-minute Challenge");
        mvprintw(max_y/3 + 6, (max_x-20)/2, "4. Return to Play Menu");
        if (has_colors()) attroff(COLOR_PAIR(2));
        
        
        mvprintw(max_y - 5, (max_x-32)/2, "Please enter your choice (1-4): ");
        
        refresh();
        
        
        int choice = getch() - '0';  // Convert char to int
        
        switch (choice) {
            case 1:
                timeattack(1);
                break;
            case 2:
                timeattack(3);
                break;
            case 3:
                timeattack(5);
                break;
            case 4:
                return;
            default:
                mvprintw(max_y - 3, (max_x-30)/2, "Invalid choice! Try again.");
                refresh();
                napms(1000); // Pause for 1 second
                break;
        }
    }
}

/**
Main time-attack game logic
parameters:
minutes: Duration of the game in minutes
 Handles the complete time-attack game flow:
  - Gets player name
  - Generates cards
  - Manages timer
  - Processes player input
  - Calculates and displays score
  - Updates leaderboard
  
  Features:
  - Real-time countdown display
  - Card generation and display
  - Input validation and processing
  - Score tracking
  - Early exit with ESC key
  - Question skipping with 's' key
 */
void timeattack(int minutes) {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/3+3, (max_x-20)/2, "Generating HELL cards...");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Get user name
    char name[100] = {0};
    mvprintw(max_y/3 + 0, (max_x-20)/2, "Enter your name: ");
    echo(); // Show typed characters
    curs_set(1); // Show cursor
    getnstr(name, sizeof(name) - 1);
    noecho();
    curs_set(0);
    
    // Convert minutes to seconds for the countdown
    int totalSeconds = minutes * 60;
    int score = 0;
    time_t startTime = time(nullptr);
    bool gameRunning = true;
    
    vector<pair<int, int>> cards = generateOrigCards();
    double cardsnumsindouble[4];
    int errorCase = -1;
    bool correct = false;
    bool inputActive = false;
    string userInput = "";
    
    // For tracking input state
    int inputPos = 0;
    
    while (gameRunning) {
        // Calculate remaining time
        time_t currentTime = time(nullptr);
        int elapsedSeconds = difftime(currentTime, startTime);
        int remainingSeconds = totalSeconds - elapsedSeconds;
        
        if (remainingSeconds <= 0) {
            gameRunning = false;
            break;
        }
        
        // Display time remaining
        int mins = remainingSeconds / 60;
        int secs = remainingSeconds % 60;
        
        // Clear and redraw the screen
        clear();
        
        // Display cards
        displayCards(cards);
        
        // Convert card values to double array for processing
        int i = 0;
        for (const auto& p : cards) {
            cardsnumsindouble[i] = (p.first >= 10) ? 10 : p.first;
            i++;
        }
        
        // Display timer prominently
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(5, 5, "Time: %02d:%02d", mins, secs);
        mvprintw(6, 5, "Score: %d", score);
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(2));
        
        // Display instructions (updated with ESC)
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(25 + 3, (max_x-50)/2, "[ESC] to quit [s] to skip this question");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        // Display input area
        mvprintw(25+7, (max_x-50)/2, "Make 24: %s", userInput.c_str());
        
        refresh();
        
        // Check for user input with timeout
        timeout(100); // Set timeout to 100ms
        int ch = getch();
        
        if (ch != ERR) { // If a key was pressed
            if (ch == 27) {  // ESC key to quit
                gameRunning = false;
                break;
            } else if (ch == 's' || ch == 'S') {
                cards = generateOrigCards();
                userInput = "";
                continue;
            } else if (ch == '\n' || ch == KEY_ENTER) {
                // Process the input
                string processedInput = userInput;
                // Process input (trim whitespaces, convert to lowercase)
                string modifiedInput = "";
                for (char character : processedInput) {
                    if (!isspace(character)) { // Trims away whitespaces
                        character = tolower(character); // Converts uppercase letters into lowercase
                        if (character=='j' || character=='q' || character=='k') { // Turns 'j', 'q', 'k' into the number 10
                            modifiedInput += "10";
                        } else if (character == 'a') { // Turns 'a' into the number 1
                            modifiedInput += '1';
                        } else {
                            modifiedInput += character;
                        }
                    }
                }
                
                // Evaluate the input
                errorCase = evalInput(modifiedInput, cardsnumsindouble, 2);
                if (errorCase == 0) {
                    correct = ansCheck(modifiedInput, cardsnumsindouble, 2);
                    if (correct) {
                        attron(A_BOLD);
                        if (has_colors()) attron(COLOR_PAIR(1));
                        mvprintw(25+10, (max_x-50)/2, "CORRECT! You made 24!");
                        attroff(A_BOLD);
                        if (has_colors()) attroff(COLOR_PAIR(1));
                        refresh();
                        score++;
                        napms(500);
                        cards = generateOrigCards();
                        userInput = "";
                    } else {
                        string themessage = displayincorrectmessage();
                        attron(A_BOLD);
                        if (has_colors()) attron(COLOR_PAIR(3));
                        mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                        attroff(A_BOLD);
                        if (has_colors()) attroff(COLOR_PAIR(3));
                        refresh();
                        napms(1000);
                        userInput = "";
                    }
                } else if (errorCase >= 1) {
                    string themessage = displayinvalidmessage(errorCase);
                    attron(A_BOLD);
                    if (has_colors()) attron(COLOR_PAIR(3));
                    mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                    attroff(A_BOLD);
                    if (has_colors()) attroff(COLOR_PAIR(3));
                    refresh();
                    napms(1000);
                    userInput = "";
                }
            } else if (ch == KEY_BACKSPACE || ch == 127) {
                // Handle backspace
                if (!userInput.empty()) {
                    userInput.pop_back();
                }
            } else if (isprint(ch)) {
                // Add character to input (including 'q'/'Q' for cards)
                userInput += ch;
            }
        }
    }
    
    // Game over
    clear();
    int finaltotalSeconds = difftime(time(nullptr), startTime);
    int finalscore = score;
    double SecondPerQuestion = 0;
    
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(3));
    mvprintw(max_y/2-4, (max_x-60)/2, "TIME'S UP!");
    if (has_colors()) attroff(COLOR_PAIR(3));
    
    mvprintw(max_y/2-2, (max_x-60)/2, "%d questions completed in %d seconds", finalscore, finaltotalSeconds);
    
    if (finalscore != 0) {
        SecondPerQuestion = (float)finaltotalSeconds/finalscore;
    } else {
        SecondPerQuestion = 9999.99; // Arbitrary high value for no questions answered
    }
    
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/2, (max_x-60)/2, "Your Second/Question: %.2f", SecondPerQuestion);
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Save the player and score to the leaderboard
    Player_info* player = findPlayer(name);
    if (player) {
        addScoreToPlayer(player, SecondPerQuestion);
        mvprintw(max_y/2+2, (max_x-60)/2, "Welcome back, %s! Your new GameRecord has been recorded.", name);
    } else {
        addNewPlayer(name, SecondPerQuestion);
        mvprintw(max_y/2+2, (max_x-60)/2, "Welcome, %s! Your first GameRecord has been recorded.", name);
    }
    
    mvprintw(max_y/2+4, (max_x-60)/2, "Press [y] to return to menu...");
    while (true) {
        int ch = getch();
        if (ch == 'y' || ch == 'Y') {
            break;
        }
    }
    refresh();
    timeout(-1); // Disable timeout
}
