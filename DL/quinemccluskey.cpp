/*  Basil El-Hindi
 *  CS 4341.HON
 *  Project 1 Quine-McCluskey
 *  bae170000 */

#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Function to convert decimal numbers to binary strings of the correct length
vector<string> decToBin(int numVars, vector<int> vec)
{
    vector<string> outvec;
    for(int i = 0; i < vec.size(); i++)
    {
        outvec.push_back(bitset<10>(vec.at(i)).to_string());
        outvec.at(i) = outvec.at(i).substr(10-numVars);
    }
    return outvec;
}

// Function to check if two binary strings differ in exactly one bit
bool isGreyCode(string a, string b)
{
    int count = 0;
    for(int i = 0; i < a.length(); i++)
    {
        if(a[i] != b[i])
        {
            count++;
        }
    }
    return count == 1;
}

// Function to replace bit of two terms that differ by one bit with a dont care
string combine(string a, string b)
{
    string out = "";
    for(int i = 0; i < a.length(); i++)
    {
        if(a[i] != b[i])
        {
            out += "-";
        }
        else
        {
            out += a[i];
        }
    }
    return out;
}

// Function to perform one iteration of adjacency combining
vector<string> reduce(vector<string> minterms)
{
    vector<string> primes;
    int numTerms = minterms.size();
    bool* checked = new bool[numTerms];
    for(int i = 0; i < numTerms; i++)
    {
        for(int j = i; j < numTerms; j++)
        {
            // Check if two terms are adjacent and replace their common bit
            if(isGreyCode(minterms.at(i), minterms.at(j)))
            {
                checked[i] = true;
                checked[j] = true;
                if(find(primes.begin(), primes.end(), 
                    combine(minterms.at(i),minterms.at(j))) == primes.end())
                {
                    primes.push_back(combine(minterms.at(i), minterms.at(j)));
                }
            }
        }
    }
    // Replace terms that were not used as they are prime implicants
    for(int i = 0; i < numTerms; i++)
    {
        if(!checked[i])
        {
            primes.push_back(minterms.at(i));
        }
    }
    delete[] checked;
    return primes;
}

// Function that returns true when boolean string a covers b
bool covers(string a, string b)
{
    for(int i = 0; i < a.length(); i++)
    {
        if(a[i] == b[i])
        {
            continue;
        }
        else if(a[i] == '-')
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// Function to convert binary string to literals
string getTerm(string term)
{
    string alphabet[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    string outstr = " ";
    for(int i = 0; i < term.length(); i++)
    {
        if(term[i] == '-')
        {
            continue;
        }
        else
        {
            outstr += alphabet[i];
            if(term[i] == '0')
            {
                outstr += "'";
            }
        }
    }
    outstr += " +";
    return outstr;
}

int main()
{
    // Parse input for number of literals, the on-array, and the dont-cares
    string input;
    getline(cin, input);
    stringstream ss(input);
    static int numLiterals;
    ss >> numLiterals;
    bool dontcare = false;
    vector<int> ons;
    vector<int> dcs;
    string word;
    while(ss >> word)
    {
        if(dontcare)
        {
            dcs.push_back(stoi(word));
            continue;
        }
        if(word == "d")
        {
            dontcare = true;
            continue;
        }
        ons.push_back(stoi(word));
    }

    // Convert decimal input to binary strings of correct length
    vector<string> onarray = decToBin(numLiterals, ons);
    vector<string> dcarray = decToBin(numLiterals, dcs);

    // Create minterms for adjacency table
    vector<string> minterms;
    minterms.insert(minterms.end(), onarray.begin(), onarray.end());
    minterms.insert(minterms.end(), dcarray.begin(), dcarray.end());
    sort(minterms.begin(), minterms.end());

    // Minimize adjacency table to determine prime implicants
    while(minterms != reduce(minterms))
    {
        minterms = reduce(minterms);
        sort(minterms.begin(), minterms.end());
    }

    // If there are no minterms, the function is equivalent to logic 0
    if(minterms.size() == 0)
    {
        cout << "F = 0" << endl;
        return 0;
    }

    // If the only minterm is all dashes, then the function is logic 1
    if(minterms.size() == 1)
    {
        for(int i = 0; i < numLiterals; i++)
        {
            if(minterms.at(0)[i] != '-')
            {
                break;
            }
        }
        cout << "F = 1" << endl;
        return 0;
    }

    // Initialize coverage table to minimize by determining essential prime
    // implicants
    vector<vector<bool> > coverageTable;
    int rows = minterms.size();
    int cols = onarray.size();
    for(int i = 0; i < rows; i++)
    {
        vector<bool> vec;
        for(int j = 0; j < cols; j++)
        {
            vec.push_back(false);
        }
        coverageTable.push_back(vec);
        vec.clear();
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(covers(minterms.at(i), onarray.at(j)))
            {
                coverageTable.at(i).at(j) = true;
            }
        }
    }

    // Minimize coverage table and build output string
    string formula = "F =";

    while(!coverageTable.empty())
    {
        ////////////////
        ////////////////////////////////
        cout << "ROWS" << endl;
        for(int i = 0; i < minterms.size(); i++)
            cout << minterms.at(i) << endl;
        cout << endl;
        cout << "COLS" << endl;
        for(int i = 0; i < ons.size(); i++)
            cout << ons.at(i) << endl;
        cout << endl; ////////////
        cout << "TABLE" << endl;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
                cout << coverageTable.at(i).at(j) << " ";
            cout << endl;
        } cout << endl;
        cout << "FORMULA" << endl;
        cout << formula << endl << endl;//////////////////
        
        // Check for the less-thans; check if i <= j
        bool remove = false;
        bool pass = false;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < rows; j++)
            {
                if(i == j)
                {
                    continue;
                }
                for(int k = 0; k < cols; k++)
                {
                    if(coverageTable.at(i).at(k) && !coverageTable.at(j).at(k))
                    {
                        pass = true;
                        break;
                    }
                }
                if(pass)
                {
                    pass = false;
                    continue;
                }
                remove = true;
                cout << "REMOVING ROW " << i << endl;
                coverageTable.erase(coverageTable.begin() + i);
                minterms.erase(minterms.begin() + i);
                rows--;
                break;
            }
            if(remove)
            {
                break;
            }
        }
        if(remove)
        {
            continue;
        }
        
        // Check for EPIs
        int epiRow = -1;
        for(int j = 0; j < cols; j++)
        {
            for(int i = 0; i < rows; i++)
            {
                if(coverageTable.at(i).at(j))
                {
                    if(epiRow < 0)
                    {
                        epiRow = i;
                    }
                    else
                    {
                        epiRow = -1;
                        break;
                    }
                }
            }
            if(epiRow > -1)
            {
                cout << "REMOVING ROW " << epiRow << " AND ITS COLUMNS" << endl;
                remove = true;
                for(int k = 0; k < cols; k++)
                {
                    if(coverageTable.at(epiRow).at(k))
                    {
                        for(int i = 0; i < rows; i++)
                        {
                            coverageTable.at(i).erase
                                (coverageTable.at(i).begin() + k);
                        }
                        ons.erase(ons.begin() + k);
                        k--;
                        cols--;
                    }
                }
                coverageTable.erase(coverageTable.begin() + epiRow);
                formula += getTerm(minterms.at(epiRow));
                minterms.erase(minterms.begin() + epiRow);
                rows--;
                break;
            }
        }
        if(remove)
        {
            continue;
        }
        // Cyclical, remove best choice

        break; /////
    }

    formula = formula.substr(0, formula.length() - 2);
    cout << formula << endl;
    return 0;
}
