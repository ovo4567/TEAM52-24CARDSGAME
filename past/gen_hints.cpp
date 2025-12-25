#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <utility>

using namespace std;
//"\xE2\x99\xA0" refresents the spade "♠"
//"\xE2\x99\xA3" represents the club "♣"
//"\xE2\x99\xA5" represents the heart "♥"
//"\xE2\x99\xA6" represents the diamond "♦"
//the ascii the cards
string diamondA[] = {
    " _________ ",
    "|A        |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA6    |",
    "|         |",
    "|         |",
    "|        A|",
    " --------- "};

string diamond2[] = {
    " _________ ",
    "|2        |",
    "|    \xE2\x99\xA6    |",
    "|         |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA6    |",
    "|        2|",
    " --------- "};

string diamond3[] = {
    " _________ ",
    "|3        |",
    "|    \xE2\x99\xA6    |",
    "|         |",
    "|    \xE2\x99\xA6    |",
    "|         |",
    "|    \xE2\x99\xA6    |",
    "|        3|",
    " --------- "};

string diamond4[] = {
    " _________ ",
    "|4        |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|         |",
    "|         |",
    "|         |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|        4|",
    " --------- "};

string diamond5[] = {
    " _________ ",
    "|5        |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|         |",
    "|    \xE2\x99\xA6    |",
    "|         |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|        5|",
    " --------- "};

string diamond6[] = {
    " _________ ",
    "|6        |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|         |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|         |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|        6|",
    " --------- "};

string diamond7[] = {
    " _________ ",
    "|7        |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|    \xE2\x99\xA6    |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|         |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|        7|",
    " --------- "};

string diamond8[] = {
    " _________ ",
    "|8        |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|    \xE2\x99\xA6    |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|    \xE2\x99\xA6    |",
    "|  \xE2\x99\xA6   \xE2\x99\xA6  |",
    "|        8|",
    " --------- "};

string diamond9[] = {
    " _________ ",
    "|9  \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|         |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|    \xE2\x99\xA6    |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|         |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6  9|",
    " --------- "};

string diamond10[] = {
    " _________ ",
    "|10 \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|    \xE2\x99\xA6    |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|         |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|    \xE2\x99\xA6    |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6 10|",
    " --------- "};

string diamondJ[] = {
    " _________ ",
    "|J  \xE2\x99\xA6     |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|    \xE2\x99\xA6    |",
    "|  \xE2\x99\xA6 J \xE2\x99\xA6  |",
    "|    \xE2\x99\xA6    |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|     \xE2\x99\xA6  J|",
    " --------- "};

string diamondQ[] = {
    " _________ ",
    "|Q  \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|  \xE2\x99\xA6 Q \xE2\x99\xA6  |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|  \xE2\x99\xA6 \xE2\x99\xA6 \xE2\x99\xA6  |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6  Q|",
    " --------- "};

string diamondK[] = {
    " _________ ",
    "|K  \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|  \xE2\x99\xA6 \xE2\x99\xA6 \xE2\x99\xA6  |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|  \xE2\x99\xA6 K \xE2\x99\xA6  |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6   |",
    "|   \xE2\x99\xA6 \xE2\x99\xA6  K|",
    " --------- "};

string clubA[] = {
    " _________ ",
    "|A        |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA3    |",
    "|         |",
    "|         |",
    "|        A|",
    " --------- "};

string club2[] = {
    " _________ ",
    "|2        |",
    "|    \xE2\x99\xA3    |",
    "|         |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA3    |",
    "|        2|",
    " --------- "};

string club3[] = {
    " _________ ",
    "|3        |",
    "|    \xE2\x99\xA3    |",
    "|         |",
    "|    \xE2\x99\xA3    |",
    "|         |",
    "|    \xE2\x99\xA3    |",
    "|        3|",
    " --------- "};

string club4[] = {
    " _________ ",
    "|4        |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|         |",
    "|         |",
    "|         |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|        4|",
    " --------- "};

string club5[] = {
    " _________ ",
    "|5        |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|         |",
    "|    \xE2\x99\xA3    |",
    "|         |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|        5|",
    " --------- "};

string club6[] = {
    " _________ ",
    "|6        |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|         |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|         |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|        6|",
    " --------- "};

string club7[] = {
    " _________ ",
    "|7        |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|    \xE2\x99\xA3    |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|         |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|        7|",
    " --------- "};

string club8[] = {
    " _________ ",
    "|8        |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|    \xE2\x99\xA3    |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|    \xE2\x99\xA3    |",
    "|  \xE2\x99\xA3   \xE2\x99\xA3  |",
    "|        8|",
    " --------- "};

string club9[] = {
    " _________ ",
    "|9  \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|         |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|    \xE2\x99\xA3    |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|         |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3  9|",
    " --------- "};

string club10[] = {
    " _________ ",
    "|10 \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|    \xE2\x99\xA3    |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|         |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|    \xE2\x99\xA3    |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3 10|",
    " --------- "};

string clubJ[] = {
    " _________ ",
    "|J  \xE2\x99\xA3     |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|    \xE2\x99\xA3    |",
    "|  \xE2\x99\xA3 J \xE2\x99\xA3  |",
    "|    \xE2\x99\xA3    |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|     \xE2\x99\xA3  J|",
    " --------- "};

string clubQ[] = {
    " _________ ",
    "|Q  \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|  \xE2\x99\xA3 Q \xE2\x99\xA3  |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|  \xE2\x99\xA3 \xE2\x99\xA3 \xE2\x99\xA3  |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3  Q|",
    " --------- "};

string clubK[] = {
    " _________ ",
    "|K  \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|  \xE2\x99\xA3 \xE2\x99\xA3 \xE2\x99\xA3  |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|  \xE2\x99\xA3 K \xE2\x99\xA3  |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3   |",
    "|   \xE2\x99\xA3 \xE2\x99\xA3  K|",
    " --------- "};

string heartA[] = {
    " _________ ",
    "|A        |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA5    |",
    "|         |",
    "|         |",
    "|        A|",
    " --------- "};

string heart2[] = {
    " _________ ",
    "|2        |",
    "|    \xE2\x99\xA5    |",
    "|         |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA5    |",
    "|        2|",
    " --------- "};

string heart3[] = {
    " _________ ",
    "|3        |",
    "|    \xE2\x99\xA5    |",
    "|         |",
    "|    \xE2\x99\xA5    |",
    "|         |",
    "|    \xE2\x99\xA5    |",
    "|        3|",
    " --------- "};

string heart4[] = {
    " _________ ",
    "|4        |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|         |",
    "|         |",
    "|         |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|        4|",
    " --------- "};

string heart5[] = {
    " _________ ",
    "|5        |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|         |",
    "|    \xE2\x99\xA5    |",
    "|         |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|        5|",
    " --------- "};

string heart6[] = {
    " _________ ",
    "|6        |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|         |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|         |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|        6|",
    " --------- "};

string heart7[] = {
    " _________ ",
    "|7        |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|    \xE2\x99\xA5    |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|         |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|        7|",
    " --------- "};

string heart8[] = {
    " _________ ",
    "|8        |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|    \xE2\x99\xA5    |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|    \xE2\x99\xA5    |",
    "|  \xE2\x99\xA5   \xE2\x99\xA5  |",
    "|        8|",
    " --------- "};

string heart9[] = {
    " _________ ",
    "|9  \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|         |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|    \xE2\x99\xA5    |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|         |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5  9|",
    " --------- "};

string heart10[] = {
    " _________ ",
    "|10 \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|    \xE2\x99\xA5    |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|         |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|    \xE2\x99\xA5    |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5 10|",
    " --------- "};

string heartJ[] = {
    " _________ ",
    "|J  \xE2\x99\xA5     |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|    \xE2\x99\xA5    |",
    "|  \xE2\x99\xA5 J \xE2\x99\xA5  |",
    "|    \xE2\x99\xA5    |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|     \xE2\x99\xA5  J|",
    " --------- "};

string heartQ[] = {
    " _________ ",
    "|Q  \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|  \xE2\x99\xA5 Q \xE2\x99\xA5  |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|  \xE2\x99\xA5 \xE2\x99\xA5 \xE2\x99\xA5  |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5  Q|",
    " --------- "};

string heartK[] = {
    " _________ ",
    "|K  \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|  \xE2\x99\xA5 \xE2\x99\xA5 \xE2\x99\xA5  |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|  \xE2\x99\xA5 K \xE2\x99\xA5  |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5   |",
    "|   \xE2\x99\xA5 \xE2\x99\xA5  K|",
    " --------- "};

string spadeA[] = {
    " _________ ",
    "|A        |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA0    |",
    "|         |",
    "|         |",
    "|        A|",
    " --------- "};

string spade2[] = {
    " _________ ",
    "|2        |",
    "|    \xE2\x99\xA0    |",
    "|         |",
    "|         |",
    "|         |",
    "|    \xE2\x99\xA0    |",
    "|        2|",
    " --------- "};

string spade3[] = {
    " _________ ",
    "|3        |",
    "|    \xE2\x99\xA0    |",
    "|         |",
    "|    \xE2\x99\xA0    |",
    "|         |",
    "|    \xE2\x99\xA0    |",
    "|        3|",
    " --------- "};

string spade4[] = {
    " _________ ",
    "|4        |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|         |",
    "|         |",
    "|         |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|        4|",
    " --------- "};

string spade5[] = {
    " _________ ",
    "|5        |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|         |",
    "|    \xE2\x99\xA0    |",
    "|         |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|        5|",
    " --------- "};

string spade6[] = {
    " _________ ",
    "|6        |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|         |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|         |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|        6|",
    " --------- "};

string spade7[] = {
    " _________ ",
    "|7        |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|    \xE2\x99\xA0    |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|         |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|        7|",
    " --------- "};

string spade8[] = {
    " _________ ",
    "|8        |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|    \xE2\x99\xA0    |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|    \xE2\x99\xA0    |",
    "|  \xE2\x99\xA0   \xE2\x99\xA0  |",
    "|        8|",
    " --------- "};

string spade9[] = {
    " _________ ",
    "|9  \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|         |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|    \xE2\x99\xA0    |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|         |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0  9|",
    " --------- "};

string spade10[] = {
    " _________ ",
    "|10 \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|    \xE2\x99\xA0    |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|         |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|    \xE2\x99\xA0    |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0 10|",
    " --------- "};

string spadeJ[] = {
    " _________ ",
    "|J  \xE2\x99\xA0     |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|    \xE2\x99\xA0    |",
    "|  \xE2\x99\xA0 J \xE2\x99\xA0  |",
    "|    \xE2\x99\xA0    |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|     \xE2\x99\xA0  J|",
    " --------- "};

string spadeQ[] = {
    " _________ ",
    "|Q  \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|  \xE2\x99\xA0 Q \xE2\x99\xA0  |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|  \xE2\x99\xA0 \xE2\x99\xA0 \xE2\x99\xA0  |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0  Q|",
    " --------- "};

string spadeK[] = {
    " _________ ",
    "|K  \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|  \xE2\x99\xA0 \xE2\x99\xA0 \xE2\x99\xA0  |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|  \xE2\x99\xA0 K \xE2\x99\xA0  |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0   |",
    "|   \xE2\x99\xA0 \xE2\x99\xA0  K|",
    " --------- "};


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

// get game value for the validate check 
vector<double> getGameValues(const vector<pair<int, int>>& cards) {
    vector<double> values;
    for (const auto& card : cards) {
        int val = card.first; // Card value (1-13)
        // int suit = card.second; // Unused
        if (val >= 11) {
            values.push_back(10.0); // J, Q, K = 10
        } else {
            values.push_back(static_cast<double>(val));
        }
    }
    return values;
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
    for (int line = 0; line < 9; ++line) { // Adjust to 11 if needed
        for (int i = 0; i < 4; ++i) {
            string* card = getCard(cards[i].first, cards[i].second);
            if (card) cout << card[line] << " ";
        }
        cout << endl;
    }
}


//step_2 timeattack, no need to check the issivable
// Global array to store card values
static int globalCardValues[4];

// Modified generateCards to return and store card values
int* generateCards(string mode) {
    vector<pair<int, int>> cards;

    if (mode == "timeattack") {
        cout << "Generating 4 random cards...\n";
        cards = generateOrigCards();
        displayCards(cards);

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
        const int MAX_ATTEMPTS = 1000;
        bool easyMode = (mode == "easy");
        while (attempts < MAX_ATTEMPTS) {
            cards = generateOrigCards();
            if (isSolvableWithAces(cards, easyMode)) {
                displayCards(cards);
                break;
            }else{
                attempts++;
            }
        }
        if (attempts > MAX_ATTEMPTS) {
            cout << "Could not find a solvable combination.\n";
            return nullptr; // Indicate failure
        }
    }


    // Store and return raw card values (1-13)
    for (int i = 0; i < 4; ++i) {
        globalCardValues[i] = cards[i].first;
    }
    return globalCardValues;
}


// Main entry points

// Fixed entry points
int* generate_easy() { return generateCards("easy"); }
int* generate_classic() { return generateCards("classic"); }
int* generate_timeattack() { return generateCards("timeattack"); }

// Fixed generate
int* generate(int choice) {
    switch(choice) {
        case 1: return generate_easy();
        case 2: return generate_classic();
        case 3: return generate_timeattack();
        default:
            cout << "Invalid choice!\n";
            return nullptr; // Fixed from return 1
    }
}

// test for array 
// Use global values

void useGlobalCardValues() {
    cout << "Global card values: ";
    for (int i = 0; i < 4; ++i) {
        int val = globalCardValues[i];
        if (val == 1) cout << "A ";
        else if (val == 11) cout << "J ";
        else if (val == 12) cout << "Q ";
        else if (val == 13) cout << "K ";
        else cout << val << " ";
    }
    cout << endl;
}




vector<int> getCardValues(int card) {
    if (card == 1) return {1, 11};      // Ace can be 1 or 11
    else if (card >= 11) return {10};   // Face cards (J, Q, K) = 10
    else return {card};                 // Number cards
}

pair<string, string> getEasyHint() {
    vector<vector<int>> possibleValues;
    for (int card : globalCardValues) {
        possibleValues.push_back(getCardValues(card));
    }

    // Try all combinations of 2 cards
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Check for perfect solutions first
                    if (a + b == 24) return {to_string(a), "+"};
                    if (a - b == 24) return {to_string(a), "-"};
                    
                    // Then check for operations that get close to 12 (half of 24)
                    if (abs(a + b - 12) <= 2) return {to_string(a), "+"};
                    if (a - b > 0 && abs(a - b - 12) <= 2) return {to_string(a), "-"};
                }
            }
        }
    }

    // Fallback to any valid addition
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    return {to_string(a), "+"};
                }
            }
        }
    }

    return {"any number", "+"};
}

pair<string, string> getClassicHint() {
    vector<vector<int>> possibleValues;
    for (int card : globalCardValues) {
        possibleValues.push_back(getCardValues(card));
    }

    // Try all combinations of 2 cards
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    // Check for perfect solutions first
                    if (a * b == 24) return {to_string(a), "*"};
                    if (a + b == 24) return {to_string(a), "+"};
                    if (a - b == 24) return {to_string(a), "-"};
                    if (b != 0 && a / b == 24) return {to_string(a), "/"};
                    
                    // Then check for factors of 24
                    if (24 % (a * b) == 0) return {to_string(a), "*"};
                    if (24 % (a + b) == 0) return {to_string(a), "+"};
                    
                    // Then check for useful intermediates
                    if (a * b < 24 && 24 % (a * b) == 0) return {to_string(a), "*"};
                    if (b != 0 && a % b == 0 && (a / b) < 24 && 24 % (a / b) == 0) {
                        return {to_string(a), "/"};
                    }
                }
            }
        }
    }

    // Fallback to multiplication as it's most likely to help reach 24
    for (int i = 0; i < 4; ++i) {
        for (int a : possibleValues[i]) {
            for (int j = 0; j < 4; ++j) {
                if (i == j) continue;
                for (int b : possibleValues[j]) {
                    return {to_string(a), "*"};
                }
            }
        }
    }

    return {"any number", "*"};
}

void easyHints() {
    auto hint = getEasyHint();
    cout << "Easy Mode: Start with " << hint.first << " " << hint.second << endl;
}

void classicHints() {
    auto hint = getClassicHint();
    cout << "Classic Mode: Start with " << hint.first << " " << hint.second << endl;
}

// for testing 
// Main to test global and returned values
int main() {
    srand(time(0));
    int* values = generate(2); // Test classic mode
    useGlobalCardValues();

    // Get and display hints
    easyHints();
    classicHints();
    return 0;
}
