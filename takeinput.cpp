//Functions contained in the file: getInput(), calculate(), evalInput(), ansCheck(), takeinputpanel()
#include<iostream>
#include<string>
#include<algorithm>
#include<stack>
#include<cctype>
#include<unordered_map>
#include<vector>
#include <ncursesw/ncurses.h>
using namespace std;

//Function input: None
//Function output: A string formula
//The function gets the input from the player without invalid input/incorrect answer evaluation, strips away the whitespaces, converts uppercase letters into lowercase, converts 'j','q','k' into "10", converts 'a' into '1', and returns trimmed input from the player
string getInput() {
  string input,modifiedInput;
  char inputinarray[100];
  char ch;
  int max_y, max_x, input_x, input_y;
  getmaxyx(stdscr, max_y, max_x);
  input_y = 25+7;
  input_x = (max_x-50)/2;

  mvprintw(input_y, input_x, "Make 24: ");
  move(input_y, input_x+9);// Move cursor to input position
  refresh();
  echo(); // Show typed characters
  curs_set(1); // Show cursor
  getnstr(inputinarray, sizeof(inputinarray) - 1); //input
  noecho();
  curs_set(0); // Hide cursor

  for (int i = 0; inputinarray[i] != '\0'; ++i) {
    input += inputinarray[i];
  }
  // Special commands
  if (input == "q" || input == "Q") {
    return "q";
  }
  if (input == "h" || input == "H") {
    return "h";
  }
  if (input == "s" || input == "S") {
    return "s";
  }
  // Process input (trim whitespaces, convert to lowercase)
  for (char character : input) {
    if (!isspace(character)) { // Trims away whitespaces
      character = tolower(character); // Converts uppercase letters into lowercase
      if (character=='j' || character=='q' || character=='k') { // Turns 'j', 'q', 'k' into the number 10
        modifiedInput += "10";
      }
      else if (character == 'a') { // Turns 'a' into the number 1
        modifiedInput += '1';
      }
      else {
        modifiedInput += character;
      }
    }
  }
  
  return modifiedInput;
}

//Function input: A string formula
//Function output: A double number
//The function calculates the input given by the player
double calculate(string expression) {
  unordered_map<char, int> precedence = {{'+',1}, {'-',1}, {'*',2}, {'/',2}};
  stack<double> values;
  stack<char> ops;
  auto applyOperation = [&]() {
    double right = values.top(); values.pop();
    double left = values.top(); values.pop();
    char op = ops.top(); ops.pop();
    switch (op) {
      case '+': values.push(left + right); break;
      case '-': values.push(left - right); break;
      case '*': values.push(left * right); break;
      case '/': values.push(left / right); break;
    }
  };
  // Helper to determine if a '-' is unary
  auto isUnaryMinus = [&](size_t i) {
    return expression[i] == '-' && 
           (i == 0 || expression[i-1] == '(' || precedence.count(expression[i-1]));
  };
  for (size_t i = 0; i < expression.length(); ++i) {
    if (isdigit(expression[i])) {
      string numberBuffer;
      while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
        numberBuffer += expression[i++];
      }
      values.push(stod(numberBuffer));
      --i; // Adjust index
    }
    else if (isUnaryMinus(i)) {
      // Handle unary minus by pushing 0 and making it a binary operation
      values.push(0);
      ops.push('-');
    }
    else if (precedence.count(expression[i])) {
      while (!ops.empty() && ops.top() != '(' && 
             precedence[ops.top()] >= precedence[expression[i]]) {
        applyOperation();
      }
      ops.push(expression[i]);
    }
    else if (expression[i] == '(') {
      ops.push(expression[i]);
    }
    else if (expression[i] == ')') {
      while (ops.top() != '(') {
        applyOperation();
      }
      ops.pop(); // Remove '('
    }
  }
  while (!ops.empty()) {
    applyOperation();
  } 
  return values.top();
}

//Function input: A string formula, a double array cards containing the 4 drawn cards, an integer mode number
//Function output: An integer error case number
//The function evaluates the input from the player and return respective error case number
int evalInput(string input,double cards[4],int mode){
  string digitList;
  vector<double> usedNums;
  if (mode==1){//Check for usage of "*" and "/"
    for (char c:input){
      if (c=='*'||c=='/'){
        //cout<<"Used '*' or '/' in easy mode"<<endl;
        return 6; //Categorize as error case 6 (Syntax error) just for now
      }
    }
  }
  //Check for empty input
  if (!input.empty()){
    for (char character:input){
      //Check for use of invalid letters
      if (isalpha(character)){
        return 8; //Error case 8: Using forbidden letters
      }
      //Check for use of invalid symbols
      else if (!isdigit(character)&&character!='*'&&character!='/'&&character!='-'&&character!='+'&&character!='('&&character!=')'){
        return 3; //Error case 3: Using symbols besides "+", "-", "*", "/"
      }
    }
    //Check for balance of parentheses
    stack<char> parenStack;
    for (char c:input){
      if (c=='('){
        parenStack.push(c);
      }
      else if (c==')'){
        if (parenStack.empty()){
	  return 4; //Error case 4: Unbalanced parenthesis
	}
	parenStack.pop();
      }
    }
    if (!parenStack.empty()){
      return 4; //Error case 4: Unbalaned parenthesis
    }
    //Check for syntax errors (consecutive operators, missing operands)
    bool expectOperand=true;
    for (size_t i=0;i<input.size();i++){
      char c=input[i];
      if (expectOperand){
        if (c=='+'||c=='*'||c=='/'||c==')'){
	  return 6; //Error case 6: Wrong syntax
	}
	else if (c=='-'||c=='('){
	  continue;
	}
	else if (isdigit(c)){
	  string numStr;
	  while (i<input.size()&&isdigit(input[i])){
	    numStr+=input[i++];
	  }
	  i--; //Adjust for loop
	  double num;
	  try{
	    num=stod(numStr);
	  }
	  catch(...){
	    return 6; //Error case 6: Invalid syntax
	  }
	  usedNums.push_back(num);
	  expectOperand=false;
	}
      }
      else{
        if (c=='+'||c=='-'||c=='*'||c=='/'){
	  expectOperand=true;
	}
	else if (isdigit(c)||c=='('){ //Check if the operator is missing
	  return 6; //Error case 6: Invalid syntax
	}
      }
    }
    if (expectOperand){//Check if the input ends with an operator
      return 6; //Error case 6: Invalid syntax
    }
    //Check if the numbers in input match the drawn numbers
    if (usedNums.size()!=4){ //Check how many numbers in input
      return 2; //Error case 2: Using less or more than 4 numbers
    }
    vector<double> drawnCards(cards,cards+4);
    vector<double> usedCards=usedNums;
    sort(drawnCards.begin(),drawnCards.end());
    sort(usedCards.begin(),usedCards.end());
    //Check if the drawn cards match the cards in input
    if (drawnCards!=usedCards){
      return 1; //Error case 1: Using numbers not in the drawn 4 cards
    }
    //Check for division by zero
    for (size_t i=0;i<input.size();i++){
      if (input[i]=='/'){
        size_t j=i+1;
	int parenLevel=0;
	string denominator;
	//Extract the full denominator
	while (j<input.size()){
	  char c=input[j];
	  if (c=='('){
	    parenLevel++;
	  }
	  else if (c==')'){
	    if (parenLevel==0){
	      break;
	    }
	    parenLevel--;
	  }
	  denominator+=c;
	  j++;
	  if (parenLevel==0&&(j==input.size()||input[j]=='+'||input[j]=='-'||input[j]=='*'||input[j]=='/')){
	    break;
	  }
	}
	double denomValue=calculate(denominator);
	if (denomValue==0){
	  return 5; //Error case 5: Division by zero
	}
      }
    }
    return 0; //Input is valid
  }
  else{
    return 7; //Error case 7: Empty input
  }
}

//Function input: A string formula, a double array cards containing the 4 drawn cards, an integer mode number
//Function output: A boolean of whether the calculated result equals to 24
//This function checks if user's input equals to 24
bool ansCheck(string input,double cards[4],int mode){
  string newInput="";
  if (mode==4){ //Tutorial part 1 (take ace as 1)
    if (calculate(input)==24){
      //cout<<"(Tutorial 1) CORRECT ANSWER"<<endl;
      return true;
    }
    else{
      //cout<<"(Tutorial 1) INCORRECT ANSWER! Your answer was "<<calculate(input)<<endl;
      return false;
    }
  }
  else if (mode==5){ //Tutorial part 2 (take ace as 11)
    for (size_t i = 0; i < input.length(); i++) {
      char c = input[i];
      if (c == '1' && (i == 0 || !isdigit(input[i - 1])) && (i == input.length() - 1 || !isdigit(input[i + 1]))) {
        newInput += "11";
      } 
      else {
        newInput += c;
      }
    }
	  
    if (calculate(newInput)==24){
      //cout<<"(Tutorial 2) CORRECT ANSWER"<<endl;
      return true;
    }
    else{
       //cout<<"(Tutorial 2) INCORRECT ANSWER! Your answer was "<<calculate(newInput)<<endl;
       return false;
    }
  }
  else if (find(cards,cards+4,1)!=cards+4){ //Not in tutorial mode & at least 1 ace is drawn
    vector<int> oneIndices;
    for (int i = 0; i <input.size(); ++i) {
      if (input[i] == '1') {
        oneIndices.push_back(i);
      }
    }
    int k=oneIndices.size();
    int totalPermutations = 1 << k; // 2^k possibilities

    for (int mask=0;mask<totalPermutations;++mask){
      string modifiedInput;
      int onePos=0;
      for (int i=0;i<input.size();){
        if (onePos<k&&i==oneIndices[onePos]){
          if (mask&(1<<onePos)){
            modifiedInput+="11";
          } 
	        else{
            modifiedInput+= '1';
          }
          onePos++;
          i++;
        } 
	      else{
          modifiedInput+=input[i];
          i++;
        }
      }
      if (calculate(modifiedInput)==24){
	      return true;
      }
    }
    return false; 
  }
  else{ //Not in tutorial mode & no aces are drawn
    if (calculate(input)==24){
      return true;
    }
    else{
      return false;
    }
  }
}

//Function input: A double array cards containing 4 drawn cards, an integer mode number, an integer error case number, a boolean of whether the user's result is correct
//Function output: None
//The function directs the program to the other functions in this file
void takeinputpanel(double cards[4], int mode, int& errorCase, bool& correct){ //mode=4 for tutorial part 1, mode=5 for tutorial part 2
  //debuged the arguments are fine
  string input;
  //int errorCase;
  double result;
  //bool correct = false;
  input=getInput();
  if (input == "q") {
    errorCase = -1; // Set error case to -1 for quitting
    return; // Quit the game
  }
  else if (input == "h") {
    // Provide a hint (not implemented here)
    errorCase = -2; // Set error case to -2 for hint
    return;
  }
  else if (input == "s") {
    // Show the solution (not implemented here)
    errorCase = -3; // Set error case to -3 for skipping
    return;
  }
  errorCase=evalInput(input,cards,mode);
  if (errorCase==0){ //The input is valid
    correct=ansCheck(input,cards,mode);
  }
}
