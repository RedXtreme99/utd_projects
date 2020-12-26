/*
 * ParkingLot.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: basil
 */
/*
 * Basil El-Hindi 2336.001
 * */
#include <iostream>
#include <string>
#include <cmath>
#include "ParkingLevel.cpp"
#include <vector>
using namespace std;
/*
 * Class ParkingLot represents the entire lot and is a vector of ParkingLevel objects. When attempting to create the lot, park and remove cars, and print the lot,
 * the class will access its private vector of ParkingLevel objects which have the ability to directly access parking spots. The constructor creates the number of
 * levels equal to its instance variables and uses the remaining parameters to construct each ParkingLevel object and push it to the end of the vector storing them.
 * There is a park and remove method for both the vehicles, and those access every parking level that the lot is storing and then perform their specific functions.
 * There is also a boolean function to determine whether or not the lot contains a certain type of vehicle at any given time. The lot is also able to be printed,
 * which it does by printing each parking level on a new line.
 * */
class ParkingLot{
	private:
		int NUM_OF_LEVELS;
		vector<ParkingLevel> lot;

	public:
//constructor takes ints for number of levels, spots/level, and spots/row and doubles for the proportion of motorcycle/large spots and makes ParkingLevel objects
//and stores them in the vector named lot
		ParkingLot(int numLevels, int spotsNum, int spotsRows, double mPortion, double lPortion)
		{
			NUM_OF_LEVELS = numLevels;
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				ParkingLevel level(spotsNum, spotsRows, mPortion, lPortion);
				lot.push_back(level);
			}
		}
//destructor
		~ParkingLot(){}
//parkCar takes no parameters and returns an output string based on the success of parking a car. It attempts to access every parking level's parkCar method
//in its search for a compact or large spot to park the car in
		string parkCar()
		{
			string output = "";
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				output = lot.at(i).parkCar();
				if(output != "")
					break;
			}
			if(output == "")
				output = "complete";
			return output;
		}
//parkMotorcycle takes no parameters and returns an output string based on the success of parking a motorcycle and accesses every level's parkMotorcycle method to
//search for any spot to park the motorcycle in
		string parkMotorcycle()
		{
			string output = "";
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				output = lot.at(i).parkMotorcycle();
				if(output != "")
					break;
			}
			if(output == "")
				output = "complete";
			return output;
		}
//parkBus takes no paramters and returns an output string based on its success and accesses every level's parkBus method, and the method searches for 5
//consecutive/continuous large spots to park the bus in
		string parkBus()
		{
			string output = "";
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				output = lot.at(i).parkBus();
				if(output != "")
					return output;
			}
			output = "complete";
			return output;
		}
//isVehicle is a boolean that takes a string key as a parameter. The removeCar, Motorcycle, and Bus methods all call this method with a specific key to check
//before attempting to remove a vehicle that that vehicle type is parked somewhere in the lot by calling a isVehicle method for every parking level
		bool isVehicle(string key)
		{
			bool status = false;
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				status = lot.at(i).isVehicle(key);
				if(status == true)
					break;
			}
			return status;
		}
//removeCar takes no parameters and returns an output string based on the success of a car being removed by calling a removeCar method for every parking level after
//checking that the lot contains a car
		string removeCar()
		{
			string output = "";
			if(isVehicle("C"))
			{
				for(int i = 0; i < NUM_OF_LEVELS; i++)
				{
					output = lot.at(i).removeCar();
					if(output != "")
						return output;
				}
			}
			else
				output = "No car to remove.\n";
			return output;
		}
//removeMotorcycle takes no parameters and returns an output string based on the success of a motorcycle being removed by calling a removeMotorcycle method for every
//parking level after checking that the lot contains a motorcycle
		string removeMotorcycle()
		{
			string output = "";
			if(isVehicle("M"))
			{
				for(int i = 0; i < NUM_OF_LEVELS; i++)
				{
					output = lot.at(i).removeMotorcycle();
					if(output != "")
						return output;
				}
			}
			else
				output = "No motorcycle to remove.\n";
			return output;
		}
//removeBus takes no parameters amd returns an output string based on the success of a bus being removed by calling a removeBus method for every parking level after
//checking that the lot contains a bus
		string removeBus()
		{
			string output = "";
			if(isVehicle("B"))
			{
				for(int i = 0; i < NUM_OF_LEVELS; i++)
				{
					output = lot.at(i).removeBus();
					if(output != "")
						return output;
				}
			}
			else
				output = "No bus to remove.\n";
			return output;
		}
//the print method takes no parameters and returns an output string that is every parking level separated by a new line to display the entire parking lot
		string print()
		{
			string output = "";
			for(int i = 0; i < NUM_OF_LEVELS; i++)
			{
				output += lot.at(i).print() + "\n";
			}
			return output;
		}
};
