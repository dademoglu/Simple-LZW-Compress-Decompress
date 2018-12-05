#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include "BinarySearchTree.h"
using namespace std;

int dictSize = 256; //global because this is constant and won't be manipulated. Only in compression state.

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
		if( this->key == rhs.key)
		{
			return true;
		}
		return false;
	}
	//compares string
	bool operator!=( const Data & rhs ) const {  //== is overloaded because I just want to see that if keyword of both data are equal
		if( this->key != rhs.key)
		{
			return true;
		}
		return false;
	}
	//compares index
	bool operator<( const Data & rhs ) const {  //i'm sorting to find keys faster
		if( this->key < rhs.key)
		{
			return true;
		}
		return false; 
	}
	//compares index
	bool operator>( const Data & rhs ) const {  
		if( this->key > rhs.key)
		{
			return true;
		}
		return false;
	}
	//output override
	friend ostream &operator<<( ostream &output, const Data &D ) { //this is just for debugging
		output << " index: " << D.index << " key : " << D.key;
		return output;            
	}

};




void compression(string txtfile, BinarySearchTree<Data> & dictionary){

	ifstream input;  
	string filename = txtfile; //open input file
	input.open(filename.c_str());

	if (input.fail() )
	{   cout << "could not open file " << filename << endl; 
	return;
	}	

	ofstream  out;
	string outfile = "compout.txt"; //open output file
	out.open(outfile.c_str()); 
	string result, linereader;
	char nextchar, firstchar, k;
	bool flag = false;
	string newword, testword, line, inputfile;
	Data datakey, testkey, tempkey;
	while(input.get(k)){ //take all characters from the beginning
		firstchar = k;
		newword += firstchar;//if first char is going to be put in the output, i need to sepereate two chars i'll take
		testword = newword;
		if(input.peek() == EOF){
			out << int(k) << " ";
			break;
		}
		input.get(k);
		nextchar = k; 
		newword += nextchar;
		datakey = Data(dictSize, newword); //two dumb data that i'll play on them later on
		testkey = Data(dictSize, newword);
		if(!dictionary.contains(datakey,dictionary.root)){ //if it's a single char, find the ASCII value
			out << int(firstchar) << " ";
		}
		while(dictionary.contains(datakey,dictionary.root) && input.peek() !=  EOF ){ //if word is in dictionary keep looking for the longer version
			input.get(k);
			nextchar = k;
			datakey.key += nextchar;

			if(!dictionary.contains(datakey,dictionary.root)){// if the new key that will be inserted is found, print the previous longest output
				out << dictionary.find(testkey, dictionary.root)->element.index<< " ";
				if(input.peek() ==  EOF){ //check if eof and if it has written to output
					flag = true;
				}
			}
			if(input.peek() !=  EOF) //if end of file don't change test key because i'll use it to check the word
				testkey.key = datakey.key;	
		}
		if(dictionary.contains(datakey,dictionary.root) && input.peek() ==  EOF) //if exist and it's eof
		{
			if(!flag)
				out << dictionary.find(datakey, dictionary.root)->element.index<< " "; //if it wasn't written before write it
			else{
				int len  = testword.length();
				int len2 = datakey.key.length();
				int totallen = len2 - len;
				if(totallen == 1)  //last added thing was a char do this
					out << int(nextchar) << " ";
				else{
					string word = datakey.key.substr(len-1, len2-1); // if it wasn't a char try to find it, if you can't find it print char by char
					char check;
					int count=0;
					tempkey = Data(datakey.index, word);
					if(dictionary.contains(tempkey, dictionary.root))
						out << dictionary.find(tempkey, dictionary.root)->element.index<< " ";
					else if(!dictionary.contains(tempkey, dictionary.root)){
						ifstream iss(tempkey.key);
						while(iss.get(check)){
							out << int(check) << " ";
						}
					}
				}
			}
			break; //since eof break the loop
		}
		if(!dictionary.contains(datakey,dictionary.root)){ //if the data wasn't add before, add it to the dictionary
			dictionary.insert(datakey, dictionary.root);
			if(input.peek() ==  EOF && flag){
				out <<  int(nextchar) << " ";
			break;	//since eof break the loop		
			}
			++dictSize; 
		}	
		if(input.peek() == EOF){//if eof, and we couldn't find the item in our list, divide the latest aded item to smaller parts and try to find it.
			int len  = testword.length();
			int len2 = datakey.key.length();
			int totallen = len2 - len;

			if(totallen == 1)
				out << int(nextchar) << " ";
			else{
				string word = datakey.key.substr(len, len2-1);
				char check;
				int count=0;
				tempkey = Data(datakey.index, word);
				if(dictionary.contains(tempkey, dictionary.root))
					out << dictionary.find(tempkey, dictionary.root)->element.index<< " ";
				else if(!dictionary.contains(tempkey, dictionary.root)){ //if it can't find the smaller part, print it char by char
					ifstream iss(tempkey.key);
					while(iss.get(check)){
						out << int(check) << " ";
					}
				}
			}
			break;//since eof break the loop
		}
		input.putback(k); //stand on the latest char that we worked on
		newword = "";
	}
	out << endl;

	out.close();
	input.close();
}

int main(){

	BinarySearchTree<Data> dictionary;
	string input;
	input = "compin.txt";
	cout << endl;
	compression(input, dictionary);




	//dictionary.printTree(dictionary.root); //debugging



	return 0;
}