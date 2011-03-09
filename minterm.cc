#include <minterm.h>
#include<string>

//constructor 
minterm::minterm(const string& mterm)
{
//fill up all the 'details'

//minterm value
this->term=mterm.c_str();

//the no.of 'ones'
while(this->onesCount < mterm.size())// QUERY:what is the correct condition to be used here ?
{
 mterm.find('1')
 this->onesCount++                 
}

//add 'x' bit positions to xpos 
size_t found;
while(i < mterm.size())  // QUERY:what is the correct condition to be used here ?
{
 found=mterm.find('x')
 if (found!=string::npos)
 {
    xpos.push_back(int(found));        
  }
  i++;
}
                             
}

minterm::~minterm(void)
{
}

