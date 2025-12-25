#include <iostream>
#include <cstdlib>
#include "displaymessage.h"
using namespace std; 
// Note: In main(), don't forget to add #include <ctime> and srand(time(0))

/**
Returns a random error message based on the error type
parameters:
n: Error case number (1-8)
return:
String: containing a random error message for the given case
 Error cases:
  1. Using numbers not in the original 4 cards
  2. Using fewer or more than 4 numbers
  3. Using invalid symbols
  4. Unbalanced or wrong parenthesis
  5. Division by zero
  6. Wrong syntax (consecutive operators or missing operands)
  7. Empty input
  8. Using invalid letters
  
  Each case has 4 different random messages that can be displayed
 */
string displayinvalidmessage(int n) {
  int r = rand() % 4; // Random index for message variation

  // Error case 1: Using numbers not in the original 4 cards
  if (n == 1) {
    switch(r) {
      case 0: return "You're only allowed to use the given cards. Try again!";
      case 1: return "Hey! That number wasn't in your hand. No cheating ";
      case 2: return "Where did you get that number from? Magic?";
      case 3: return "Oops, that card wasn't dealt. Stick to the originals.";
    }
  }

  // Error case 2: Using fewer or more than 4 numbers
  else if (n == 2) {
    switch (r) {
      case 0: return "You need to use all four numbers — no more, no less!";
      case 1: return "You're missing something... or maybe added too much!";
      case 2: return "Count your numbers. There should be four.";
      case 3: return "Every card deserves a turn! Use all and only four.";
    }
  }

  // Error case 3: Using symbols besides "+", "-", "*", "/", "(", ")" and whitespace
  else if (n == 3) {
    switch (r) { 
      case 0: return "What's that? I only speak math — try using +, -, *, /.";
      case 1: return "That's some ancient hieroglyphs right there";
      case 2: return "Characters and symbols are off-limits! Stick to the numbers and math ops.";
      case 3: return "Unless you're casting spells, those characters don't belong.";
    }
  }

  // Error case 4: Unbalanced or wrong parenthesis
  else if (n == 4) {
    switch (r) { 
      case 0: return "Something's off with your brackets. They're like socks — they need pairs!";
      case 1: return "Missing a parenthesis? Math is picky like that.";
      case 2: return "Nice try, but your parentheses are mismatched!";
      case 3: return "Uh-oh. I think you dropped a bracket somewhere.";
    }
  }

  // Error case 5: Division by zero
  else if (n == 5) {
    switch (r) { 
      case 0: return "Whoa there! Dividing by zero tears the universe apart ";
      case 1: return "Math meltdown! You tried to divide by zero.";
      case 2: return "Zero can't be a divider. It's just not built that way.";
      case 3: return "Careful! Division by zero is like stepping into a black hole.";
    }
  }

  // Error case 6: Wrong syntax (consecutive operators or missing operands)
  else if (n == 6) {
    switch (r) { 
      case 0: return "Operators need numbers to work with — they're picky.";
      case 1: return "You gave me a puzzle I can't solve. Check your math!";
      case 2: return "Syntax error! Your math sentence doesn't make sense.";
      case 3: return "That's not how math talks. Try again!";
    }
  }

  // Error case 7: Empty input
  else if (n == 7) {
    switch (r) { 
      case 0: return "You gave me... nothing. I need an answer!";
      case 1: return "Blank? Even the cards are confused";
      case 2: return "Don't be shy! Type in your answer.";
      case 3: return "Hello? Anyone there? Your input is empty.";
    }
  }

  // Error case 8: Using letters other than "j", "q", "k" and "a" (characters for jack, queen, king and ace)
  else if (n == 8) {
    switch (r) { 
      case 0: return "Unless your calculator speaks English, words won't work here!";
      case 1: return "This isn't a spelling bee — try using numbers instead.";
      case 2: return "I see letters where there should be digits. Math got confused!";
      case 3: return "Nice try, but I only understand numbers.";
    }
  }
  return "Unknown error";
}

/**
Returns a random message for incorrect (but valid) answers
return:
String: containing a random encouragement/error message
  
Provides 8 different random messages that can be displayed when
the user's answer is mathematically valid but doesn't equal 24
 */
string displayincorrectmessage() {
  int r = rand() % 8; // Random index for message variation
  switch (r) {
    case 0: return "Hmm... That's not quite 24. Try Again!";
    case 1: return "Close, but math says nope.";
    case 2: return "Not the answer we're looking for. Double-check your numbers!";
    case 3: return "Boom! Just kidding, that's a wrong one.";
    case 4: return "Good effort, but that doesn't add up to 24!";
    case 5: return "You're in the ballpark, but the math's not quite right.";
    case 6: return "So close, yet so far! 24 is still waiting...";
    case 7: return "Wrong result. Don't worry — even Einstein had bad days.";
  }
  return "Unknown error";
}
