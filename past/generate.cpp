// this is for mapping the numbers to the asciicards 

string* getDiamondCard(int number) {
    switch(number) {
        case 1: return diamondA;
        case 2: return diamond2;
        case 3: return diamond3;
        case 4: return diamond4;
        case 5: return diamond5;
        case 6: return diamond6;
        case 7: return diamond7;
        case 8: return diamond8;
        case 9: return diamond9;
        case 10: return diamond10;
        case 11: return diamondJ;
        case 12: return diamondQ;
        case 13: return diamondK;
        default: return nullptr;
    }
}

// Function to get club card
string* getClubCard(int number) {
    switch(number) {
        case 1: return clubA;
        case 2: return club2;
        case 3: return club3;
        case 4: return club4;
        case 5: return club5;
        case 6: return club6;
        case 7: return club7;
        case 8: return club8;
        case 9: return club9;
        case 10: return club10;
        case 11: return clubJ;
        case 12: return clubQ;
        case 13: return clubK;
        default: return nullptr;
    }
}

// Function to get heart card
string* getHeartCard(int number) {
    switch(number) {
        case 1: return heartA;
        case 2: return heart2;
        case 3: return heart3;
        case 4: return heart4;
        case 5: return heart5;
        case 6: return heart6;
        case 7: return heart7;
        case 8: return heart8;
        case 9: return heart9;
        case 10: return heart10;
        case 11: return heartJ;
        case 12: return heartQ;
        case 13: return heartK;
        default: return nullptr;
    }
}

// Function to get spade card
string* getSpadeCard(int number) {
    switch(number) {
        case 1: return spadeA;
        case 2: return spade2;
        case 3: return spade3;
        case 4: return spade4;
        case 5: return spade5;
        case 6: return spade6;
        case 7: return spade7;
        case 8: return spade8;
        case 9: return spade9;
        case 10: return spade10;
        case 11: return spadeJ;
        case 12: return spadeQ;
        case 13: return spadeK;
        default: return nullptr;
    }
}

// General function to get any card based on suit and number
// call getCard function to display the cards 

//retrieve the string function from the above according to the number and suit index 
string* getCard(int number, int suitIndex) {
    switch(suitIndex) {
        case 0: return getDiamondCard(number);
        case 1: return getClubCard(number);
        case 2: return getHeartCard(number);
        case 3: return getSpadeCard(number);
        default: return nullptr;
    }
}

// random generate 4 numbers and random suits for them and store them into cards 
// cards should be an array containing values and suits for 4 numbers 
vector<pair<int, int>> generateOrigCards() {
    vector<pair<int, int>> cards; // Pair: <value, suitIndex>
    for (int i = 0; i < 4; ++i) {
        int value = rand() % 13 + 1; // 1-13 (A=1, J=11, Q=12, K=13)
        int suit = rand() % 4; // Random suit: 0=Diamond, 1=Club, 2=Heart, 3=Spade
        cards.push_back({value, suit});
    }
    return cards;
}



// Convert raw card values to game values (A=1 or 11, J/Q/K=10)
vector<double> getGameValues(const vector<pair<int, int>>& cards, vector<int>& aceChoices) {
    vector<double> values;
    aceChoices.clear();
    for (auto [val, suit] : cards) {
        if (val >= 11) {
            values.push_back(10.0); // J, Q, K = 10
            aceChoices.push_back(-1); // No Ace choice, -1 here just for checking the number is 1 or not 
        } else if (val == 1) {
            int choice = rand() % 2; // Randomly pick 1 or 11 for Ace
            values.push_back(choice ? 11.0 : 1.0);
            aceChoices.push_back(choice); // Store choice (0=1, 1=11)
        } else {
            values.push_back(static_cast<double>(val)); // 2-10
            aceChoices.push_back(-1); // No Ace choice
        }
    }
    return values; // only return only game values in this step 
}


const double TARGET = 24.0;
const double EPSILON = 1e-6; // For floating point comparison

bool solve24(vector<double>& nums, bool easyMode = false) {
    // Base case: if only one number left, check if it's approximately 24
    if (nums.size() == 1) {
        return abs(nums[0] - TARGET) < EPSILON;
    }

    // Try all pairs of numbers
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < nums.size(); ++j) {
            if (i == j) continue; // Skip using the same number twice

            double num1 = nums[i];
            double num2 = nums[j];

            // Create a new vector with remaining numbers
            vector<double> remainingNumbers;
            for (size_t k = 0; k < nums.size(); ++k) {
                if (k != i && k != j) {
                    remainingNumbers.push_back(nums[k]);
                }
            }

            // Try all possible operations
            vector<double> paths;
            
            // Always try addition
            paths.push_back(num1 + num2);
            
            // Always try subtraction (both orders)
            paths.push_back(num1 - num2);
            paths.push_back(num2 - num1);

            // In classic mode, also try multiplication and division

            // if it is classic mode, the bool easymode will be set as False 
            if (!easyMode) {
                paths.push_back(num1 * num2);
                
                // Only try division if not dividing by zero
                if (abs(num2) > EPSILON) {
                    paths.push_back(num1 / num2);
                }
                if (abs(num1) > EPSILON) {
                    paths.push_back(num2 / num1);
                }
            }

            // Try each operation result
            for (double result : paths) {
                remainingNumbers.push_back(result);
                if (solve24(remainingNumbers, easyMode)) {
                    return true;
                }
                remainingNumbers.pop_back(); // Backtrack
            }
        }
    }
    return false;
}


// just for handling Ace condition 
bool isSolvableWithAces(const vector<pair<int, int>>& cards, bool easyMode = false) {
    // First, convert all cards to their base values
    // Aces will be temporarily set to 0 (to be handled later)
    // Face cards (J/Q/K = 11/12/13) become 10
    vector<double> cardValues;
    vector<int> acePositions; // Stores positions of Aces in the cardValues vector
    
    for (size_t i = 0; i < cards.size(); ++i) {
        int cardValue = cards[i].first;
        
        if (cardValue >= 11) { // Face card (Jack, Queen, King)
            cardValues.push_back(10.0);
        } 
        else if (cardValue == 1) { // Ace
            cardValues.push_back(0.0); // Temporary placeholder
            acePositions.push_back(i); // Remember this is an Ace
        } 
        else { // Number card (2-10)
            cardValues.push_back(static_cast<double>(cardValue));
        }
    }

    // If there are no Aces, just check normally
    if (acePositions.empty()) {
        return solve24(cardValues, easyMode);
    }

    // For each Ace, it can be either 1 or 11
    // We need to try all possible combinations
    int numberOfAces = acePositions.size();
    int totalCombinations = 1 << numberOfAces; // 2^numberOfAces possibilities
    
    for (int combination = 0; combination < totalCombinations; ++combination) {
        vector<double> currentValues = cardValues;
        
        // Set each Ace to either 1 or 11 based on the combination
        for (int aceIndex = 0; aceIndex < numberOfAces; ++aceIndex) {
            bool useHighValue = combination & (1 << aceIndex);
            currentValues[acePositions[aceIndex]] = useHighValue ? 11.0 : 1.0;
        }
        
        // Check if this combination works
        if (solve24(currentValues, easyMode)) {
            return true;
        }
    }
    
    // None of the Ace combinations worked
    return false;
}

// Display cards
void displayCards(const vector<pair<int, int>>& cards) {
    cout << "\nGenerated cards:\n";
    for (int line = 0; line < 10; ++line) { // Adjust to 11 if needed
        for (int i = 0; i < 4; ++i) {
            string* card = getCard(cards[i].first, cards[i].second);
            if (card) cout << card[line] << " ";
        }
        cout << endl;
    }
}


//step_2 timeattack, no need to check the issivable

void generateCards(string mode) {
    srand(time(0));
    vector<pair<int, int>> cards;

    if (mode == "timeattack") {
        cout << "Enter your nickname: ";
        cin >> nickname;

        // Check if player exists
        Player_info* player = findPlayer(nickname); // supposed findPlayer has been defined in other funciton 
        
    
        cout << "Generating 4 random cards...\n";
        cards = generateOrigCards();
        displayCards(cards);

        if (player) {
            // Existing player - add new score
            player->scores.push_back(score);
            
        } else {
            // New player - create new record
            addNewPlayer(name, score);
            
        }

    } else {
        cout << "Generating valid 24-game combination...\n";
        int attempts = 0;
        const int MAX_ATTEMPTS = 100;
        bool easyMode = (mode == "easy");   // if choosing classic mode, easymode here will be false 
        while (attempts++ < MAX_ATTEMPTS) {
            cards = generateOrigCards();
            if (isSolvableWithAces(cards, easyMode)) {
                displayCards(cards);
                return;
            }
        }
    }
}

// Main entry points

// step_1 call each function according each mode 
int generate_easy() { generateCards("easy"); return 0; }
int generate_classic() { generateCards("classic"); return 0; }
int generate_timeattack() { generateCards("timeattack"); return 0; }

//takes an int argument of which mode, 1 - easy, 2 - classic, 3 - timeattack
int generate(int choice) {
    switch(choice) {
        case 1: return generate_easy();
        case 2: return generate_classic();
        case 3: return generate_timeattack();
        default:
            cout << "Invalid choice!\n";
            return 1;
    }
}
