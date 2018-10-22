#include <iostream>
#include <map>
#include <iterator>

using namespace std;


int main()
{
	typedef std::map<int,string> EMPLOYE_MAP;
	EMPLOYE_MAP employees;

	employees.insert(EMPLOYE_MAP::value_type(25301,"A"));
	employees.insert(EMPLOYE_MAP::value_type(25302,"B"));
	employees.insert(EMPLOYE_MAP::value_type(25303,"C"));
	employees.insert(EMPLOYE_MAP::value_type(25304,"D"));
	employees.insert(EMPLOYE_MAP::value_type(25305,"E"));


	for(EMPLOYE_MAP::iterator it=employees.begin();it!=employees.end();++it)
	{
		cout<<it->first<<"-"<<it->second<<endl;
	}


}
