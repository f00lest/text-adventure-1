#include <iostream>
#include <string>
#include <vector> // For the command handling function.
#include <cctype> // Will be used to eliminate case sensitive problems.

using namespace std;

// integers to direction names mapping.
enum en_DIRS {NORTH, EAST, SOUTH, WEST};
// integers to room names mapping.
// both the sportshop and the north are zero, its our understanding that matters.
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM, POOL, GARDEN, POND, PUMPROOM}; const int NONE = -1;
// there are 4 directions and 11 rooms, these constants will be used to create dirctions
// and rooms arrays.
const int DIRS = 4;
const int ROOMS = 11;

// This struct will add a name string to the direction numbers we will be using.
struct word
{
    string word;
    int code;
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
bool parser(int &loc, string wd1, string wd2, word *dir, room *rms);


int main()
{    
    string command;
    string word_1;
    string word_2;

    room rooms[ROOMS];
    set_rooms(rooms);
    word directions[DIRS];
    set_directions(directions);
    int location = CARPARK; // using the enumerated type identifier, of course.

    
    while (word_1 != "QUIT") // I have provided an escape condition from the loop here
    {        
        command.clear();
        cout << "What shall I do? ";        
        getline(cin, command);        
        cout << "Your raw command was " << command << endl;        
        word_1.clear();
        word_2.clear();

        // Call the function that handles the command line fromat.
        section_command(command, word_1, word_2); 
        parser(location, word_1, word_2, directions, rooms);
        cout << word_1 << " " << word_2 << endl; // For test purposes, output the command after formatting by the function.
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
    for(i = words.size() - 1; i > 0; i--)
    {
        if (words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }

    // Make words upper case
    // Right here is where the functions from cctype are used
    for(i = 0; i < words.size(); i++)
    {
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
    rms[CORRIDOR].exits_to_room[EAST] = STOREROOM;
    rms[CORRIDOR].exits_to_room[SOUTH] = GARDEN;
    rms[CORRIDOR].exits_to_room[WEST] = NONE;
 
    rms[STOREROOM].description.assign("store room");
    rms[STOREROOM].exits_to_room[NORTH] = NONE;
    rms[STOREROOM].exits_to_room[EAST] = NONE;
    rms[STOREROOM].exits_to_room[SOUTH] = NONE;
    rms[STOREROOM].exits_to_room[WEST] = CORRIDOR;
 
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


bool parser(int &loc, string wd1, string wd2, word *dir, room *rms)
{
    int i;

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
                cout << "I am now in a " << rms[loc].description << "," << endl;
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
    cout << "No valid command entered." << endl;
    return false;
}
