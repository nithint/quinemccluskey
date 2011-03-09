#pragma once
#include <vector>

class minterm
{
protected:
	vector<short>mintermVal; // bits of 'this' minterm eg:0001

public:
	minterm(short);
	~minterm();

	minterm canCombine(minterm &minterm); //compares the objs mintermVal with parameters and returns the 
	//combined value else returns NULL.
	int countParameters(short); // returns the no.of parameters present in the minterm
	// get the actual term 
	vector<short> getTerm();
	// returns true if other covers this minterm, false otherwise
	bool coveredBy(minterm other);

	string toString();
};