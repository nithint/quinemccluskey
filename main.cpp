/*Filename: main.cpp
desc:main method for minlogic
*/
#include "minterm.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>
#define DONTCARE 2

using namespace std;
//global list of prime implicants
list<minterm> primeImplicants;

bool covered(vector<vector<bool>>& coverTable, int rows, int cols);
int findEssentialPI(vector<vector<bool>>& coverTable, vector<minterm>& origMinterms, 
	vector<minterm>& primeImplicants);
vector<minterm> removeDontCares(vector<minterm>& allMinterms, vector<minterm>& dontcares);
/**
* convert string to number
*/
template <class T>
bool tryParse(T& t,
	const std::string& s)
{
	std::istringstream iss(s);
	return !(iss >> t).fail();
}
vector<minterm> solveCoveringTable(vector<minterm> allMinterms, vector<minterm> dontcares,
	vector<minterm> primeImplicants)
{
	// create the covering table
	vector<vector<bool>> coverTable = vector<vector<bool>>();
	// remove don't care output terms from original minterms
	vector<minterm> origMinterms = removeDontCares(allMinterms, dontcares);

	for(int i = 0; i < primeImplicants.size(); i++)
	{
		for(int j = 0; j < origMinterms.size(); j++)
		{
			coverTable[i][j] = origMinterms[j].coveredBy(primeImplicants[i]);
		}
	}

	// essential prime implicants
	vector<minterm> essPI = vector<minterm>();
	// extract all essential prime implicants
	int p = 0;
	while(p!= -1)
	{
		int p = findEssentialPI(coverTable, primeImplicants.size(), origMinterms.size());
		if(p!= -1)
		{
			// add p to ess pi
			essPI.push_back(primeImplicants[p]);
			// zero out columns covered by p
			removePI(coverTable, p, origMinterms.size());
		}
	}

	// no more essential PI, pick the largest covering PI first
	while(!covered(coverTable, primeImplicants.size(), origMinterms.size()))
	{
		int p = findLargestCoveringPI(coverTable, primeImplicants.size(), origMinterms.size());
		essPI.push_back(primeImplicants[p]);
		removePI(coverTable, p, origMinterms.size());
	}
	return essPI;
}

void printPrimeImplicants(vector<minterm> pi)
{
	string result = "";
	for(int i = 0; i < pi.size(); i++)
	{
		result += pi[i].toString();

		if(i != pi.size()-1)
			result += " + ";
	}
	printf(result.c_str());
}

void countSomething(vector<minterm> piList)
{

}

// remove the essential pi from cover table
// sets all columns covered by the ess PI to zero 
void removePI(vector<vector<bool>>& coverTable, int p, int cols)
{
	// zero out all columns with p in it
	for(int i = 0; i < cols; i++)
	{
		if(coverTable[p][i] == true)
		{
			// zero out column
			for(int j = 0; j < primeImplicants.size(); j++)
			{
				coverTable[j][i] = false;
			}
		}
	}
}
bool covered(vector<vector<bool>>& coverTable, int rows, int cols)
{
	// covered if the cover table is full of zero
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			if(coverTable[i][j] != 0)
				return false;
	return true;
}

int findLargestCoveringPI(vector<vector<bool>>& coverTable, int rows, int cols)
{
	int sum = 0;
	int pos = 0;
	// search for largest sum over row
	for(int i = 0; i < rows; i++)
	{
		int tempSum = 0;
		for(int j = 0; j < cols; j++)
		{
			if(coverTable[i][j])
				tempSum ++;
		}
		if(tempSum > sum)
		{
			sum = tempSum;
			pos = i;
		}
	}

	return pos;
}

int findEssentialPI(vector<vector<bool>>& coverTable, int rows, 
	int cols)
{
	// column first search for columns covered by only 1 PI
	for(int i = 0; i < cols; i++)
	{
		// count # of 1's in this column
		int count = 0;
		int position = -1;
		for(int j = 0; j < rows; j++)
		{
			if(coverTable[j][i] == true)
			{
				count++;
				position = j;
			}
		}
		if(count == 1)
		{
			// this column only covered by 1 PI. return that pi's position
			return position;
		}
	}
	// no essential prime implicants
	return -1;
}
// remove all the dont care output terms from the original minterms
vector<minterm> removeDontCares(vector<minterm>& allMinterms, vector<minterm>& dontcares)
{
	// clone all minterms
	vector<minterm> result = vector<minterm>(allMinterms);
	// remove all dont care terms
	for(int i = 0; i < dontcares.size(); i++)
	{
		for(int j = 0; j < result.size(); j++)
		{
			if(result[j].equals(dontcares[i]))
				result.erase(result.begin()+j);
		}
	}
	return result;
}