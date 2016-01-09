#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inData;
	inData.open("Workbook1.txt");
	char c;
	while (!inData.eof())
	{
		inData >> c;
		cout << c << endl;
	}

	return 0;
}