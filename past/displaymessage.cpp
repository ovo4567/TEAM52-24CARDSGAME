#include <iostream>
#include <cstdlib>
#include "displaymessage.h"
using namespace std; 
//later in main(), dont forget to add #include <ctime> and srand(time(0))

void displayinvalidmessage(int n){
  int r = rand() % 4;

  //Error case 1: Using numbers not in the original 4 cards
  if (n == 1){
    switch(r){
      case 0: cout << "You’re only allowed to use the given cards. Try again!" << endl; break;
      case 1: cout << "Hey! That number wasn’t in your hand. No cheating " << endl; break;
      case 2: cout << "Where did you get that number from? Magic?" << endl; break;
      case 3: cout << "Oops, that card wasn’t dealt. Stick to the originals." << endl; break;
    }
  }

  //Error case 2: Using fewer or more than 4 numbers
  else if (n == 2){
    switch (r){
      case 0: cout << "You need to use all four numbers — no more, no less!" << endl; break;
      case 1: cout << "You're missing something… or maybe added too much!" << endl; break;
      case 2: cout << "Count your numbers. There should be four." << endl; break;
      case 3: cout << "Every card deserves a turn! Use all and only four." << endl; break;
    }
  }

  //Error case 3: Using symbols besides "+", "-", "*", "/", "(", ")" and whitespace
  else if (n == 3){
    switch (r){ 
      case 0: cout << "What’s that? I only speak math — try using +, -, *, /." << endl; break;
      case 1: cout << "That’s some ancient hieroglyphs right there" << endl; break;
      case 2: cout << "characters and symbols are off-limits! Stick to the numbers and math ops." << endl; break;
      case 3: cout << "Unless you’re casting spells, those characters don’t belong." << endl; break;
    }
  }

  //Error case 4: Unbalanced or wrong parenthesis
  else if (n == 4) {
    switch (r){ 
      case 0: cout << "Something’s off with your brackets. They’re like socks — they need pairs!" << endl; break;
      case 1: cout << "Missing a parenthesis? Math is picky like that." << endl; break;
      case 2: cout << "Nice try, but your parentheses are mismatched!" << endl; break;
      case 3: cout << "Uh-oh. I think you dropped a bracket somewhere." << endl; break;
    }
  }

  //Error case 5: Division by zero
  else if (n == 5){
    switch (r){ 
      case 0: cout << "Whoa there! Dividing by zero tears the universe apart " << endl; break;
      case 1: cout << "Math meltdown! You tried to divide by zero." << endl; break;
      case 2: cout << "Zero can’t be a divider. It’s just not built that way." << endl; break;
      case 3: cout << "Careful! Division by zero is like stepping into a black hole." << endl; break;
    }
  }

  //Error case 6: Wrong syntax (consecutive operators or missing operands)
  else if (n == 6){
    switch (r){ 
      case 0: cout << "Operators need numbers to work with — they’re picky." << endl; break;
      case 1: cout << "You gave me a puzzle I can’t solve. Check your math!" << endl; break;
      case 2: cout << "Syntax error! Your math sentence doesn’t make sense." << endl; break;
      case 3: cout << "That’s not how math talks. Try again!" << endl; break;
    }
  }

  //Error case 7: Empty input
  else if (n == 7){
    switch (r){ 
      case 0: cout << "You gave me… nothing. I need an answer!" << endl; break;
      case 1: cout << "Blank? Even the cards are confuse " << endl; break;
      case 2: cout << "Don’t be shy! Type in your answer." << endl; break;
      case 3: cout << "Hello? Anyone there? Your input is empty." << endl; break;
    }
  }

  //Error case 8: Using letters other than "j", "q", "k" and "a" (characters for jack, queen, king and ace)
  else if (n == 8){
    switch (r){ 
      case 0: cout << "Unless your calculator speaks English, words won’t work here!" << endl; break;
      case 1: cout << "This isn't a spelling bee — try using numbers instead." << endl; break;
      case 2: cout << "I see letters where there should be digits. Math got confused!" << endl; break;
      case 3: cout << "Nice try, but I only understand numbers." << endl; break;
    }
  }

  cout << "\n\n"; //adjust later for the sake of the ui beauty team
}

void displayincorrectmessage(){
  int r = rand() % 8; 
  switch (r){
    case 0: cout << "Hmm… That’s not quite 24. Try Again!"; break;
    case 1: cout << "Close, but math says nope."; break;
    case 2: cout << "Not the answer we’re looking for. Double-check your numbers!"; break;
    case 3: cout << "Boom! Just kidding, that’s a wrong one."; break;
    case 4: cout << "Good effort, but that doesn’t add up to 24!"; break;
    case 5: cout << "You're in the ballpark, but the math's not quite right."; break;
    case 6: cout << "So close, yet so far! 24 is still waiting..."; break;
    case 7: cout << "Wrong result. Don't worry — even Einstein had bad days."; break;
  }
  cout "\n\n" //can adjust once again boys
}

