#include <iostream>

using namespace std;

int main(int agrc, char* argv[])
{
	for (int i = 0; i < agrc; i++)
	{
		cout << argv[i] << endl;
	}

	return 0;
}