/*
 * ParkingLevel.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: basil
 */
/*
 * Basil El-Hindi 2336.001
 * */
#include <iostream>
#include <string>
#include <cmath>
#include "ParkingSpot.cpp"
#include <vector>
using namespace std;
/*
 * ParkingLevel is a class meant to represent every level of the parking lot and itself is a vector of ParkingSpot objects. The ParkingLevel is built from the
 * parameters passed from the ParkingLot class, as well as creating another instance variable named vecWidth to store the length of the vector including spaces to
 * represent the different rows within a level. The constructor calculates how many of the total spots should me large, compact, and motorcycle spots, and creates
 * ParkingSpot objects to reflect these spots and pushes them to the vector storing all the spots as well as including spaces at the end of each row. The park,
 * remove, and print method all parse the vector and perform the necessary operations. This action is done across every level by the ParkingLot class methods. The
 * park methods for each vehicle search for available parking spots for that vehicle and then construct a ParkingSpot object to replace an empty space it finds,
 * and the remove methods change a Spot occupied by a vehicle back to the spot it was before. The method to check if a vehicle is in each level is also
 * implemented and is used to see if a vehicle exists before attempting to remove it. The print method prints the letter used to represent each spot with a space
 * in between.
 * */
class ParkingLevel{
	private:
		int SPOTS_PER_LEVEL,SPOTS_PER_ROW;
		double motorPortion, largePortion;
//width of the level vector equal to spots per level + the spaces between each row
		int vecWidth;
		vector<ParkingSpot> level;

	public:
//default constructor not used
		ParkingLevel()
		{
			SPOTS_PER_LEVEL = 30;
			SPOTS_PER_ROW = 10;
			motorPortion = .2;
			largePortion = .2;
			vecWidth = 32;
		}
//ParkingLevel constructer that takes ints for the number of spots/level and /row, and doubles for the large and motorcycle proportions.
		ParkingLevel(int spotsNum, int spotsRows, double mPortion, double lPortion)
		{
//algorithm to find how many rows each level contains. Input required every row to be the same length, so subtracting this length from the total level length gives
//a count for how many rows the level has
			int rowsPerLevel = 0;
			SPOTS_PER_LEVEL = spotsNum;
			while(spotsNum >= spotsRows)
			{
				spotsNum-=spotsRows;
				rowsPerLevel++;
			}
			spotsNum = SPOTS_PER_LEVEL;
//the vector length storing each spot is equal to the total number of spots + 1 less than the number of rows in that level, since there is 1 less space between rows
//than there are rows
			vecWidth = SPOTS_PER_LEVEL + rowsPerLevel - 1;
			SPOTS_PER_ROW = spotsRows;
			motorPortion = mPortion;
			largePortion = lPortion;
//integer for the number of motorcycle and large spots calculated by multiplying the total number of spots in that row to the proportion that are supposed to be a
//certain size and rounding up
			int motorNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * motorPortion));
			int largeNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * largePortion));
//to prevent rounding issues from making too many spaces, the compact spaces are found by subtracting the number of motorcycle and large spaces from the total/level
			int comp = SPOTS_PER_LEVEL - motorNum - largeNum;
//outer loop pushes a ParkingSpot object instantiated with a space in between each row
			for(int i = 0; i < rowsPerLevel; i++)
			{
//the inner loop creates each row
				for(int j = 0; j < SPOTS_PER_ROW; j++)
				{
//the count for each number of spots is decremented every time a spot of that type is made. Motorcycle spots are made first on the left, and then compact spots,
//and then large spots. If statement checks if there are more of that spot type, and if there are, push that Spot object to the vector, decrement the counter,
//and then use continue to advance the loop to the next iteration without creating more of that or another type
					if(motorNum > 0)
					{
						ParkingSpot s("m");
						level.push_back(s);
						motorNum--;
						continue;
					}
					if(comp > 0)
					{
						ParkingSpot s("c");
						level.push_back(s);
						comp--;
						continue;
					}
					if(largeNum > 0)
					{
						ParkingSpot s("l");
						level.push_back(s);
						largeNum--;
						continue;
					}
				}
				ParkingSpot s(" ");
				level.push_back(s);
			}
		}
//destructor
		~ParkingLevel(){}
//parkCar takes no parameters and returns a string. It parses the width of the vector and searches for compact and large spots, and if there is one, it assigns a new
//ParkingSpot object instantiated with the vehicle to that position and returns a success message to the lot parkCar method. If no empty space is discovered, it
//returns an empty string to the lot method, which it interprets as failure. The search stops once only one car is successfully parked
		string parkCar()
		{
			string output = "";
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == "c" || level.at(i).getSpot() == "l")
				{
					output = "success";
					ParkingSpot s("C");
					level.at(i) = s;
					break;
				}
			}
			return output;
		}
//parkMotorcycle takes no parameters and returns a string. It parses the width of the vector and searches for any empty spot, and if there is one, it creates a new
//ParkingSpot object instantiated with the vehicle and replaces the empty spot. If it does this, it returns a success string to the lot method, if it fails it sends
//an empty string, and the search ends once only one motorcycle is parked.
		string parkMotorcycle()
		{
			string output = "";
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == "c" || level.at(i).getSpot() == "l" || level.at(i).getSpot() == "m")
				{
					output = "success";
					ParkingSpot s("M");
					level.at(i) = s;
					break;
				}
			}
			return output;
		}
//parkBus takes no parameters and returns a string. It searches the width of the vector and searches for 5 consecutive large spots. If there exists space, the
//method creates five ParkingSpot objects all instantiated with a B to represent the bus and replaces the 5 spots with the new object and exists the loop once one
//bus is parked. The function outputs an empty string for failure and a success string when successful
		string parkBus()
		{
			string output = "";
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == "l" && level.at(i+1).getSpot() == "l" && level.at(i+2).getSpot() == "l" && level.at(i+3).getSpot() == "l" && level.at(i+4).getSpot() == "l")
				{
					output = "success";
					ParkingSpot s1("B");
					ParkingSpot s2("B");
					ParkingSpot s3("B");
					ParkingSpot s4("B");
					ParkingSpot s5("B");
					level.at(i) = s1;
					level.at(i+1) = s2;
					level.at(i+2) = s3;
					level.at(i+3) = s4;
					level.at(i+4) = s5;
					break;
				}
			}
			return output;
		}
//The isVehicle is used to check if a certain vehicle is in the lot before its attempted to be removed. It is a boolean and requires a key which comes from the lot
//remove methods and matches with the vehicle they want to remove. This function parses the width of the level and if any of those elements are the vehicle it's
//searching for, the search halts and the function returns true to the lot isVehicle, but if it does not find one, it returns false
		bool isVehicle(string key)
		{
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == key)
					return true;
			}
			return false;
		}
//removeCar takes no parameters and returns a string. The method searches for a parked car, and upon finding it, replaces that position with whatever type of spot
//it was parked in which is retroactively determined. It returns the text Car removed to display on the console when successful or an empty string to the lot method
		string removeCar()
		{
//same motorNum, comp and largeNum calculations for constructor and initialized a space counter to count how many spaces occur between the beginning of a level and
//the desired vehicle to remove
			int spaceCount = 0;
			int motorNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * motorPortion));
			int largeNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * largePortion));
			int comp = SPOTS_PER_LEVEL - motorNum - largeNum;
//parses the width and counts the spaces until it encounters a C. It then checks to see if the index to be replaced should be a compact or a large spot by adding
//the number of spaces to the number of motorcycle and compact spots since they are consecutive. If the index is less, the car was parking on a compact spot, but if
//not it was parked in a large spot. The appropriate new ParkingSpot object is created to replace it and a message is returned.
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == " ")
					spaceCount++;
				if(level.at(i).getSpot() == "C")
				{
					if(i < motorNum + comp + spaceCount)
					{
						ParkingSpot s("c");
						level.at(i) = s;
					}
					else
					{
						ParkingSpot s("l");
						level.at(i) = s;
					}
					return "Car removed.\n";
				}
			}
			return "";
		}
//removeMotorcycle takes no parameters and returns a string. The method searches for a parked motorcycle and if it finds one, replaces that ParkingSpot with whatever
//size it originally was and it returns success text or an empty string
		string removeMotorcycle()
		{
//same motorNum, comp and largeNum calculations for constructor and initialized a space counter to count how many spaces occur between the beginning of a level and
//the desired vehicle to remove
			int spaceCount = 0;
			int motorNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * motorPortion));
			int largeNum = static_cast<int>(ceil(SPOTS_PER_LEVEL * largePortion));
			int comp = SPOTS_PER_LEVEL - motorNum - largeNum;
//parses the width of the level and searches for a motorcycle while counting the spaces until it occurs. It then determines what the spot origninally was by adding
//each type of ParkingSpot and the spaces before the removed motorcycle to determine which interval/space the motorcycle was parked in, then creates the proper
//object and replaces it
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == " ")
					spaceCount++;
				if(level.at(i).getSpot() == "M")
				{
					if(i < motorNum + spaceCount)
					{
						ParkingSpot s("m");
						level.at(i) = s;
					}
					else if(i < motorNum + comp + spaceCount)
					{
						ParkingSpot s("c");
						level.at(i) = s;
					}
					else
					{
						ParkingSpot s("l");
						level.at(i) = s;
					}
					return "Motorcycle removed.\n";
				}
			}
			return "";
		}
//removeBus takes no parameters and returns a success or empty string. It searches for the first occurrence of a B to find where a bus starts, and then changes that
//spot and the 4 after it to large spots
		string removeBus()
		{
//parses width and uses nested loop to change the 5 positions of the bus to large spots
			for(int i = 0; i < vecWidth; i++)
			{
				if(level.at(i).getSpot() == "B")
				{
					for(int j = 0; j < 5; j++)
					{
						ParkingSpot s("l");
						level.at(i+j) = s;
					}
					return "Bus removed.\n";
				}
			}
			return "";
		}
//print takes no parameters and returns a string, parsing the level and printing the value at each spot
		string print()
		{
			string output = "";
			for(int i = 0; i < vecWidth; i++)
			{
				output += level.at(i).getSpot();
			}
			return output;
		}
};
