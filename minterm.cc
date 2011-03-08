/*
Filename: minterm.cc
description:class definition for minterm
created:6-3-2011
*/

#include <minterm.h>
#include<string>
#include<vector>

//constructor
minterm::minterm(const short mterm)
{
//fill up all the 'details'
//minterm value
mtermVal.push_back(mterm);
}
minterm::~minterm(void)


//compares the objs mintermVal with parameters and returns the
//combined value else returns NULL.
minterm minterm::canCombine(minterm& other)
{
//NOTE: do not modify the original use a copy
 vector<short>::iterator it;
 vector<short>::iterator otherit;
 //do a bit wise minterm comparison and insert 'x' whereever they differ.
 for (it=this->mintermVal.begin() , otherit=other.begin(); it < this->mtermVal.end(); it++ ,otherit++)
 {
     if ( *it != *otherit)
     {
      mintermVal.insert(it,'x',1); //VERIFY:is this a valid expression?
      bitDiff++;
     }
 }
 //return the result ONLY if there is a one bit difference else ret NULL
 if( bitDiff==1)
 return(mintermVal);
 else
 return NULL;
}


//counts the number of 'p's in the minterm vector and returns the count
int minterm::countParam(short p)
{
 int pcount =0;
 vector<short>::iterator it;
 for (it=this->mintermVal.begin() ; it < this->mtermVal.end(); it++ )
 {
     if( *it=p)
     pcount++;
 }
 return(pcount);
}