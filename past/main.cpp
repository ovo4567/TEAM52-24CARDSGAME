#include<iostream>
#include<ctime>
#include<iomanip>
#include<cstdlib>

#include "24cardgame.h"

/*
int main(){
	menu(); //amoss 
	cin>>input
	while input != 5: 
		if input == 1: //Play
  			cin>>answer //The user selects mode
			difficulty menu, take answer 
			int type = answer; 
			if answer == 1 : //easy mode 	
				string input = ""
				while (input != "exit") //to "e"
					generate(answer) 	
					//olivia needs to return the 4 cards as a double array that holds 4 numbers for herman to check
					//hints whos in charge?
					do{
						getline(cin, input)
						if input == hint: hinteasymode(4 cards):
					} (while !evaluate(input) && !takeinput(input));
				go back to main menu 

			elif answer == 2: //classic mode
				string input = "" //just a base value so the while loop below can be used laa
				while (input != exit)
					generate(answer) 	
					//olivia needs to return the 4 cards as a double array that holds 4 numbers for herman to check
					do{
						getline(cin, input)
						if input == hint: hintclassicmode(4 cards):
					} (while !evaluate(input) && !takeinput(input);
				go back to main menu 
	
			elif answer == 3: //time attack mode
				INT TYPE = 3
				put in name 	
				cin >> time //time options //1,3,5 mins
				count = 0;
				while time != 0: //timer thing, display later during game timer(int minute)
					generate (TYPE) 
					do{
						getline(cin>>equation);
						if exit : break 
						else if skip: continue;
					}(while !evaluate(input) && !takeinput(input));
					count++;
				double score = time/count; //ALEX CHANGE LATER, SMALLER IS BETTER.
				add_score(SCORE);
				cout << your spend << score << (second == 1)? second :seconds << per questions. u can access later in the leaderboard
				double score == time / count; //time per questions, 
				add_score(score);
				
		elif answer == 2 ://Tutorial
			cout tutorial.cpp //section by section lah wait for user input y, display next section
			if answer == y: 
				can run the second part of tutorial.cpp 
				int minigamelvl = 0; 
					//we cout the first one first later we 
					
			elif answer == n:
				go back to menu()
			else : cout invalid input 
				
		elif answer == 3 : //Leaderboard
			leaderboard()
		elif answer == 4 : //Credit
			cout credits line by line //herman will make the cpp 
		elif answer == 5 : //End
			terminate 
		else : cout invalid 


	what do we need to do after this:
		sean. 
			tutorial.cpp artscii, and how to generate line by line, section bysection
		olivia. 
			change the generate() to return 4 nums
		herman. 
			change the takeinput(): 
					1. take argument int mode.. LATER SEE IF URS GOES ALONG WITH THE ABOVE MAIN.CPP
			does your takeinput() consider A (can be two values), J, Q, K
		
		alex.
			leaderboard() needs to change to second / question.. reverse the sorting settings.
			timer()
		amos. 
			dont get too stressed baby, we love u. see if the logic goes along with the ncurses. file complains if necessary.
	
	return 0;
}
*/

#include <ncursesw/ncurses.h> //uses ncurses library (workable in hku server)
#include <locale.h> // new library for suit symbols
#include <string>
#include <cstdlib>
#include "generate.h"

#ifdef _WIN32 //this is new 14-4
#include <windows.h> // For SetConsoleOutputCP
#endif

void DisplayStartScreen();
void DisplayMenuScreen();
void ShowRules();
void EasyMode();
void ClassicMode();
void TimeAttackMode();
void Leaderboard();

int main(int arc, char **argv) {
    // Set locale to the system's default
    setlocale(LC_ALL, "");

#ifdef _WIN32 //this is new 14-4
    // Set console output code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    // Optional: Set console input code page as well if needed
    // SetConsoleCP(CP_UTF8); 
#endif

    // Initialize
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0); // Hide cursor
    setlocale(LC_ALL, ""); // for card symbols
    
    // Check colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
    }
    DisplayStartScreen();
    endwin();
    return 0;
}

void DisplayStartScreen() {
    clear();
    // Get dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display game title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/3, (max_x-34)/2, "THE 24 GAME - MATHEMATICAL CHALLENGE");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Display start message
    mvprintw(max_y/2, (max_x-25)/2, "Press any key to start...");
    
    refresh();
    getch(); // Wait for user input
    
    // Move to menu screen
    DisplayMenuScreen();
}

void DisplayMenuScreen() {
    while (true) {
        clear();
        
        // Get screen dimensions
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        // Display menu title
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(max_y/5, (max_x-10)/2, "MAIN MENU");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));
        
        // Display menu options
        if (has_colors()) attron(COLOR_PAIR(2));
        mvprintw(max_y/3 + 0, (max_x-20)/2, "1. Display Rules");
        mvprintw(max_y/3 + 2, (max_x-20)/2, "2. Easy Mode");
        mvprintw(max_y/3 + 4, (max_x-20)/2, "3. Classic Mode");
        mvprintw(max_y/3 + 6, (max_x-20)/2, "4. Time-Attack Mode");
        mvprintw(max_y/3 + 8, (max_x-20)/2, "5. Leaderboard");
        mvprintw(max_y/3 + 10, (max_x-20)/2, "6. Exit Game");
        if (has_colors()) attroff(COLOR_PAIR(2));
        
        // Prompt for user choice
        mvprintw(max_y - 5, (max_x-32)/2, "Please enter your choice (1-6): ");
        
        refresh();
        
        // Get user input
        int choice = getch() - '0';  // Convert char to int
        
        // Process user choice
        switch (choice) {
            case 1:
                ShowRules();
                break;
            case 2:
                generate_easy(); //generate.cpp
                break;
            case 3:
                generate_classic(); //generate.cpp
                break;
            case 4:
                generate_timeattack(); //generate.cpp
                break;
            case 5:
                Leaderboard();
                break;
            case 6:
                // Exit the program
                return;
            default:
                // Invalid choice, show error message
                mvprintw(max_y - 3, (max_x-30)/2, "Invalid choice! Try again.");
                refresh();
                napms(1500); // Pause for 1.5 seconds
                break;
        }
    }
}

void ShowRules() {
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Heading
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(3, (max_x-14)/2, "GAME RULES");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Display rules content
    mvprintw(6, 5, "1. Blah.");
    mvprintw(8, 5, "2. Blah blah.");
    mvprintw(10, 5, "3. Blah blah blah.");
    mvprintw(12, 5, "4. Blah blah blah blah.");
    mvprintw(14, 5, "5. Blah blah blah blah blah.");
    
    // Game mode descriptions
    mvprintw(17, 5, "Easy Mode: Blah.");
    mvprintw(19, 5, "Classic Mode: Blah.");
    mvprintw(21, 5, "Time-Attack Mode: Blah.");
    
    // Back instruction
    attron(A_BOLD);
    mvprintw(max_y - 3, (max_x-31)/2, "Press 'q' to return to main menu");
    attroff(A_BOLD);
    
    refresh();
    
    // Wait for 'q' key
    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q');
    
    // Return to menu screen
    return;
}

void EasyMode() {
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display mode title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/4, (max_x-9)/2, "EASY MODE");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Placeholder for easy mode implementation
    mvprintw(max_y/2, (max_x-45)/2, "Something will be implemented here.");
    
    // Back instruction
    attron(A_BOLD);
    mvprintw(max_y - 3, (max_x-31)/2, "Press any key to return to main menu");
    attroff(A_BOLD);
    
    refresh();
    getch();
    
    // Return to menu screen
    return;
}

void ClassicMode() {
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display mode title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/4, (max_x-12)/2, "CLASSIC MODE");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Placeholder for classic mode implementation
    mvprintw(max_y/2, (max_x-48)/2, "Something will be implemented here.");
    
    // Back instruction
    attron(A_BOLD);
    mvprintw(max_y - 3, (max_x-31)/2, "Press any key to return to main menu");
    attroff(A_BOLD);
    
    refresh();
    getch();
    
    // Return to menu screen
    return;
}

void TimeAttackMode() {
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display mode title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/4, (max_x-17)/2, "TIME-ATTACK MODE");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Placeholder for time attack mode implementation
    mvprintw(max_y/2, (max_x-52)/2, "Something will be implemented here.");
    
    // Back instruction
    attron(A_BOLD);
    mvprintw(max_y - 3, (max_x-31)/2, "Press any key to return to main menu");
    attroff(A_BOLD);
    
    refresh();
    getch();
    
    // Return to menu screen
    return;
}

void Leaderboard() {
    clear();
    
    // Get screen dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Display leaderboard title
    attron(A_BOLD);
    if (has_colors()) attron(COLOR_PAIR(1));
    mvprintw(max_y/4, (max_x-11)/2, "LEADERBOARD");
    attroff(A_BOLD);
    if (has_colors()) attroff(COLOR_PAIR(1));
    
    // Placeholder for leaderboard implementation
    mvprintw(max_y/2, (max_x-40)/2, "Leaderboard will be displayed here.");
    
    // Back instruction
    attron(A_BOLD);
    mvprintw(max_y - 3, (max_x-31)/2, "Press any key to return to main menu");
    attroff(A_BOLD);
    
    refresh();
    getch();
    
    // Return to menu screen
    return;
}
