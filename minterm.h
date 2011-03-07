#pragma once
#include <vector>

class minterm
{
protected:
	vector<short> term;
public:
	minterm(void);
	~minterm(void);

	// get the actual term 
	vector<short> getTerm();
	// returns true if other covers this minterm, false otherwise
	bool coveredBy(minterm other);
};

