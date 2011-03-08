/*Filename: main.cpp
desc:main method for minlogic
*/
#include <minterm.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>
#define DONTCARE "d"

using namespace std;
//global list of prime implicants
list<minterm> primeImplicants;
/**
* convert string to number
*/
template <class T>
bool tryParse(T& t,
const std::string& s)
{
  std::istringstream iss(s);
  return !(iss >> t).fail();
}

int main(int argc, char *argv[])
{
if(argc != 2)
{
cout << "Usage: " << argv[0] << "filename" << endl;
exit(1);
}
//check if the input minterm file exists
ifstream fin(argv[1]);

if(!fin)
{
cout << "Minterm (input) file " << argv[1] << " not found." << endl;
exit(1);
}
string fileData; //used to read the implicant input file
string buffer;
list<minterm>dontCares; //list of all don't cares
list<minterm>allMinterms; //list of all minterms (this includes dc)
int noOfvars;
int noOfTerms;
   
//read the no.of vars and no of terms
getline(fin,fileData);
noOfVars= atoi(fileData.c_str());
getline(fin,fileData);
noOfTerms=atoi(fileData.c_str());
size_t found;
//read all minterms from file and add to appropriate lists
while( mintermcount< noOfTerms)
{
         getline(fin,fileData);
         //If a term is marked as dont care ,put it into the dc and mintern lists.
          size_t found=fileData.find(DONTCARE);
          if (found!=string::npos) // the term is a dont care eg: 1001 d
          {
             fileData.copy(buffer,noOfVars);
             try //NOTE to self: looks weird but might work ref http://www.codeguru.com/forum/showthread.php?t=231054
             {
                short t;
                minterm m(tryParse(t,buffer));
                dontCares.push_back(m);
                allMinterms.push_back(m);
             }
            
          }
        else //the term is not a dc - so add it only to the minterm list
         {
                         
           fileData.copy(buffer,noOfVars);
             try //NOTE to self: looks weird but might work ref http://www.codeguru.com/forum/showthread.php?t=231054
             {
                short t;
                minterm m(tryParse(t,buffer));
                allMinterms.push_back(m);
             }
         }
         mintermcount++;
             
}

vector< vector <vector<minterm> > mintermArray();

//initial setup: fill up all the uncombined terms ( all terms will end up in the first row -with zero 'x's)
for(i=0; i < mintermArray.size() ; ++i)
for ( j=0; j < mintermArray[i].size();j++)
{
    mintermit=allMinterms.begin();
       for ( mintermit=allMinterms.begin() ; mintermit != allMinterms.end(); mintermit++ )
           if (mintermit->countParameters(1)==j) //check for the no of ones only (since we know no of xs is zero anyway)
           mintermArray[i][j]=(*mintermit); //VERIFY:is this syntax right?
    }

//QM :combining terms
//run thru the array from top to bottom and check adjacent cells i,j if they can be combined
//put the result in the [i+1th][j-1th] location
for(i=0; i < mintermArray.size() ; ++i)
for ( j=0; j < mintermArray[i].size();j++)
 {
       ( minterm[i][j].canCombine(minterm[i][j]) )
    {//adjacent terms differ by one bit so combine
      
    }
    
       
 }
 



