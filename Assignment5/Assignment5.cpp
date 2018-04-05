// Assignment5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


using namespace std;
int main(int argc, char * argv[])
{
	cout << "number of arguments: " << argc << endl;
	cout << "command line arguments: ";
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i];
		cout <<endl;
	}
	cout << endl;

	//source file opening
	ifstream sFile(argv[1]);
	if (!sFile.is_open())
		cout << "\nFIle is unavailable";

	//target file openning
	ofstream tFile(argv[2]);
	if (!tFile.is_open())
		cout << "\nFIle is unavailable";

	tFile << 

	sFile.close();
	tFile.close();

	cin.get();
	return 0;
}

