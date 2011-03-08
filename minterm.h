#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;
using std::pair;
using std::make_pair;

class minterm
{
private:
vector<short>mintermVal; // bits of 'this' minterm eg:0001
//vector<int> xpos;        //the bit positions of 'x' in this minterm.

public:
minterm(short);
~minterm();

minterm canCombine(&minterm); //compares the objs mintermVal with parameters and returns the 
                              //combined value else returns NULL.
int countParameters(short); // returns the no.of parameters present in the minterm
};
