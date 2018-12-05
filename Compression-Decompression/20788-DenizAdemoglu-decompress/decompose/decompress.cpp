#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <fstream>
#include "BinarySearchTree.h"
using namespace std;

int dictSize = 255;

class Data{
public: 
	int index;
	string key;

	Data(){}

	//constructor
	Data(int  & in, string  & k){
		index = in;
		key = k;
	}

	//compares string
	bool operator==( const Data & rhs ) const {  //== is overloaded because I just want to see that if keyword of both data are equal
		if( this->index == rhs.index)
		{
			return true;
		}
		return false;
	}
	//compares string
	bool operator!=( const Data & rhs ) const {  //== is overloaded because I just want to see that if keyword of both data are equal
		if( this->index != rhs.index)
		{
			return true;
		}
		return false;
	}
	//compares index
	bool operator<( const Data & rhs ) const {  
		if( this->index < rhs.index)
		{
			return true;
		}
		return false; 
	}
	//compares index
	bool operator>( const Data & rhs ) const {  
		if( this->index > rhs.index)
		{
			return true;
		}
		return false;
	}
	//output override
	friend ostream &operator<<( ostream &output, const Data &D ) { 
		output << " index: " << D.index << " key : " << D.key;
		return output;            
	}

};



// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.
void decompression(string txtfile, BinarySearchTree<Data> & dictionary){

	ifstream input;  
	string filename = txtfile; 
	input.open(filename.c_str());

	if (input.fail() )
	{   cout << "could not open file " << filename << endl;
	return;
	}	

	ofstream  out;
	string outfile = "decompout.txt";
	out.open(outfile.c_str()); 
	int decode, nextcode = dictSize;
	string result, linereader, oldstring;
	string newword, testword, line, foundword;
	Data testkey, willAdd, newadd;
					
		input >> linereader;
		oldstring = char(stoi(linereader)); //for the first input only
		foundword = "";
		out << oldstring;

		while(input >> linereader){ //read every code number
			decode = stoi(linereader);
			nextcode = nextcode+1;
			testkey = Data(decode, result);
			if(dictionary.contains(testkey, dictionary.root) || decode < 256)
			{
				if(decode < 256){ //If it's a single char
					out << char(decode);
					foundword = char(decode);
					oldstring += foundword;
				}
				else{ //if it's longer
					foundword = dictionary.find(testkey, dictionary.root)->element.key;
					out << foundword;
					oldstring += foundword.at(0); //basis for the next element in the dictionary
				}
				newadd = Data(nextcode, oldstring);
				dictSize += 1;
				dictionary.insert(newadd, dictionary.root);
				oldstring = foundword;
			}
			else if(!dictionary.contains(testkey, dictionary.root))
			{
				newword = oldstring + oldstring.at(0);
				willAdd = Data(decode, newword);
				dictionary.insert(willAdd, dictionary.root);
				out << willAdd.key;
				oldstring = newword; 
			}
		}
		out << endl;
	out.close();
	input.close();
}

int main(){

	BinarySearchTree<Data> dictionary;
	string input;
	input = "compout.txt";
	cout << endl;
	decompression(input, dictionary);

	//dictionary.printTree(dictionary.root);



	return 0;
}