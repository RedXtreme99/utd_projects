/*  Basil El-Hindi
 *  CS 4365.HON
 *  CSP Solver
 *  main.cpp        */

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    // Check for correct number of command line inputs
    if(argc != 4)
    {
        cout << "Wrong number of inputs" << endl;
        return -1;
    }

    // Ensure each input is valid
    string varfilename = argv[1];
    if(varfilename.substr(varfilename.length()-4) != ".var")
    {
        cout << "Invalid var file name" << endl;
        return -2;
    }
    ifstream varfile(varfilename);
    if(!varfile.is_open())
    {
        cout << "Unable to open var file" << endl;
        return -2;
    }
    string confilename = argv[2];
    if(confilename.substr(confilename.length()-4) != ".con")
    {
        cout << "Invalid con file name" << endl;
        return -2;
    }
    ifstream confile(confilename);
    if(!confile.is_open())
    {
        cout << "Unable to open con file" << endl;
        return -2;
    }
    string procedure = argv[3];
    if(!(procedure == "fc" || procedure == "none"))
    {
        cout << "Invalid procedure given" << endl;
        return -2;
    }

    // Store variables and their domains
    string line;
    map<char, vector<int> > varMap;
    while(getline(varfile, line))
    {
        char var = line[0];
        stringstream ss(line.substr(3));
        string value;
        while(ss >> value)
        {
            varMap[var].push_back(stoi(value));
        }
    }

    // Store constraints as a vector

    return 0;
}
