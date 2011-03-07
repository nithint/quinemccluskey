#include "minterm.h"
#include <vector>

void solveCoveringTable(vector<minterm> allMinterms, vector<minterm> primeImplicants)
{
	// create the covering table
	vector<vector<bool>> coverTable = new vector<vector<bool>>();
	// remove don't care output terms from original minterms
	vector<minterm> origMinterms = removeDontCares();
	
	for(int i = 0; i < primeImplicants.size(); i++)
	{
		for(int j = 0; j < origMinterms.size(); j++)
		{
			coverTable[i][j] = origMinterms[j].coveredBy(primeImplicants[i]);
		}
	}

	// essential prime implicants
	vector<minterm> essPI = new vector<minterm>();
	while(!covered(coverTable, primeImplicants.size(), origMinterms.size()))
	{
		int p = findEssentialPI(coverTable, origMinterms, primeImplicants);
		if(p!= -1)
		{
			// zero out that column and add pi to final list
			essPI.push_back(primeImplicants[p]);
			zerooutColumn(//dont know what column);
		}
	}

}

bool covered(vector<vector<bool>> coverTable, int rows, int cols)
{
	// covered if the cover table is full of zero
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			if(coverTable[i][j] != 0)
				return false;
	return true;
}

int findEssentialPI(vector<vector<bool>> coverTable, vector<minterm> origMinterms, 
	vector<minterm> primeImplicants)
{
	// column first search for columns covered by only 1 pim
	for(int i = 0; i < origMinterms.size(); i++)
	{
		// count # of 1's in this column
		int count = 0;
		int position = -1;
		for(int j = 0; j < primeImplicants.size(); j++)
		{
			if(coverTable[j][i] == true)
			{
				count++;
				position = j;
			}
		}
		if(count == 1)
		{
			// this column only covered by 1 pim. return that pi's position
			return position;
		}
	}
	// no essential prime implicants
	return -1;
}
// remove all the dont care output terms from the originall minterms
vector<minterm> removeDontCares()
{

}