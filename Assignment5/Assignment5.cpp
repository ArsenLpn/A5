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
class stringComp
{
	public :
		inline bool operator() (const string& s1, const string& s2)
		{
			return (!s1.compare(s2));
		}

};

struct Data{
	string id,type,name,batter,topping;

	Data(string id,string type,string name, string batter,string topping){
		this->id = id;
		this->name = name;
		this->topping = topping;
		this->type = type;
		this->batter = batter;
	}
};


int main(int argc, char * argv[])
{

	cout<<"Argument entered: "<<argc<<'\n';

	try{
		if(argc==1)
			throw "No argument entered";

	}catch(string& str){
		cerr<<str;
		exit(1);
	}

	for(int i=0; i<argc;++i)
		cout<<argv[i]<<'\n';

	ifstream iFile(argv[3]);
	ofstream oFile(argv[4]);

	vector<Data> data;

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
	oFile << setw(5) << "id" << setw(10) << "type" << setw(15)<< "name" << setw(15)<< "batter" << setw(18)<< "topping";

	cout << j["items"]["item"][0]["id"].get<string>() + "a";

	for(size_t i = 0; !j["items"]["item"][i].is_null();++i)
	{//iterates through item

		for(size_t k = 0; !j["items"]["item"][i]["batters"]["batter"][k].is_null();++k)
		{//should iterate through batter

			for(size_t l = 0; !j["items"]["item"][i]["topping"][l].is_null();++l)
			{
				cout<<"here";
					string id = j["items"]["item"][i]["id"].get<string>() +
								j["items"]["item"][i]["batters"]["batter"][k]["id"].get<string>() +
								j["items"]["item"][i]["topping"][l]["id"].get<string>();
					cout << id <<'\n';
				//data.push_back(*new Data());

			}
			;//write id , type , name
		}

	}





	//oFile << setw(3) << j << '\n';



	iFile.close();
	oFile.close();



	//cin.get();

    // create JSON arrays
	return 0;
}

