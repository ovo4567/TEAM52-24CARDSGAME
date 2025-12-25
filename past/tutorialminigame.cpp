#include <iostream>
#include <cstdlib>
#include "tutorialminigame.h"
//INCLUDE HERMANS FUNCTION HEADER!!!!
using namespace std; 

Void displaytutorialhint(int case){
  int r = rand() % 4;
	if (case == 1){ //2-10 cards minigame
    switch(r){
    	case 0: cout << "Start with multiplying 5 by something." << endl << break;
    	case 1: cout << "Start with subtracting 6 by something." << endl << break;
    	case 2: cout << "Start ith adding 4 by something." << endl << break;
      }
  }

  else if (case == 2){ //JQK case
    switch(r){
	    case 0: cout << "Start with adding 5 by something." << endl << break;
    	case 1: cout << "Start with subtracting  by something." << endl << break;
    	case 2: cout << "Start with subtracting 5 by something." << endl << break;
    }
  }

  else if (case == 3){ //when A is valued 1 
    switch(r){
      case 0: cout << "Start by multiplying 3 with something." << endl << break;
    	case 1: cout << "Start by subtracting 10 with something." << endl << break;
    	case 2: cout << "Start by adding 5 with something." << endl << break;
    }
  }

  else if (case == 4) //when A is valued 11
    switch(r){
      case 0: cout << "Start by multiplying 3 with something." << endl << break;
    	case 1: cout << "Start by subtracting A with something." << endl << break;
    	case 2: cout << "Start by multiplying 10 with something." << endl << break;
    }
}

//later add for different case ui outputing aswell this is the draft so far, check out the draft in the docs. modify the main as well. 
