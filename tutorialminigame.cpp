#include <iostream>
#include <cstdlib>
#include "tutorialminigame.h"
using namespace std; 

string displaytutorialhint(int case_type){
  int r = rand() % 3;
	if (case_type == 1){ //2-10 cards minigame
    switch(r){
    	case 0: return "Start with multiplying 5 by something.";
    	case 1: return "Start with subtracting 6 by something.";
    	case 2: return "Start with adding 4 by something.";
    }
  }

  else if (case_type == 2){ //JQK case
    switch(r){
	    case 0: return "Start with adding 5 by something.";
    	case 1: return "Start with multiplying 3 by something.";
    	case 2: return "Start with subtracting 5 by something.";
    }
  }

  else if (case_type == 3){ //when A is valued 1 
    switch(r){
      case 0: return "Start by multiplying 3 with something.";
    	case 1: return "Start by subtracting 10 with something.";
    	case 2: return "Start by adding 5 with something.";
    }
  }

  else if (case_type == 4) //when A is valued 11
    switch(r){
      case 0: return "Start by multiplying 3 with something.";
    	case 1: return "Start by subtracting A with something.";
    	case 2: return "Start by multiplying 10 with something.";
    }
  
  return "Error";
}

//later add for different case ui outputing aswell this is the draft so far, check out the draft in the docs. modify the main as well.
