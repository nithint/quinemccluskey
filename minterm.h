#pragma once
/*
Filename: minterm.h
description:header for minterm class
created:6-3-2011
*/
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;
using std::pair;
using std::make_pair;

#define DONTCARE 'd'
#define ONE 1
#define ZERO 0
#define X 2

using namespace std;
class minterm
{
protected:
	vector<short> mintermVal; // bits of 'this' minterm eg:0001

public:
	minterm();
	minterm( vector<short> term);
	~minterm();

	minterm canCombine(minterm &minterm); //compares the objs mintermVal with parameters and returns the 
	//combined value else returns NULL.
	int countParameters(short); // returns the no.of parameters present in the minterm
	// get the actual term 
	vector<short> getTerm();
	// returns true if other covers this minterm, false otherwise
	bool coveredBy(minterm other);
	bool equals(minterm& other);
	string toString();

	bool canCombine(minterm& other, minterm& combined); //compares the objs mintermVal with parameters and returns the
							  //combined value else returns NULL.
};