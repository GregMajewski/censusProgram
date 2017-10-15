// censusProject.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

#include <stdlib.h>
#include <time.h>//included for rand
#include <utility>//included for pair
#include <vector>//included for vector
#include <iostream>//included for cout
#include <fstream>//included for file reading
#include <string>//included for parsing read info
#include <iterator>//included for splitting the string read from file
#include <sstream>//included for splitting the string read from file

using namespace std;//cut out the need for  everywhere

#define MAXYEAR 2000// last year someone can be alive
#define MINYEAR 1900// first year somone could be born
#define MINPEOPLE 1//minimum number of people in the census
#define MAXPEOPLE 10//maximum number of people in the census
//#define RANDOMDATA 0//if 1 a random ammount of people with random data are populated, if 0 it uses set values//used this for non-file testing

vector<int> startCensus(vector<pair<int,int>> peopleList)//checks to see what year(s) are most populated and returns a vector of them
{
	vector<int> nBigYear;//var for holding the biggest years
	vector<pair<int,int>> activeYears;//vector of pairs, each pair is a year and a population ammount, keeps track of the years people were alive for.
	int nNumPeopleAlive = 0;//check for how many people were alive

	for(int i = 0; i < peopleList.size(); i++)//for each person
	{
		int nStartPoint = peopleList[i].first;//find the start point
		int nEndPoint = peopleList[i].second;//find the end point

		for(int x = nStartPoint; x <= nEndPoint; x++)//while between the start and end
		{
			bool foundIt = false;//flag for if we found the year in the list
			int check = 0;//iterator
			while(check < activeYears.size())//while there are years in activeYears
			{
				if(activeYears[check].first == x)//if we found the year we are looking for
				{
					activeYears[check].second++;//incriment the ammount of living people
					foundIt = true;//set flag to true
					if(activeYears[check].second > nNumPeopleAlive)//check to see if the year is now the most populated
					{
						nNumPeopleAlive = activeYears[check].second;//it was, increase the highest population var
					}
					break;//exit while
				}
				++check;//didn't find it, check next
			}
			if(foundIt == false)//if we didnt find the year
			{
				pair<int,int> temp(x, 1);//create it with 1 population
				activeYears.push_back(temp);//add it to the list
				if(nNumPeopleAlive < 1)//check to see if it is the first year someone was alive
				{
					nNumPeopleAlive = 1;//it was, increase the highest population var
				}
			}
		}
	}
	
	for(int a = 0; a < activeYears.size(); a++)//for each active year
	{
		if(nNumPeopleAlive == activeYears[a].second)//if this years population is equal to the highest population reached
		{
			nBigYear.push_back(activeYears[a].first);//add year to list of biggest years
		}
	}
	cout << "Highest population: " << nNumPeopleAlive << "\n";
	
	return nBigYear;//return the years with the biggest living populations
}

vector<string> split(const string &s, char delim)//splits the supplied string by the given delim
{
	vector<string> elems;//vector to hold the items coming out of the parse
	stringstream ss;
	ss.str(s);//sets stringstream to point at the start of the string
	string item;
	while (getline(ss, item, delim))//parses the line by the delim
	{
		elems.push_back(item);//adds the item to the end of the vector
	}
	return elems;
}

vector <pair <int,int>> getPeople()//creates a vector of people
{
	vector<pair <int,int>> peopleList;
	/*
	if(RANDOMDATA == 1)
	{
		int numPeople = rand()%(MAXPEOPLE-MINPEOPLE+1)+MINPEOPLE;//randomize number of people in census between max and min

		cout << "Number of people surveyed: " << numPeople << "\n";
		for(int p = 0; p < numPeople; p++)//for the ammount of people in census
		{
			int bDay = rand()%(MAXYEAR-MINYEAR+1)+MINYEAR;//find a date of birth between min and max
			int dDay = rand()%(MAXYEAR-bDay+1)+bDay;//find a death date between birth and max
			pair<int,int> temp(bDay, dDay);//create record
			peopleList.push_back(temp);//add to list of people
		}
	}
	else
	{
		pair<int, int> temp(1929,1954); //testing unit 1

		pair<int, int> temp2(1945,1952);//testing unit 2

		pair<int, int> temp3(1981,2000); //testing unit 3

		pair<int, int> temp4(1906,1955);//testing unit 4

		pair<int, int> temp5(1907,1973); //testing unit 5

		pair<int, int> temp6(1944,1986);//testing unit 6

		pair<int, int> temp7(1926,1988); //testing unit 7

		pair<int, int> temp8(1948,1971);//testing unit 8

		pair<int, int> temp9(1919,1978); //testing unit 9

		pair<int, int> temp10(1900,2000);//testing unit 10

		peopleList.push_back(temp);
		peopleList.push_back(temp2);
		peopleList.push_back(temp3);
		peopleList.push_back(temp4);
		peopleList.push_back(temp5);
		peopleList.push_back(temp6);
		peopleList.push_back(temp7);
		peopleList.push_back(temp8);
		peopleList.push_back(temp9);
		peopleList.push_back(temp10);
	}
	*///used for non-file testing

	string line;//read info
	ifstream myfile ("dataset.txt");//open file
	if (myfile.is_open())//if the file was there
	{
		while (getline(myfile, line))//while there are still lines to be read
		{
			vector<string> data = split(line, ',');//split the string
			if(data.size() > 0)//if we got information
			{
				pair<int, int> temp(stoi(data[0]),stoi(data[1]));//the first item is birthdate second is date of death, create a person

				peopleList.push_back(temp);//add to list
			}
		}
		myfile.close();//close the file
	}
	else
	{
		cout << "Unable to open file\n"; //we didnt find dataset.text
	}

	return peopleList;//return the list of people
}



int main()
{
	srand ( time(NULL) );//seed the rand function
	
	vector<int> nBiggestYears;//var for holding the years with the most ammount of people
	vector<pair<int,int>> people = getPeople();//get people
	if(people.size() > 0)//if we have people
	{
		nBiggestYears = startCensus(people);//get the biggest years after getting the list of people
	
		int numberOfYears = nBiggestYears.size();//we'll be using the number a few times, this is quicker than calling the function repeatedly
	
		if(numberOfYears > 1)//if there are more than one year
		{
			cout <<"Years with the most people alive: ";
		}
		else//if only one year
		{
			cout <<"Year with the most people alive: ";
		}

		for(int count = 0; count < numberOfYears; count++)//for each year
		{
			cout << nBiggestYears[count];//print the year
			if((count+1) < numberOfYears)//if its not the end add a comma and a space
			{
				cout << ", ";
			}
		}
	}
	else
	{
		cout << "No people surveyed";
	}
	cout <<"\n";//newline so it looks good
	std::cout << "Press ENTER to continue...\n";
	std::cin.ignore();//added so the cmd doesnt close on its own
	return 0;//end program
}

