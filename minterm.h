
class minterm
{
private:
string term;   //The minterm specified eg"1001"
int onesCount; //a count of the number of ones in the minterm      
vector<int> xpos; //the bit positions of 'x' in this minterm.
minterm(string)
~minterm();
};
