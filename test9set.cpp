#include <iostream>
#include <set>

using namespace std;



int main()
{
	set<string> fruits;
	fruits.insert("apple");
	fruits.insert("orange");
	fruits.insert("banana");

	for(set<string>::iterator it=fruits.begin(); it!=fruits.end();it++)
		cout << *it << endl;


	return 0;
}
