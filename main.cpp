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
#include <fstream>

#define DONTCARE 'd'
#define ONE 1
#define ZERO 0
#define X 2

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

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Usage: " << argv[0] << "filename" << endl;
		exit(1);
	}
	//check if the input minterm file exists
	ifstream fin(argv[1]);

	if(!fin)
	{
		cout << "Minterm (input) file " << argv[1] << " not found." << endl;
		exit(1);
	}
	string fileData; //used to read the implicant input file
	string buffer; // to store just the minterm portion of input
	vector<minterm>dontCares; //list of all don't cares
	vector<minterm>allMinterms; //list of all minterms (this includes dc)
	int noOfVars;
	int noOfTerms;
	int mintermcount = 0;

	//read the no.of vars and no of terms
	getline(fin,fileData);
	noOfVars= atoi(fileData.c_str());
	getline(fin,fileData);
	noOfTerms=atoi(fileData.c_str());
	size_t found;
	//read all minterms from file and add to appropriate lists
	while( mintermcount< noOfTerms)
	{
		getline(fin,fileData);
		minterm m = NULL;
		buffer = fileData.substr(0,noOfVars);
		short t;
		if(!tryParse(t,buffer))
		{
			printf("Invalid input found: %s", fileData);
			exit(0);
		}
		allMinterms.push_back(m);	
		//If a term is marked as dont care ,put it into the dc list also
		size_t found=fileData.find(DONTCARE);

		if (found!=string::npos) // the term is a dont care eg: 1001 d
		{
			dontCares.push_back(m);
		}
		mintermcount++;
	}

	vector< vector <vector<minterm>>> mintermArray(noOfVars-1);

	// initialize cells
	for(int i = 0; i < mintermArray.size(); i++)
	{
		mintermArray[i] = vector<vector<minterm>>(noOfVars);
	}

	//initial setup: fill up all the uncombined terms ( all terms will end up in the first row -with zero 'x's)
	minterm* mintermit=NULL;
	for (vector<minterm>::iterator mintermit=allMinterms.begin() ; mintermit != allMinterms.end(); mintermit++ )
		int j = mintermit->countParameters(1);
	mintermArray[0][j].push_back(*mintermit);

//QM :combining terms
//run thru the array from top to bottom and check adjacent cells i,j if they can be combined
//put the result in the [i+1th][j-1th] location
for(int xes=0; xes < noOfVars -1; xes++) //for every x dont care bit
{
	for(int ones=0; ones < noOfVars -1; ones++)  //for every # of ones
	{
		vector<minterm> left   = mintermArray[xes][ones];
		vector<minterm> right  = mintermArray[xes][ones+1];
		vector<minterm> out    = mintermArray[xes+1][ones];
		for(int i = 0; i < left.size(); i++)
		{
			for(int j = 0; j < right.size(); j++)
			{
				minterm combined = left[i].canCombine(right[j]);
				if(combined != null)
				{
					
			}
		}
		result= left.canCombine(right); //check if the terms left and right 'cells' can be combined
		if(result!=NULL) //check if the combined term already exists in the 'destination' cell
		{
			if (! ( result.ifPresent(out))) //add the combined term to the destination cell.
			{
				vector<short>::iterator it;
				for it=result.begin() ; it < result.end(); it++ )
					mintermArray[i+1][j].push_back(*it);

			}
		} 
		else //we cant combine the terms so add them to teh prime implicant list
		{
			primeImplicants.push_back(left); 
			primeImplicants.push_back(right); 
		}
	}
}
