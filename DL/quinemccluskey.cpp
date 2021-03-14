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

    return 0;
}
