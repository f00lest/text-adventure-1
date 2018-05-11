#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
    string command;

    while (1 == 1) // Temporary condition for now.
    {
        command.clear();
        cout << "What shall I do? ";
        getline(cin, command);
        cout << "Your raw command was " << command << endl;
    }
    return 0;
}