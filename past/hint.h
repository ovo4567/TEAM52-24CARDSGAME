#ifndef HINT_H
#define HINT_H

#include <vector>
#include <string>
#include <utility> // for pair

using namespace std;

// Function declarations
string getEasyModeHint(const vector<pair<int, int>>& cards);
int hint_easy();
string getClassicModeHint(const vector<pair<int, int>>& cards);
int hint_classic();

#endif // HINT_H
