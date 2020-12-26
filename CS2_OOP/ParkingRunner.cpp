/*
 * ParkingRunner.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: basil
 */

/*
 * Basil El-Hindi 2336.001
 * Run code and enter either a "d" to construct a parking lot with default values or an "n" to enter your own values. Enter values as prompted, invalid input will
 * prompt you to reenter it. Enter positive integers for the number of levels, number of spots per level, and the number of spots per row. Enter a number between
 * 0 and 1 inclusive for the motorcycle and large proportions. The parking lot will print and prompt you to begin parking and removing vehicles. Entering "pc"
 * will park a car in the first available compact or large spot, "pm" will park a motorcycle in the first available spot, and "pb" will park a bus in the first
 * available 5 consecutive large spots. If there is no space to park the vehicle, the program will inform you and terminate. After parking a vehicle, the program will
 * inform you that it parked successfully and reprint the lot. Entering "rc" will remove the first car in the lot parsing the top row first from left to right,
 * "rm" will remove the first occurring motorcycle, and "rb" will remove the first occurring bus. If there is no vehicle of the type you try to remove, the program
 * will inform you and reprint the lot and wait for input. The program can be terminated at any time during this process by typing "exit". When the program
 * terminates either through the exit command or by attempting to park a car without space, it will inform you that the lot is finalized and print it.
 * */
#include <iostream>
#include <cmath>
#include <string>
#include "ParkingLot.cpp"
using namespace std;

int main()
{
//Loop determining whether parking lot is constructed with default or custom values, only progresses with a "d" or "n", any other input triggers an error and reloops
	string start = "";
	while(true)
	{
		cout << "Enter a 'd' to use default values or 'n' to enter your preferred values:" << endl;
		cin >> start;
		if(start == "n" || start == "d")
			break;
		else
		{
			cout << "invalid input" << endl;
			start = "";
		}
	}
//Initialization of instance variables and either accepts user input if custom constructor selected above, or uses default values to initialize instance variables
	int numLevels, spotsPerLevel, spotsPerRow;
	double motorPortion, largePortion;
	if(start == "n")
	{
		while(true)
		{
			cout << "Enter number of levels: ";
			cin >> numLevels;
			if(numLevels)
			cout << "Enter spots per level: ";
			cin >> spotsPerLevel;
			cout << "Enter spots per row: ";
			cin >> spotsPerRow;
//values must always be positive, and all the rows within a level all must be the same size
			if(numLevels > 0 && spotsPerLevel > 0 && spotsPerRow > 0 && spotsPerRow <= spotsPerLevel && spotsPerLevel%spotsPerRow == 0)
				break;
			else
			{
				cout << "invalid input" << endl;
				numLevels = 0;
				spotsPerLevel = 0;
				spotsPerRow = 0;
			}
		}
		while(true)
		{
			cout << "Enter a number between 0 and 1 for the portion of motorcycle spots per row: ";
			cin >> motorPortion;
			cout << "Enter a number between 0 and 1 for the portion of large spots per row: ";
			cin >> largePortion;
//the motorcycle and large spot proportions can not add up to more than 100% and both must be between [0,1]
			if(motorPortion+largePortion <= 1.0 && motorPortion <= 1.0 && largePortion <= 1.0 && motorPortion >= 0.0 && largePortion >= 0.0)
				break;
			else
			{
				cout << "invalid input" << endl;
				motorPortion = 0.0;
				largePortion = 0.0;
			}
		}
	}
	if(start == "d")
	{
		numLevels = 5;
		spotsPerLevel = 30;
		spotsPerRow = 10;
		motorPortion = .2;
		largePortion = .2;
	}
//construct ParkingLot object lot with either the default or custom values
	ParkingLot lot(numLevels, spotsPerLevel, spotsPerRow, motorPortion, largePortion);
//command is the user inputted command, and parkresult is a string giving the result of an attempt to park a vehicle that determines the next course of action
	string command = "";
	string parkresult = "";
//loop that will display the parking lot and instructions after every command until the program is terminated
	while(true)
	{
		while(true)
		{
//commands are in the format: first letter is "p" or "r" for park or remove, and second letter is "c", "m", or "b" for car, motorcycle, or bus, respectively
			cout << "Parking lot:\n" + lot.print() << "\nType 'pc' to park a car, 'pm' to park a motorcycle, 'pb' to park a bus, 'rc' to remove a car, 'rm' to remove a motorcycle, or 'rb' to remove a bus:\nType 'exit' to close the program.\n";
			cin >> command;
//any time during this loop to park and remove cars, the user can type exit to display the final lot and terminate the program
			if(command == "exit")
				break;
			if(command == "pc" || command == "pm" || command == "pb" || command == "rc" || command == "rm" || command == "rb")
				break;
			else
			{
				cout << "invalid input" << endl;
				command = "";
			}
		}
		if(command == "exit")
			break;
//park command calls method based on the vehicle. If that park returns an empty string, it was unsuccessful and the program ends with a message and the final lot.
		if(command.at(0) == 'p')
		{
			if(command.at(1) == 'c')
				parkresult = lot.parkCar();
			if(command.at(1) == 'm')
				parkresult = lot.parkMotorcycle();
			if(command.at(1) == 'b')
				parkresult = lot.parkBus();
			if(parkresult == "success")
				cout << "Vehicle parked.\n";
			if(parkresult == "complete")
			{
				cout << "No available space to park.";
				break;
			}
		}
//remove command calls method based on the vehicle, will always display whether or not its successful and then update the lot
		if(command.at(0) == 'r')
		{
			if(command.at(1) == 'c')
			{
				cout << lot.removeCar();
			}
			if(command.at(1) == 'm')
			{
				cout << lot.removeMotorcycle();
			}
			if(command.at(1) == 'b')
			{
				cout << lot.removeBus();
			}
		}
	}
//program termination informs user the lot is finalized and prints it one last time
	cout << "Final parking lot:\n" << lot.print();
	return 0;
}
