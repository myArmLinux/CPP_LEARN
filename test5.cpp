#include <iostream>
//#include <ostream>
#include <iterator>

using namespace std;

int main()
{
	ostream_iterator<int> output(cout," : ");  
	*output = 5;  
	*output = 6;  
	cout<<endl;
}

