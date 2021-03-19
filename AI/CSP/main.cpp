/*  Basil El-Hindi
 *  CS 4365.HON
 *  CSP Solver
 *  main.cpp        
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Function to determine which variables are still unassigned
vector<string> diff(map<string, vector<int> > mp, vector<string> vec)
{
    vector<string> vars;
    for(auto const& e : mp)
    {
        if(!count(vec.begin(), vec.end(), e.first))
        {
            vars.push_back(e.first);
        }
    }
    return vars;
}

// Function to determine which variable to next assign
string select_variable
(
    vector<string> vars, 
    map<string, vector<int> > varMap, 
    vector<string> constraints
)
{
    // If there is only one variable available, select it
    if(vars.size() == 1)
    {
        return vars.at(0);
    }

    // Choose the most constrained variable
    vector<string> mostConstrained;
    int domainSize = 9999;
    for(int i = 0; i < vars.size(); i++)
    {
        if(varMap[vars.at(i)].size() < domainSize)
        {
            domainSize = varMap[vars.at(i)].size();
            mostConstrained.clear();
        }
        if(varMap[vars.at(i)].size() == domainSize)
        {
            mostConstrained.push_back(vars.at(i));
        }
    }
    if(mostConstrained.size() == 1)
    {
        return mostConstrained.at(0);
    }

    // If there are ties, use the most contraining variable
    vector<string> mostConstraining;
    int constraintCount;
    int mostConstraint = -1;
    for(int i = 0; i < mostConstrained.size(); i++)
    {
        constraintCount = 0;
        for(int j = 0; j < vars.size(); j++)
        {
            if(mostConstrained.at(i) == vars.at(j))
            {
                continue;
            }
            for(int k = 0; k < constraints.size(); k++)
            {
                if(constraints.at(k).find(mostConstrained.at(i)) < constraints.at(k).length()
                    && constraints.at(k).find(vars.at(j)) < constraints.at(k).length())
                {
                    constraintCount++;
                }
            }
        }
        if(constraintCount > mostConstraint)
        {
            mostConstraint = constraintCount;
            mostConstraining.clear();
        }
        if(constraintCount == mostConstraint)
        {
            mostConstraining.push_back(mostConstrained.at(i));
        }
    }
    if(mostConstraining.size() == 1)
    {
        return mostConstraining.at(0);
    }

    // If still ties, break alphabetically
    sort(mostConstraining.begin(), mostConstraining.end());
    return mostConstraining.at(0);
}

void backtrack
(
    map<string, vector<int> > varMap, 
    vector<string> constraints, 
    vector<string> assignment
)
{
    if(assignment.size() == varMap.size())
    {
        return;
    }
    vector<string> unassigned = diff(varMap, assignment);
    string var = select_variable(unassigned, varMap, constraints);
    cout << var << endl;
    return;
}

void forwardcheck
(
    map<string, vector<int> > varMap, 
    vector<string> constraints, 
    vector<string> assignment
)
{

}

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
    map<string, vector<int> > varMap;
    while(getline(varfile, line))
    {
        string var = ""; 
        var = line[0];
        stringstream ss(line.substr(3));
        string value;
        while(ss >> value)
        {
            varMap[var].push_back(stoi(value));
        }
    }

    // Store constraints as a vector where all elements are length 3 strings
    vector<string> constraints;
    while(getline(confile, line))
    {
        stringstream ss;
        ss << line[0] << line[2] << line[4];
        constraints.push_back(ss.str());
    }

    // Use the commanded procedure to attempt to solve the CSP
    // Pass empty assignment string vector to either backtracking algorithm
    // or the forward checking algorithm
    vector<string> assignment;
    if(procedure == "none")
    {
        backtrack(varMap, constraints, assignment);
    }
    else
    {
        forwardcheck(varMap, constraints, assignment);
    }

    return 0;
}
