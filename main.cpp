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

//destructor
minterm::~minterm(void)

//compares the objs mintermVal with parameters and returns the 
//combined value else returns NULL.
minterm minterm::canCombine(minterm& other)
{
 minterm copyOfMinterm = other; //make a copy of the other minterm
 vector<short>::iterator it;
 vector<short>::iterator otherit;
 //do a bit wise  minterm comparison and insert 'x' whereever they differ.
 for (it=this->mintermVal.begin() , otherit=copyOfMinterm.begin(); it < this->mtermVal.end(); it++ ,otherit++)
 {   
     if ( *it != *otherit)
     {
      copyOfMinterm.insert(it,'x',1);  //VERIFY:is this a valid expression?
      bitDiff++;
     }
 }
 //return the combined result ONLY if there is a one bit difference else ret NULL
 if( bitDiff==1)
 return(copyOfMinterm);
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
//checks if a given minterm is prseent 
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
