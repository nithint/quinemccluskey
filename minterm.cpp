#include "minterm.h"


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