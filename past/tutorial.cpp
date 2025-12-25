//from Sean

#include <ncurses.h>
#include <unistd.h>
#include <string>
#include "tutorial.h"

void typeText(const std::string& text, int delay) {
    for (char c : text) {
        addch(c);
        refresh();
        usleep(delay);
    }
}

void printCentered(const std::string& text, int row, int delay) {
    int col = (COLS - text.length()) / 2;
    move(row, col);
    typeText(text, delay);
}

void displayTutorial() {
    clear();
    int row = 2;

    // General Information
    printCentered("General Information", row);
    row += 2;
    typeText("\nThe game is called “24 cards game”. In this game, you ought to make a value of 24 by using all the given 4 random cards with addition, subtraction, multiplication, and division.\n\n");
    typeText("The cards can only be used once for each question, but you can use the same operations multiple times.\n\n");
    typeText("Card values are as follows:\n");
    typeText("┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐\n");
    typeText("│ 2 │ │ J │ │ Q │ │ K │ │ A │\n");
    typeText("└───┘ └───┘ └───┘ └───┘ └───┘\n\n");
    typeText("2–10 : the number itself\nJ,Q,K : 10\nAce : 1 or 11\n");
    sleep(2);

    clear();
    row = 2;

    // Input Types
    printCentered("The type of input that the game accepts", row);
    row += 2;
    typeText("\nThe input main principle is easy: if your primary grade math teacher would accept it, so would the system.\n\n");
    typeText("Don’t worry about the space format. General mathematics precedence still occurs. Most importantly, parentheses usage is supported.\n\n");

    typeText("Valid input examples:\n\n");
    typeText("Q:\n");
    typeText("┌───┐ ┌───┐ ┌───┐ ┌───┐\n│ 8 │ │ 5 │ │ 4 │ │ 2 │\n│ ♣ │ │ ♦ │ │ ♥ │ │ ♠ │\n└───┘ └───┘ └───┘ └───┘\n\n");
    typeText("Ans: 8 *(5- 4 + 2 )\n\n");

    typeText("Q:\n");
    typeText("┌───┐ ┌───┐ ┌───┐ ┌───┐\n│ J │ │ 3 │ │ 7 │ │ A │\n│ ♠ │ │ ♥ │ │ ♦ │ │ ♣ │\n└───┘ └───┘ └───┘ └───┘\n\n");
    typeText("Ans: J*3 -A +7\n");
    typeText("Exp: A values 1 in this case\n\n");

    typeText("Types of invalid syntax:\n- Using a different set of cards from the question\n- Using the cards more than once or not using all 4 cards\n- Using invalid symbols and characters beside card letters\n- Unbalanced parentheses\n- Division by 0\n");
    sleep(2);

    clear();
    row = 2;

    // Game Modes
    printCentered("Three Different Game Modes:", row);
    row += 2;
    typeText("\nEasy Mode\nIn this mode, you can ONLY use + and - operators. Every question here is guaranteed to have a solution. Type 'hint' for help.\n\n");

    typeText("Classic Mode\nThis is the traditional 24 Game you know and love. All four operators (+, -, *, /) are available. Questions are solvable, and hints are available.\n\n");

    typeText("Time Attack Mode\nQuestions might NOT have a solution, and you’ll have to decide if you want to solve or skip. No hints here. Scores will be saved to the leaderboard.\n\n");
    typeText("Important: Usernames are case-sensitive.\n\n");
    sleep(2);

    clear();

    // End
    typeText("Have you understood the tutorials?\nDo you wish to try out some introduction questions? (Y/N)\n");
    refresh();
}
