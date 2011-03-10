/*
Filename: minterm.cc
description:class definition for minterm
created:6-3-2011
*/

#include "minterm.h"
#include <string>
#include <vector>

using namespace std;

//constructor
minterm::minterm()
{}
minterm::minterm(vector<short> mterm)
{
	this->mintermVal = vector<short>(mterm);
}

minterm::~minterm(void) {}


//compares the objs mintermVal with parameters and returns the
//combined value else returns NULL.
bool minterm::canCombine(minterm& other, minterm& combined)
{
	vector<short> termBits = vector<short>(this->getTerm());
	vector<short>::iterator it;
	vector<short> otherTermBits = vector<short>(other.getTerm());
	vector<short>::iterator otherit = otherTermBits.begin();
	int bitDiff = 0;
	//do a bit wise minterm comparison and insert 'x' whereever they differ.
	for(int i = 0; i < termBits.size(); i++)
	{
		if(termBits[i] != other.getTerm()[i])
		{
			termBits[i] = X;
			bitDiff++;
		}
	}

	//return the result ONLY if there is a one bit difference else ret NULL
	if( bitDiff==1)
	{
		combined = minterm(termBits);
		return true;
	}
	else
		return false;
}


//counts the number of 'p's in the minterm vector and returns the count
int minterm::countParameters(short p)
{
	int pcount =0;
	vector<short>::iterator it;
	for (it=this->mintermVal.begin() ; it < this->mintermVal.end(); it++ )
	{
		if( *it==p)
			pcount++;
	}
	return(pcount);
}


bool minterm::coveredBy(minterm other)
{
	vector<short> term = other.getTerm();
	for(unsigned int i = 0; i < term.size(); i++)
	{
		if(term[i] != X && term[i] != getTerm()[i])
			return false;
	}
	return true;
}

vector<short> minterm::getTerm()
{
	return this->mintermVal;
}

string minterm::toString()
{
	char alphabet[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	string result = "";
	for(unsigned int i = 0; i < this->getTerm().size(); i++)
	{
		if(this->getTerm()[i] != X)
		{
			result += alphabet[i];
			if(this->getTerm()[i] == 0)
			{
				result += "'";
			}
		}
	}
	return result;
}

bool minterm::equals(minterm& other)
{
	vector<short>::iterator it;
	vector<short> otherTerm = vector<short>(other.getTerm());
	vector<short>::iterator otherit = otherTerm.begin();
	for(int i = 0; i < this->getTerm().size(); i++)
	{
		if(this->getTerm()[i] != other.getTerm()[i])
			return false;
	}
	return true;
}