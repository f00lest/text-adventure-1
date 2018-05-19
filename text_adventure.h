#include <iostream>
#include <string>
#include <vector> // For the command handling function.
#include <cctype> // Will be used to eliminate case sensitive problems.
#include <algorithm>
#include <cassert>

using namespace std;

// integers to direction names mapping.
enum en_DIRS {NORTH, EAST, SOUTH, WEST};
// integers to room names mapping.
// both the sportshop and the north are zero, its our understanding that matters.
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM, POOL, GARDEN, POND, PUMPROOM}; const int NONE = -1;
// verbs
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};
const int NOUNS = 6;
// there are 4 directions and 11 rooms, these constants will be used to create dirctions
// and rooms arrays.
const int DIRS = 4;
const int ROOMS = 11;
const int VERBS = 8;

// This struct will add a name string to the direction numbers we will be using.
struct word
{
    string word;
    int code;
};

// will represent objects like door, magnet, etc.., they should have a name, description, 
// and location, etc.., so we can track them.
struct noun
{
    string word;
    string description;
    int code;
    int location;
    bool can_carry;
};

// will hold the name of room and all possible exits.
struct room
{
    // constructor
    room()
    {
        // fill in directions with NONE initially
        std::fill(this->exits_to_room, this->exits_to_room + DIRS, NONE);
    }
    // description is simply the name of the room.
    string description;
    // each exit will be and denoted by an index, we do not need to remember those indeces
    // because we got enums. But In each of those directions we store the number of the 
    // next room through that exit. We'll use enums there too.
    int exits_to_room[DIRS];
};



void section_command(string Cmd, string &wd1, string &wd2);
void set_rooms(room *rms);
void set_directions(word *dir);
void set_verbs(word *vbs);
void set_nouns(noun *nns);
bool parser(int &loc, string wd1, string wd2, word *dir, word *vbs, room *rms, noun *nns);
void look_around(int loc, room *rms, word *dir, noun *nns, bool door_state);
/** prints introduction story **/
void print_intro();
