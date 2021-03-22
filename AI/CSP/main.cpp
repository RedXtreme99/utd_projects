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

int branchNum = 1;      // variable to count branch number for output

// Function to determine which variables are still unassigned
vector<string> diff(map<string, vector<int> > mp, vector<string> vec)
{
    vector<string> vars;
    bool push;
    for(auto const& e : mp)
    {
        push = true;
        for(int i = 0; i < vec.size(); i++)
        {
            if(vec.at(i)[0] == e.first[0])
            {
                push = false;
                break;
            }
            if(push)
            {
                vars.push_back(e.first);
            }
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
    sort(mostConstraining.begin(), mostConstraining.end());
    return mostConstraining.at(0);
}

int select_value
(
    vector<string> unassigned,
    string variable,
    map<string, vector<int> > varMap,
    vector<string> constraints
)
{
    vector<int> values = varMap[variable];
    int numConstraining = -1;
    vector<int> leastConstraining;
    for(int i = 0; i < values.size(); i++)
    {
        int tempVal = values.at(i);
        int count = 0;
        for(int j = 0; j < unassigned.size(); j++)
        {
            bool constrained = false;
            for(int k = 0; k < constraints.size(); k++)
            {
                if(constraints.at(k).find(variable) < constraints.at(k).length() && 
                    constraints.at(k).find(unassigned.at(j)) < constraints.at(k).length())
                {
                    constrained = true;
                    switch(constraints.at(k)[1])
                    {
                        case '>':
                            if(variable[0] == constraints.at(k)[0])
                            {
                                for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                                {
                                    if(tempVal > varMap[unassigned.at(j)].at(l))
                                    {
                                        count++;
                                    }
                                }
                            }
                            else
                            {
                                for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                                {
                                    if(tempVal < varMap[unassigned.at(j)].at(l))
                                    {
                                        count++;
                                    }
                                }
                            }
                            break;
                        case '<':
                            if(variable[0] == constraints.at(k)[0])
                            {
                                for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                                {
                                    if(tempVal < varMap[unassigned.at(j)].at(l))
                                    {
                                        count++;
                                    }
                                }
                            }
                            else
                            {
                                for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                                {
                                    if(tempVal > varMap[unassigned.at(j)].at(l))
                                    {
                                        count++;
                                    }
                                }
                            }
                            break;
                        case '=':
                            for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                            {
                                if(tempVal == varMap[unassigned.at(j)].at(l))
                                {
                                    count++;
                                }
                            }
                            break;
                        case '!':
                            for(int l = 0; l < varMap[unassigned.at(j)].size(); l++)
                            {
                                if(tempVal != varMap[unassigned.at(j)].at(l))
                                {
                                    count++;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }
            if(!constrained)
            {
                count += varMap[unassigned.at(j)].size();
            }
        }
        if(count > numConstraining)
        {
            numConstraining = count;
            leastConstraining.clear();
        }
        if(count == numConstraining)
        {
            leastConstraining.push_back(tempVal);
        }
    }
    sort(leastConstraining.begin(), leastConstraining.end());
    return leastConstraining.at(0);
}

bool isConsistent
(
    string variable,
    int value,
    vector<string> constraints,
    vector<string> assignment
)
{
    for(int i = 0; i < assignment.size(); i++)
    {
        for(int j = 0; j < constraints.size(); j++)
        {
            if(constraints.at(j).find(variable) < constraints.at(j).length() &&
                constraints.at(j).find(assignment.at(i)[0]) < constraints.at(j).length())
            {
                    switch(constraints.at(j)[1])
                    {
                        case '>':
                            if(variable[0] == constraints.at(j)[0])
                            {
                                if(value < assignment.at(i)[2])
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                if(value > assignment.at(i)[2])
                                {
                                    return false;
                                }
                            }
                            break;
                        case '<':
                            if(variable[0] == constraints.at(j)[0])
                            {
                                if(value > assignment.at(i)[2])
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                if(value < assignment.at(i)[2])
                                {
                                    return false;
                                }
                            }
                            break;
                        case '=':
                            if(value != assignment.at(i)[2])
                            {
                                return false;
                            }
                            break;
                        case '!':
                            if(value == assignment.at(i)[2])
                            {
                                return false;
                            }
                            break;
                        default:
                            break;
                    }

                break;
            }
        }
    }
    return true;
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
        cout << branchNum << ". ";
        for(int i = 0; i < assignment.size(); i++)
        {
            cout << assignment.at(i);
            if(i != assignment.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "  solution" << endl;
        return;
    }
    vector<string> unassigned = diff(varMap, assignment);
    string var = select_variable(unassigned, varMap, constraints);
    unassigned.erase(remove(unassigned.begin(), unassigned.end(), var), unassigned.end());
    int value = select_value(unassigned, var, varMap, constraints);
    if(isConsistent(var, value, constraints, assignment))
    {
        string assign = var + "=" + to_string(value);
        assignment.push_back(assign);
        backtrack(varMap, constraints, assignment);
    }
    else
    {
        cout << branchNum++ << ". ";
        for(int i = 0; i < assignment.size(); i++)
        {
            cout << assignment.at(i);
            if(i != assignment.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "  failure" << endl;
    }
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
