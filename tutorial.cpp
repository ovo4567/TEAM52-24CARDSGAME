//from Sean

#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <utility> 
#include "tutorial.h"
#include "generate.h"
#include <iostream>
#include "tutorialminigame.h"
#include "takeinput.h"
#include "displaymessage.h"
using namespace std;

void displayCardsTutorial(const vector<pair<int, int>>& cards) {
    int card_width = 11;
    int card_height = 9;
    int spacing_x = 3;
    int start_x = 0;
    int start_y = getcury(stdscr) + 1;

    for (int i = 0; i < 4; ++i) {
        int pos_x = start_x + i * (card_width + spacing_x);
        int pos_y = start_y;
        
        string* card = getCard(cards[i].first, cards[i].second);
        if (card) {
            for (int line = 0; line < 9; ++line) {
                mvprintw(pos_y + line, pos_x, "%s", card[line].c_str());
            }
        }
    }
    // Move the cursor down to avoid overwriting the cards
    move(start_y + card_height, 0);
}

void typeText(const std::string& text, int delay) {
    for (char c : text) {
        addch(c);
        refresh();
        usleep(delay);
    }
}

void printCentered(const std::string& text, int row, int delay) {
    if (has_colors()) attron(COLOR_PAIR(1)); //green
    int col = (COLS - text.length()) / 2;
    move(row, col);
    typeText(text, delay);
    if (has_colors()) attroff(COLOR_PAIR(1));
}

void tutorialminigame() {
    vector<pair<int, int>> cards;
    clear();
    // Get dimensions
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int intmode = 2;
    double cardsnumsindouble[4];
    int errorCase = -1;
    bool correct = false;
    string themessage, hints;
    cards = {make_pair(5, 0), make_pair(6, 1), make_pair(4, 2), make_pair(2, 3)}; //0=Diamond, 1=Club, 2=Heart, 3=Spade
    int i=0;
    for (const auto& p : cards) {
        if (p.first >= 10){
            cardsnumsindouble[i] = 10;
        }
        else{
            cardsnumsindouble[i] = p.first;
        }
        i++;
    }
    while (true) { //Game1
        clear();
        displayCards(cards);
        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(1));
        mvprintw(2, (max_x-15)/2, "Case 1: using card 2-10");
        mvprintw(25 + 3, (max_x-50)/2, "[h] for a hint, [q] to quit");
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(1));

        takeinputpanel(cardsnumsindouble,intmode,errorCase,correct);

        attron(A_BOLD);
        if (has_colors()) attron(COLOR_PAIR(3)); //most of the display are error cases

        if (errorCase == -1) {
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(3));
            return;
        } 
        else if (errorCase == -2) { //hints
            hints = displaytutorialhint(1);
            if (has_colors()) attroff(COLOR_PAIR(3));
            if (has_colors()) attron(COLOR_PAIR(2));
            mvprintw(25+10, (max_x-50)/2, hints.c_str());
            if (has_colors()) attroff(COLOR_PAIR(2));
            refresh();
        }
        else if (errorCase == -3) { //if the player type 's' not in time
            continue;
            //break;
        }
        else if (errorCase == 0) {
            if (correct) {
                if (has_colors()) attroff(COLOR_PAIR(3));
                if (has_colors()) attron(COLOR_PAIR(1));
                mvprintw(25+10, (max_x-50)/2, "CORRECT! You made 24!");
                if (has_colors()) attroff(COLOR_PAIR(1));
                refresh();
                getch(); //could be removed...
                break;
            }
            else {
                themessage = displayincorrectmessage();
                mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                refresh();
            }
        }
        else if (errorCase >= 1) {
            themessage = displayinvalidmessage(errorCase);
            mvprintw(25+10, (max_x-50)/2, themessage.c_str());
            refresh();
        }
        attroff(A_BOLD);
        if (has_colors()) attroff(COLOR_PAIR(3));
        getch();
    }
    //Game2
    intmode = 2;
    errorCase = -1;
    correct = false;
    cards = {make_pair(11, 3), make_pair(5, 1), make_pair(7, 0), make_pair(3, 2)};
    i=0;
    for (const auto& p : cards) {
        if (p.first >= 10){
            cardsnumsindouble[i] = 10;
        }
        else{
            cardsnumsindouble[i] = p.first;
        }
        i++;
    }
    while (true) { //Game2
            clear();
            displayCards(cards);
            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(1));
            mvprintw(2, (max_x-15)/2, "Case 2: using FACE cards (JQK)");
            mvprintw(25 + 3, (max_x-50)/2, "[h] for a hint, [q] to quit");
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(1));

            takeinputpanel(cardsnumsindouble,intmode,errorCase,correct);

            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(3));

            if (errorCase == -1) {
                attroff(A_BOLD);
                if (has_colors()) attroff(COLOR_PAIR(3));
                return;
            } 
            else if (errorCase == -2) { //hints
                hints = displaytutorialhint(2);
                if (has_colors()) attroff(COLOR_PAIR(3));
                if (has_colors()) attron(COLOR_PAIR(2));
                mvprintw(25+10, (max_x-50)/2, hints.c_str());
                if (has_colors()) attroff(COLOR_PAIR(2));
                refresh();
            }
            else if (errorCase == -3) { //if the player type 's' not in time
                continue;
                //break;
            }
            else if (errorCase == 0) {
                if (correct) {
                    if (has_colors()) attroff(COLOR_PAIR(3));
                    if (has_colors()) attron(COLOR_PAIR(1));
                    mvprintw(25+10, (max_x-50)/2, "CORRECT! You made 24!");
                    if (has_colors()) attroff(COLOR_PAIR(1));
                    refresh();
                    getch(); //could be removed...
                    break;
                }
                else {
                    themessage = displayincorrectmessage();
                    mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                    refresh();
                }
            }
            else if (errorCase >= 1) {
                themessage = displayinvalidmessage(errorCase);
                mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                refresh();
            }
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(3));
            getch();
    }
    //Game3
    intmode = 4; //mode 4 for treating A as 1, mode 5 for treating A as 11
    errorCase = -1;
    correct = false;
    cards = {make_pair(10, 3), make_pair(1, 1), make_pair(5, 0), make_pair(3, 2)};
    i=0;
    for (const auto& p : cards) {
        if (p.first >= 10){
            cardsnumsindouble[i] = 10;
        }
        else{
            cardsnumsindouble[i] = p.first;
        }
        i++;
    }
    while (true) { //Game3
            clear();
            displayCards(cards);
            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(1));
            mvprintw(2, (max_x-15)/2, "Case 3: ace the ACE case (1 or 11)");
            mvprintw(25 + 3, (max_x-50)/2, "[h] for a hint, [q] to quit");
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(1));
            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(3));
            if (intmode == 4) {
                mvprintw(25 + 5, (max_x-50)/2, "Please treat A as 1");
            }
            else if (intmode == 5) {
                mvprintw(25 + 5, (max_x-50)/2, "Please treat A as 11 this time");
            }
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(3));
            
            takeinputpanel(cardsnumsindouble,intmode,errorCase,correct);

            attron(A_BOLD);
            if (has_colors()) attron(COLOR_PAIR(3));

            if (errorCase == -1) {
                attroff(A_BOLD);
                if (has_colors()) attroff(COLOR_PAIR(3));
                return;
            } 
            else if (errorCase == -2) { //hints
                hints = (intmode == 4) ? displaytutorialhint(3) : displaytutorialhint(4);
                if (has_colors()) attroff(COLOR_PAIR(3));
                if (has_colors()) attron(COLOR_PAIR(2));
                mvprintw(25+10, (max_x-50)/2, hints.c_str());
                if (has_colors()) attroff(COLOR_PAIR(2));
                refresh();
            }
            else if (errorCase == -3) { //if the player type 's' not in time
                continue;
            }
            else if (errorCase == 0) {
                if (correct) {
                    if (has_colors()) attroff(COLOR_PAIR(3));
                    if (has_colors()) attron(COLOR_PAIR(1));
                    mvprintw(25+10, (max_x-50)/2, "CORRECT! You made 24!");
                    if (has_colors()) attroff(COLOR_PAIR(1));
                    refresh();
                    if (intmode == 4) {
                        intmode = 5; //no break, because part2
                    }
                    else if (intmode == 5) {
                        getch();
                        break;
                    }
                }
                else {
                    themessage = displayincorrectmessage();
                    mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                    refresh();
                }
            }
            else if (errorCase >= 1) {
                themessage = displayinvalidmessage(errorCase);
                mvprintw(25+10, (max_x-50)/2, themessage.c_str());
                refresh();
            }
            attroff(A_BOLD);
            if (has_colors()) attroff(COLOR_PAIR(3));
            getch();
    }
}

void displayTutorial() {
    clear();
    int row = 2;

    vector<pair<int, int>> cards = {make_pair(2, 0), make_pair(11, 1), make_pair(13, 2), make_pair(1, 3)}; //0=Diamond, 1=Club, 2=Heart, 3=Spade
    
    // General Information
    printCentered("General Information", row);
    row += 2;
    typeText("\n\nIn order to have the best gaming experience, we suggest you play this game in full screen.\n\nThe game is called “24 Cipher”. In this game, you ought to make a value of 24 by using all the given 4 random cards with\n\n");
    typeText("Addition, Subtraction, Multiplication, and Division.\n\n");
    typeText("The cards can only be used once for each question, but you can use the same operations multiple times.\n\n");
    typeText("Card values are as follows:\n");
    
    displayCardsTutorial(cards);
    typeText("\n");
    
    typeText("2–10 : the number itself\nJ,Q,K : 10\nAce : 1 or 11\n");
    if (has_colors()) attron(COLOR_PAIR(1));
    typeText("\nPress any key to continue...");
    if (has_colors()) attroff(COLOR_PAIR(1));
    //sleep(2);
    getch();

    clear();
    row = 2;

    // Input Types
    printCentered("The type of input that the game accepts", row);
    row += 2;
    typeText("\n\nThe input main principle is easy: if your primary grade math teacher would accept it, so would the system.\n\n");
    typeText("Don’t worry about the space format. General mathematics precedence still occurs. Most importantly, parentheses usage is supported.\n\n");

    typeText("Valid input examples:\n\n");
    typeText("Q:\n");
    cards = {make_pair(8, 1), make_pair(5, 0), make_pair(4, 2), make_pair(2, 3)};
    displayCardsTutorial(cards);
    typeText("\n");

    typeText("Ans: 8*(5-4+2)\n\n");

    typeText("Q:\n");
    cards = {make_pair(11, 3), make_pair(3, 2), make_pair(7, 0), make_pair(1, 1)};
    displayCardsTutorial(cards);
    typeText("\n");
    
    typeText("Ans: j*3-7+a\n");
    typeText("Exp: A values 1 in this case\n\n");

    typeText("Types of invalid syntax:\n- Using a different set of cards from the question\n- Using the cards more than once or not using all 4 cards\n- Using invalid symbols and characters beside card letters\n- Unbalanced parentheses\n- Division by 0\n");
    if (has_colors()) attron(COLOR_PAIR(1));
    typeText("\nPress any key to continue...");
    if (has_colors()) attroff(COLOR_PAIR(1));
    //sleep(2);
    getch();

    clear();
    row = 2;

    // Game Modes
    printCentered("Three Different Game Modes:", row);
    row += 2;
    if (has_colors()) attron(COLOR_PAIR(2));
    typeText("\n\nEasy Mode");
    if (has_colors()) attroff(COLOR_PAIR(2));
    typeText("\nIn this mode, you can ONLY use + and - operators. Every question here is guaranteed to have a solution. Type 'h' for help.");

    if (has_colors()) attron(COLOR_PAIR(1));
    typeText("\n\nClassic Mode");
    if (has_colors()) attroff(COLOR_PAIR(1));
    typeText("\nThis is the traditional 24 Game you know and love. All four operators (+, -, *, /) are available. Questions are solvable, and hints are available.");

    if (has_colors()) attron(COLOR_PAIR(3));
    typeText("\n\nTime Attack Mode");
    if (has_colors()) attroff(COLOR_PAIR(3));
    typeText("\nQuestions might NOT have a solution, and you’ll have to decide if you want to solve or skip. No hints here. Scores will be saved to the leaderboard.");

    typeText("\n\nImportant: Usernames are case-sensitive.\n\n");
    if (has_colors()) attron(COLOR_PAIR(1));
    typeText("\nPress any key to continue...");
    if (has_colors()) attroff(COLOR_PAIR(1));
    //sleep(2);
    getch();

    clear();
    row = 2;

    // End
    printCentered("Have you understood the tutorials?", row);
    row += 2;
    printCentered("Do you wish to try out some introduction questions? (Y/N)", row);
    //typeText("Have you understood the tutorials?\nDo you wish to try out some introduction questions? (Y/N)\n");
    refresh();
    int ch;
    do {
        ch = getch();
    } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
    if (ch == 'Y' || ch == 'y') {
        tutorialminigame();
    } else {
        clear();
        row = 2;
        printCentered("Exiting tutorial...", row);
        refresh();
        sleep(1);
    }
}
