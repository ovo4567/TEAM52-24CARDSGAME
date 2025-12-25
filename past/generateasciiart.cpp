#include "24cardgame.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
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
void generatecards(int* fournumbers, string* cards[4]) { //inputs required: the 4 numbers generated, null array to be passed on(the output)
    string* allcards[14][4] = {
        {diamondA, clubA, heartA, spadeA},
        {diamond2, club2, heart2, spade2},
        {diamond3, club3, heart3, spade3},
        {diamond4, club4, heart4, spade4},
        {diamond5, club5, heart5, spade5},
        {diamond6, club6, heart6, spade6},
        {diamond7, club7, heart7, spade7},
        {diamond8, club8, heart8, spade8},
        {diamond9, club9, heart9, spade9},
        {diamond10, club10, heart10, spade10},
        {diamondA, clubA, heartA, spadeA},
        {diamondJ, clubJ, heartJ, spadeJ},
        {diamondQ, clubQ, heartQ, spadeQ},
        {diamondK, clubK, heartK, spadeK}
    };
    srand (time(NULL));
    int JQK[] = {10, 12, 13, 14}; //JQK as value of 10
    for (int i = 0; i < 4; i++) {
        int num = fournumbers[i];
        int randomnumber = rand() % 4;
        if (num >= 1 && num <= 11) {
            if (num == 10){
                int randomnumber2 = rand() % 4;
                cards[i] = allcards[JQK[randomnumber]-1][randomnumber2];
            }
            else{
                cards[i] = allcards[num-1][randomnumber];
            }
            
        }
    }
}
    
int main() {    //for debug(should be removed)
    srand (time(NULL));
    fournumbers = getRandomNumbers() //from 24cardgame.cpp
    string* cards[4]; //hold 4 pointers
    generatecards(fournumbers, cards);
    for (int line = 0; line < 9; line++) { // Each card has 9 lines
        for (int cardIndex = 0; cardIndex < 4; cardIndex++) {
            cout << cards[cardIndex][line] << " ";
        }
        cout << endl; 
    }
}
