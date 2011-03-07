#include <minterm.h>
#include<string>

//constructor 
minterm::minterm(const string& mterm)
{
//fill up all the 'details'

//minterm value
this->term=mterm.c_str();

//the no.of 'ones'
while(this->onesCount < mterm.size())
{
 mterm.find('1')
 this->onesCount++                 
}
  
                             
}

minterm::~minterm(void)
{
}

