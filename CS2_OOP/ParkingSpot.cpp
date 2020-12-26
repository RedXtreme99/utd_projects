/*
 * ParkingSpot.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: basil
 */
/*
 * Basil El-Hindi 2336.001*/
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
/*
 * ParkingSpot is a class meant to store each parking spot within the parking lot. The spot is initialized with a lower case letter to indicate the size of its
 * spot, and can later be replaced by a capital letter to represent a vehicle. The getSpot methods allows every spot to be printed.
 * */
class ParkingSpot{
	private:
		string size;

	public:
//default constructor
		ParkingSpot()
		{
			size = "";
		}
//custom constructor takes a string and assigns it to the instance variable for that instance of ParkingSpot
		ParkingSpot(string letter)
		{
			size = letter;
		}
//destructor
		~ParkingSpot(){}
//getSpot returns a string that is the length 1 string representing the size of that spot or what vehicle occupies it
		string getSpot()
		{
			return size;
		}

};
