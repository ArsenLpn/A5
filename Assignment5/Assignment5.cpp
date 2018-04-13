// Assignment5.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include "json.hpp"
#include <vector>


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

	iFile >> j; // file parsed
	oFile << setw(4) << "id" << setw(10) << "type" << setw(15)<< "name" << setw(15)<< "batter" << setw(18)<< "topping";

	for(size_t i = 0; !j["items"]["item"][i].is_null();++i)
	{//iterates through item




		for(size_t k = 0; !j["items"]["item"][i]["batters"]["batter"][k].is_null();++k)
		{//should iterate through batter

			;/*write id , type , name */
		}
		for(size_t l = 0; !j["items"]["item"][i]["toppings"][l].is_null();++l){
			;
		}
	}





	//oFile << setw(3) << j << '\n';



	iFile.close();
	oFile.close();



	//cin.get();
	return 0;
}

