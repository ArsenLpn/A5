// Assignment5.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include "json.hpp"

using namespace std;
using namespace nlohmann;

//argv[0] is the exe file
//argv[1] is -s (don't know the point of that)
//argv[2] is the field by which we want to sort //
//argv[3] is the input file
//argv[4] is the output file

// very useful link

//https://codereview.stackexchange.com/questions/167121/reading-and-storing-nested-data


int main(int argc, char * argv[])
{

	cout<<"Argument entered: "<<argc<<'\n';

	try{
		if(!argc)
			throw "No argument entered";

	}catch(string& str){
		cerr<<str;
		exit(1);
	}

	for(int i=0; i<argc;++i)
		cout<<argv[i]<<'\n';

	ifstream iFile(argv[3]);
	ofstream oFile(argv[4]);

	try{
		if (!iFile.is_open())
			throw "\niFile is unavailable";
		if (!oFile.is_open())
			throw "\noFIle is unavailable";
	}
	catch(string& str){
		cerr<<str;
		exit(1);
	}

	json j;

	iFile >> j;
	oFile << setw(3) << j << '\n';



	iFile.close();
	oFile.close();



	//cin.get();
	return 0;
}

