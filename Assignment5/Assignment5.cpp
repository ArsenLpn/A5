// Assignment5.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include "json.hpp"
#include <vector>
#include <algorithm>


using namespace std;
using namespace nlohmann;

//argv[0] is the exe file
//argv[1] is -s 
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

	friend ostream& operator<<(ostream& out, Data& data)
	{
		out << setw(5) << data.id << setw(10) << data.type << setw(15) << data.name << setw(15) << data.batter << setw(30) << data.topping;
		return out;
	}

	Data(string id = "null",string type = "null",string name = "null", string batter = "null",string topping = "null"){
		this->id = id;
		this->name = name;
		this->topping = topping;
		this->type = type;
		this->batter = batter;
	}
};

bool compareId(Data& d1, Data& d2){return d1.id<d2.id;}

bool compareType(Data& d1, Data& d2){return d1.type<d2.type;}
bool compareName(Data& d1, Data& d2){return d1.name<d2.name;}
bool compareBatter(Data& d1, Data& d2){return d1.batter<d2.batter;}
bool compareTopping(Data& d1, Data& d2){return d1.topping<d2.topping;}

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
	oFile << setw(5) << "id" << setw(10) << "type" << setw(15)<< "name" << setw(15)<< "batter" << setw(30)<< "topping"<<'\n';



	for(size_t i = 0; !j["items"]["item"][i].is_null();++i)
	{//iterates through item

		for(size_t k = 0; !j["items"]["item"][i]["batters"]["batter"][k].is_null();++k)
		{//should iterate through batter

			for(size_t l = 0; !j["items"]["item"][i]["topping"][l].is_null();++l)
			{
				data.push_back(*new Data(
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
	for(vector<Data>::iterator it = data.begin(); it != data.end(); ++it)
		cout << *it << '\n';
	string temp = argv[2];
	/*switch(temp)
	{
		case "type":
			sort(data.begin(), data.end(), compareType);
			break;
		case "name":
			sort(data.begin(), data.end(), compareName);
			break;
		case "batter":
			sort(data.begin(), data.end(), compareBatter);
			break;
		case "topping":
			sort(data.begin(), data.end(), compareTopping);
			break;

		case "id":
		default:
			sort(data.begin(), data.end(), compareTopping);
			break;
	}*/
	if(!temp.compare("type")){
		sort(data.begin(), data.end(), compareType);
		cout<<1;
	}
	else if(!temp.compare("name")){
		sort(data.begin(), data.end(), compareName);
		cout<<"\n\n\n"<<"here"<<"\n\n\n";
	}
	else if(!temp.compare("batter")){
		sort(data.begin(), data.end(), compareBatter);
		cout<<3;
	}
	else if(!temp.compare("topping")){
		sort(data.begin(), data.end(), compareTopping);
		cout<<4;
	}
	else{
		sort(data.begin(), data.end(), compareId);
		cout<<5;
	}

	for(vector<Data>::iterator it = data.begin(); it != data.end(); ++it)
		oFile << *it << '\n';





	//oFile << setw(3) << j << '\n';



	iFile.close();
	oFile.close();

	//cin.get();

    // create JSON arrays
	return 0;
}

