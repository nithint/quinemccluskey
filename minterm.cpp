#include "minterm.h"
#include <vector>
#include <string>

using namespace std;

minterm::minterm(void)
{
}


minterm::~minterm(void)
{
}


bool minterm::coveredBy(minterm other)
{
	vector<short> term = other.getTerm();
	for(int i = 0; i < term.size(); i++)
	{
		if(term[i] != DONTCARE && term[i] != this.getTerm()[i])
			return false;
	}
	return true;
}

vector<short> minterm::getTerm()
{
	return this->term;
}

string minterm::toString()
{
	vector<char> alphabet = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
		'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	string result = "";
	for(int i = 0; i < term.size(); i++)
	{
		if(term[i] != DONTCARE)
		{
			result += alphabet[i];
			if(term[i] == 0)
			{
				result += "'";
			}
		}
	}
		return result;
}