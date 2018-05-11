#include <iostream>
#include <string>
#include <vector> // For the command handling function.
#include <cctype> // Will be used to eliminate case sensitive problems.

using namespace std;


void section_command(string Cmd, string &wd1, string &wd2);


int main()
{
    string command;
    string word_1;
    string word_2;

    
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
        
        cout << word_1 << " " << word_2 << endl; // For test purposes, output the command after formatting by the function.
    }    

    return 0;
}


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