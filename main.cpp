#include<minterm.h>l
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <map>
#define DONTCARE //TBD

using namespace std;
//global list of prime implicants
list<minterm> primeImplicants;


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
string fileData;        //used to read the implicant input file    
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
         //If a term is marked as dont care ,put it into the dc list else add
         //it to the minterm list.
          size_t found=fileData.find(DONTCARE);
          if (found!=string::npos)
          {
             fileData.copy(buffer,noOfVars);
             minterm m(buffer);
             dontCares.push_back(m);
          }
        else
         {
             fileData.copy(buffer,noOfVars);
             minterm m(buffer);             
             allMinterms.push_back(m);
         }
         mintermcount++;        
              
}

