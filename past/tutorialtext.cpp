#include <iostream>
#include "tutorialtext.h"
#include <unistd.h>
using namespace std; 


void printtutorial(){

}

/* this is the tutorial text from the docs

//persection wait 2 secs
//make a typing animation please, except for cards, also print justified with centered allignment, thanks

General Information //section 1
The game is called “24 cards game”. In this game, you ought to make a value of 24 by using all the given 4 random cards with addition, subtraction, multiplication, and division. The cards can only be used once for each question, but you can use the same operations multiple times. 

Card values are as follows: 
┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐
│ 2 │ │ J │ │ Q │ │ K │ │ A │
└───┘ └───┘ └───┘ └───┘ └───┘

2–10	: the number itself
J,Q,K	: 10 
Ace	: 1 or 11

The type of input that the game accepts
The input main principle is easy: if your primary grade math teacher would accept it, so would the system. Don’t worry about the space format. General mathematics precedence still occurs. Most importantly, parentheses usage is supported. 

Valid input examples: //section 2
Q: 
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ 8 │ │ 5 │ │ 4 │ │ 2 │
│ ♣ │ │ ♦ │ │ ♥ │ │ ♠ │
└───┘ └───┘ └───┘ └───┘
Ans: 8 *(5- 4 +   2 )

Q: 
┌───┐ ┌───┐ ┌───┐ ┌───┐
│ J │ │ 3 │ │ 7 │ │ A │
│ ♠ │ │ ♥ │ │ ♦ │ │ ♣ │
└───┘ └───┘ └───┘ └───┘
Ans: J*3 -A +7
Exp: A values 1 in this case

Types of invalid syntax:
Using a different set of cards from the question
Using the cards more than once or not using all 4 cards
Using invalid symbols and characters beside card letters
Unbalanced parentheses
Division by 0


Three Different Game Modes: //section 3
Easy Mode
In this mode, you can ONLY use + and - operators. Yes, we truly made it easy for you. On top of that, every question here is guaranteed to have a solution. In case you're stuck, type 'hint' and we'll give you a little nudge — a hint will tell you one operator and one number to start with.

Classic Mode
This is the traditional 24 Game you know and love. All four operators (+, -, *, /) are available. Questions are still solvable, and you can request 'hint' the same way you would in Easy Mode. 

Time Attack Mode
This is where things get serious. Questions might NOT have a solution, and you’ll have to decide if you want to solve or skip. You can skip as many as you want, but your final score depends on how many you solve. Hint' is, unfortunately, NOT available here. However, we still provide you with the card values. Your performance will be recorded on the game's leaderboard, accessible from the homepage. 

Important: Usernames are case-sensitive, and all your score history will be stored under the exact username you enter (“Olivia” and “oLivia” are treated as different players).

Have you understood the tutorials? Do you wish to try out some introduction questions? (Y/N)
*/



  
