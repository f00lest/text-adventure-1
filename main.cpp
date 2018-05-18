#include <iostream>
#include <string>
#include <vector> // For the command handling function.
#include <cctype> // Will be used to eliminate case sensitive problems.
#include <algorithm>

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


int main()
{    
    string command;
    string word_1;
    string word_2;

    // set rooms, directions, verbs, nouns.
    room rooms[ROOMS];
    set_rooms(rooms);
    word directions[DIRS];
    set_directions(directions);
    word verbs[VERBS];
    set_verbs(verbs);
    noun nouns[NOUNS];
    set_nouns(nouns);


    int location = CARPARK; // using the enumerated type identifier, of course.

    
    while (word_1 != "QUIT") // I have provided an escape condition from the loop here
    {        
        command.clear();
        cout << "What shall I do? ";        
        getline(cin, command);        
        word_1.clear();
        word_2.clear();

        // Call the function that handles the command line fromat.
        section_command(command, word_1, word_2); 

        if(word_1 != "QUIT")
        {
            parser(location, word_1, word_2, directions, verbs, rooms, nouns);
        }
    }    

    return 0;
}


/** This function divides the user command into first and second words. **/
void section_command(string Cmd, string &wd1, string &wd2)
{    
    string sub_str;
    vector<string> words;
    char search = ' ';
    size_t i, j;

    for(i = 0; i < Cmd.size(); i++)
    {        
        if(Cmd.at(i) != search)
        {
            sub_str.insert(sub_str.end(), Cmd.at(i));
        }

        if(i == Cmd.size() - 1)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }

        if(Cmd.at(i) == search)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
    }

    // Clear out any blanks
    // I work backwords through the vectors here as a cheat not to invalidate
    // moving in the reverse direction prevents change of index of next elements that will
    // be evaluated.
    for(i = words.size() - 1; i > 0; i--)
    {
        if (words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }

    // Make words upper case
    // Right here is where the functions from cctype are used
    // iterate on words
    for(i = 0; i < words.size(); i++)
    {
        // iterate on letters of the words
        for(j = 0; j < words.at(i).size(); j++)
        {
            if(islower(words.at(i).at(j)))
            {
                words.at(i).at(j) = toupper(words.at(i).at(j));
            }
        }
    }
    // Very simple. For the moment I only wat the first to words at most (verb / noun).
    if(words.size() == 0)
    {
        cout << "No command given" << endl;
    }
    if(words.size() == 1)
    {
        wd1 = words.at(0);
    }
    if(words.size() == 2)
    {
        wd1 = words.at(0);
        wd2 = words.at(1);
    }
    if(words.size() > 2)
    {
        cout << "Command too long. Only type one or two words (direction or verb and noun)" << endl;
    }
}


void set_rooms(room *rms)
{
    // assign description to first index 
    rms[SPORTSHOP].description.assign("sports shop");
    // set the number of room this room exits into in each direction, -1 if it does not.
    rms[SPORTSHOP].exits_to_room[NORTH] = NONE;
    rms[SPORTSHOP].exits_to_room[EAST] = NONE;
    rms[SPORTSHOP].exits_to_room[SOUTH] = CARPARK;
    rms[SPORTSHOP].exits_to_room[WEST] = NONE;
 
    rms[CASINO].description.assign("bustling casino");
    rms[CASINO].exits_to_room[NORTH] = NONE;
    rms[CASINO].exits_to_room[EAST] = NONE;
    rms[CASINO].exits_to_room[SOUTH] = LOBBY;
    rms[CASINO].exits_to_room[WEST] = NONE;
 
    rms[CARPARK].description.assign("car park");
    rms[CARPARK].exits_to_room[NORTH] = SPORTSHOP;
    rms[CARPARK].exits_to_room[EAST] = LOBBY;
    rms[CARPARK].exits_to_room[SOUTH] = NONE;
    rms[CARPARK].exits_to_room[WEST] = NONE;
 
    rms[LOBBY].description.assign("hotel lobby");
    rms[LOBBY].exits_to_room[NORTH] = CASINO;
    rms[LOBBY].exits_to_room[EAST] = RESTAURANT;
    rms[LOBBY].exits_to_room[SOUTH] = CORRIDOR;
    rms[LOBBY].exits_to_room[WEST] = CARPARK;
 
    rms[RESTAURANT].description.assign("restaurant");
    rms[RESTAURANT].exits_to_room[NORTH] = NONE;
    rms[RESTAURANT].exits_to_room[EAST] = NONE;
    rms[RESTAURANT].exits_to_room[SOUTH] = NONE;
    rms[RESTAURANT].exits_to_room[WEST] = LOBBY;
 
    rms[CORRIDOR].description.assign("corridor");
    rms[CORRIDOR].exits_to_room[NORTH] = LOBBY;
    //rms[CORRIDOR].exits_to_room[EAST] = STOREROOM;
    rms[CORRIDOR].exits_to_room[SOUTH] = GARDEN;
    rms[CORRIDOR].exits_to_room[WEST] = NONE;
 
    rms[STOREROOM].description.assign("store room");
    rms[STOREROOM].exits_to_room[NORTH] = NONE;
    rms[STOREROOM].exits_to_room[EAST] = NONE;
    rms[STOREROOM].exits_to_room[SOUTH] = NONE;
    //rms[STOREROOM].exits_to_room[WEST] = CORRIDOR;
 
    rms[POOL].description.assign("swimming pool area");
    rms[POOL].exits_to_room[NORTH] = NONE;
    rms[POOL].exits_to_room[EAST] = GARDEN;
    rms[POOL].exits_to_room[SOUTH] = PUMPROOM;
    rms[POOL].exits_to_room[WEST] = NONE;
 
    rms[GARDEN].description.assign("tranquil garden");
    rms[GARDEN].exits_to_room[NORTH] = CORRIDOR;
    rms[GARDEN].exits_to_room[EAST] = POND;
    rms[GARDEN].exits_to_room[SOUTH] = NONE;
    rms[GARDEN].exits_to_room[WEST] = POOL;
 
    rms[POND].description.assign("patio with a fish pond");
    rms[POND].exits_to_room[NORTH] = NONE;
    rms[POND].exits_to_room[EAST] = NONE;
    rms[POND].exits_to_room[SOUTH] = NONE;
    rms[POND].exits_to_room[WEST] = GARDEN;
 
    rms[PUMPROOM].description.assign("damp pump room");
    rms[PUMPROOM].exits_to_room[NORTH] = POOL;
    rms[PUMPROOM].exits_to_room[EAST] = NONE;
    rms[PUMPROOM].exits_to_room[SOUTH] = NONE;
    rms[PUMPROOM].exits_to_room[WEST] = NONE;
}

/** Add names to directions **/
void set_directions(word *dir)
{
    dir[NORTH].code = NORTH;
    dir[NORTH].word = "NORTH";
    dir[EAST].code = EAST;
    dir[EAST].word = "EAST";
    dir[SOUTH].code = SOUTH;
    dir[SOUTH].word = "SOUTH";
    dir[WEST].code = WEST;
    dir[WEST].word = "WEST";
}


// Function to set the verbs...
void set_verbs(word *vbs)
{
    // Reminder GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK
    vbs[GET].code = GET;
    vbs[GET].word = "GET";
    vbs[DROP].code = DROP;
    vbs[DROP].word = "DROP";
    vbs[USE].code = USE;
    vbs[USE].word = "USE";
    vbs[OPEN].code = OPEN;
    vbs[OPEN].word = "OPEN";
    vbs[CLOSE].code = CLOSE;
    vbs[CLOSE].word = "CLOSE";
    vbs[EXAMINE].code = EXAMINE;
    vbs[EXAMINE].word = "EXAMINE";
    vbs[INVENTORY].code = INVENTORY;
    vbs[INVENTORY].word = "INVENTORY";
    vbs[LOOK].code = LOOK;
    vbs[LOOK].word = "LOOK";
}

void set_nouns(noun *nns)
{
        //enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};
    nns[STORE_DOOR].word = "DOOR";
    nns[STORE_DOOR].code = STORE_DOOR;
    nns[STORE_DOOR].description = "a closed store room door";
    nns[STORE_DOOR].can_carry = false;
    nns[STORE_DOOR].location = CORRIDOR;
    nns[MAGNET].word = "MAGNET";
    nns[MAGNET].code = MAGNET;
    nns[MAGNET].description = "a magnet";
    nns[MAGNET].can_carry = true;
    nns[MAGNET].location = NONE;
    nns[METER].word = "METER";
    nns[METER].code = METER;
    nns[METER].description = "a parking meter";
    nns[METER].can_carry = false;
    nns[METER].location = CARPARK;
    nns[ROULETTE].word = "ROULETTE";
    nns[ROULETTE].code = ROULETTE;
    nns[ROULETTE].description = "a roulette wheel";
    nns[ROULETTE].can_carry = false;
    nns[ROULETTE].location = CASINO;
    nns[MONEY].word = "MONEY";
    nns[MONEY].code = MONEY;
    nns[MONEY].description = "some money";
    nns[MONEY].can_carry = true;
    nns[MONEY].location = NONE;
    nns[FISHROD].word = "ROD";
    nns[FISHROD].code = FISHROD;
    nns[FISHROD].description = "a fishing rod";
    nns[FISHROD].can_carry = false;
    nns[FISHROD].location = SPORTSHOP;
}

bool parser(int &loc, string wd1, string wd2, word *dir, word *vbs, room *rms, noun *nns)
{
    int i;
    int VERB_ACTION = NONE;
    int NOUN_MATCH = NONE;
    static bool door_state = false;

    // Iterate on direction names
    for(i = 0; i < DIRS; i++)
    {
        // check if they match the input direction of user.
        if(wd1 == dir[i].word)
        {
            // if it does then look if exit in that input direction
            // is present in the current room that user is in.
            if(rms[loc].exits_to_room[dir[i].code] != NONE)
            {
                loc = rms[loc].exits_to_room[dir[i].code];
                cout << "I am now in a " << rms[loc].description << endl;
                return true;
            }
            // if there is no exit that way it fails with a message.
            else
            {
                cout << "No exit that way." << endl;
                return true;
            }
        }
    }

    // iterates over verbs, converts user entered verb string
    // to an enum / int value.
    for(i = 0; i < VERBS; ++i)
    {
        if(wd1 == vbs[i].word)
        {            
            // if found verb, get its code save it to a local variable and 
            // break for next tasks.
            VERB_ACTION = vbs[i].code;            
            break;
        }
    }

    if(wd2 != "")
    {
        for(i = 0; i < NOUNS; i++)
        {
            if(wd2 == nns[i].word)
            {
                NOUN_MATCH = nns[i].code;
                break;
            }
        }
    }

    // if the verb is not found amongst our list
    if(VERB_ACTION == NONE)
    {
        // warn user
        cout << "No valid command entered." << endl;
        return true;
    }
    // if it was look
    if(VERB_ACTION == LOOK)
    {
        // call a nice little function. Of course we need current location along with rooms and
        // directions to look up for that room in rms and then get all possible exits in a
        // ll possible directions and then print them out for the user.
        // This is an example of sub proceduralizing a function from the parser.
        look_around(loc, rms, dir, nns, door_state);
        return true;
    }
    if(VERB_ACTION == OPEN)
    {
        if(NOUN_MATCH == STORE_DOOR)
        {
            if(loc == CORRIDOR || loc == STOREROOM)
            {
                if (door_state == false)
                {
                    door_state = true;
                    rms[CORRIDOR].exits_to_room[EAST] = STOREROOM;
                    rms[STOREROOM].exits_to_room[WEST] = CORRIDOR;
                    nns[STORE_DOOR].description.clear();
                    nns[STORE_DOOR].description.assign("an open store room door");
                    cout << "I have opened the door." << endl;
                    return true;
                }
                else if(door_state == true)
                {
                    cout << "The door is already open." << endl;
                    return true;
                }
            }
            else 
            {
                cout << "There is no door to open here." << endl;
            }
        }
        else
        {
            cout << "Opening that is not possible." << endl;
        }
    }

    if(VERB_ACTION == CLOSE)
    {
        if(NOUN_MATCH == STORE_DOOR)
        {
            if(loc == CORRIDOR || loc == STOREROOM)
            {
                if (door_state == true)
                {
                    door_state = false;
                    rms[CORRIDOR].exits_to_room[EAST] = NONE;
                    rms[STOREROOM].exits_to_room[WEST] = NONE;
                    nns[STORE_DOOR].description.clear();
                    nns[STORE_DOOR].description.assign("a closed store room door");
                    return true;
                }
                else if(door_state == false)
                {
                    cout << "The door is already closed." << endl;
                    return true;
                }
            }
            else
            {
                cout << "There is no door to close here." << endl;
                return true;
            }
        }
        else
        {
            cout << "Closing that is not possible." << endl;
            return true;
        }
    }

    // we've run out of implemented verbs and directions.
    cout << "No valid command entered.!!" << endl;
    return false;
}

// prints out all exits in all directions from the current location.
void look_around(int loc, room *rms, word *dir, noun *nns, bool door_state)
{
    int i;
    // print current room name.
    cout << "I am in a " << rms[loc].description << endl;

    // LOOK should also allow the player to see what exits exist from the current room.
    // look in all direcctions
    for(i = 0; i < DIRS; i++)
    {
        // if an exit exits in that direction
        if(rms[loc].exits_to_room[i] != NONE)
        {
            // print out the details of that exit.
            cout << "There is an exit " << dir[i].word << " to a " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
        }
    }
    for(i = 0; i < NOUNS; i++)
    {
        if(nns[i].location == loc)
        {
            cout << "I see " << nns[i].description << "." << endl;
        }
    }
}
