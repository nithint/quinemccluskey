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
//vector<int> xpos; //the bit positions of 'x' in this minterm.

public:
minterm(short);
~minterm();
minterm & operator=(const minterm &m);//overload '=' for making copies of objects
{
//just to ensure that we don't accidentally assign an obj to itself!
if(this == m)
return *this;
}

minterm canCombine(&minterm); //compares the objs mintermVal with parameters and returns the
                              //combined value else returns NULL.
int countParameters(short); // returns the no.of parameters present in the minterm

bool ifPresent(&minterm ); //to check if the passed minterm is present in the list

};


//checks if a given minterm is present 
bool ifPresent(&minterm other )
{
     int diff=0;
      vector<short>::iterator it;
      vector<short>::iterator otherit;
      for (it=this->mintermVal.begin(),otherit=other.begin() ; it < this->mtermVal.end(); it++ ,otherit++)
      {
          if((*it)!=(*otherit)) 
          diff++;
      } 
      if(diff>0) return TRUE;
      else return FALSE;
  
}
