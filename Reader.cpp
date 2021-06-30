#include "Reader.h"


Matrix_rep * Reader::load(int v0)
{
	std::string file_name;
	std::cout << "Podaj nazwe pliku: " << std::endl;
	std::cin >> file_name;
	std::ifstream inputFileStream;
	inputFileStream.open(file_name.c_str());
	if(!inputFileStream.good())
	{
		std::cout << "Blad przy otwieraniu, nacisnij przycisk";
		getch();
		return NULL;
	}
	int v;
	int e;
	int v_start;
	int v1;
	int v2;
	int cost;
	std::string data;
	getline(inputFileStream, data);
	std::istringstream inputStringStream(data);
	inputStringStream >> e;
	inputStringStream >> v;
	if(v0 == 116)
	{
		inputStringStream >> v_start;	
		std::cout << "v_start: " << v_start << std::endl;
		getch();
	}
	Matrix_rep * ans = new Matrix_rep(v);
	for(int i = 0; i < e; i++)
	{
		getline(inputFileStream, data);
		std::istringstream inputStringStream(data);
		inputStringStream >> v1;
		inputStringStream >> v2;
		inputStringStream >> cost;
		ans -> add_edge(v1, v2, cost);
		ans -> set_v_start(v_start);
	}
	return ans;
}
