// Assignment5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <algorithm>


using namespace std;
using namespace nlohmann;

//NOTES:
//argv[0] is the exe file
//argv[1] is -s 
//argv[2] is the field by which we want to sort //
//argv[3] is the input file
//argv[4] is the output file

// very useful link
//https://codereview.stackexchange.com/questions/167121/reading-and-storing-nested-data

struct Data{																		//struct for extracted objects from .json
	string id,type,name,batter,topping;												//variables from .json

	friend ostream& operator<<(ostream& out, Data& data)							//stream operator overloading
	{
		out << setw(5) << data.id << setw(10) << data.type << setw(15) << data.name << setw(15) << data.batter << setw(30) << data.topping;
		return out;
	}

	Data(string id = "null",string type = "null",string name = "null", string batter = "null",string topping = "null"){		//constructor for the container
		this->id = id;																//fields of the container
		this->name = name;
		this->topping = topping;
		this->type = type;
		this->batter = batter;
	}
};

inline bool compareId(Data& d1, Data& d2){return d1.id<d2.id;}								//functors for sorting different field in data container
inline bool compareType(Data& d1, Data& d2){return d1.type<d2.type;}							//using st::sort
inline bool compareName(Data& d1, Data& d2){return d1.name<d2.name;}
inline bool compareBatter(Data& d1, Data& d2){return d1.batter<d2.batter;}
inline bool compareTopping(Data& d1, Data& d2){return d1.topping<d2.topping;}

int main(int argc, char * argv[])
{

	cout<<"Argument entered: "<<argc<<'\n';											//basic debug info

	try{
		if (argc < 5) {																//test for the proper amount of arguments
			cout << "bad param!\n";
			throw "No argument entered";												//break otherwise
		}

	}catch(string& str){															//catch preious exception
		cerr<<str;
		exit(1);																		//exit
	}

	for(int i=0; i<argc;++i)														//list the used arguments
		cout<<argv[i]<<'\n';

	ifstream iFile(argv[3]);														//open files
	ofstream oFile(argv[4]);

	vector<Data> data;																//create vector of data containers

	try{																			//test opened files
		if (!iFile.is_open())
			throw "\niFile is unavailable";												//exception otherwise
		if (!oFile.is_open())
			throw "\noFIle is unavailable";
	}
	catch(string& str){
		cerr<<str;
		exit(1);
	}

	json j;

	iFile >> j; // file parsed
	oFile << setw(5) << "id" << setw(10) << "type" << setw(15)<< "name" << setw(15)<< "batter" << setw(30)<< "topping"<<'\n';	//set the table headers



	for(size_t i = 0; !j["items"]["item"][i].is_null();++i)									//start from the first element of 'item' and test if it exists
	{//iterates through item

		for(size_t k = 0; !j["items"]["item"][i]["batters"]["batter"][k].is_null();++k)		//iterate trough batter variations and
		{//should iterate through batter

			for(size_t l = 0; !j["items"]["item"][i]["topping"][l].is_null();++l)				//for each variation in batter go trough toppings. => multiplying batter and topings
			{
				data.push_back(*new Data(														//create an object for each variation
					j["items"]["item"][i]["id"].get<string>() +								//Unique id, combining all intermediate ids
							j["items"]["item"][i]["batters"]["batter"][k]["id"].get<string>() +
							j["items"]["item"][i]["topping"][l]["id"].get<string>(),
					j["items"]["item"][i]["type"].get<string>(),							//cake type
					j["items"]["item"][i]["name"].get<string>(),							//name
					j["items"]["item"][i]["batters"]["batter"][k]["type"].get<string>(),	//batter type
					j["items"]["item"][i]["topping"][l]["type"].get<string>()				//topping
					));
			}
		}
	}
	for(vector<Data>::iterator it = data.begin(); it != data.end(); ++it)					//debug info: unsorted data
		cout << *it << '\n';
	string temp = argv[2];

	if(!temp.compare("type")){																//sorting using stl
		sort(data.begin(), data.end(), compareType);											//by type
		cout<<1;
	}
	else if(!temp.compare("name")){																//by name
		sort(data.begin(), data.end(), compareName);
		cout<<"\n\n\n"<<"here"<<"\n\n\n";
	}
	else if(!temp.compare("batter")){															//by batter
		sort(data.begin(), data.end(), compareBatter);
		cout<<3;
	}
	else if(!temp.compare("topping")){															//by topping
		sort(data.begin(), data.end(), compareTopping);
		cout<<4;
	}
	else{																						//default sort by id
		sort(data.begin(), data.end(), compareId);
		cout<<5;
	}

	for(vector<Data>::iterator it = data.begin(); it != data.end(); ++it)					//output result in to a file
		oFile << *it << '\n';





	//oFile << setw(3) << j << '\n';



	iFile.close();																			//close files
	oFile.close();

	cin.get();																				//hold the console

    // create JSON arrays
	return 0;																				//DONE!
}

