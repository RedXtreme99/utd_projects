/*  Basil El-Hindi
 *  CS 4365.HON
 *  CSP Solver
 *  main.cpp        */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        cout << "Wrong number of inputs" << endl;
        return -1;
    }

    string varfilename = argv[1];
    ifstream varfile(varfilename);
    if(!varfile.is_open())
    {
        cout << "Unable to open var file" << endl;
        return -2;
    }
    string confilename = argv[2];
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
    cout << "Variable file: " << varfilename << endl << "Constraint file: " << confilename << endl << "Procedure: " << procedure << endl;
    return 0;
}
