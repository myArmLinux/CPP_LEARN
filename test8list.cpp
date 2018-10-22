#include <iostream>
#include <list>
using namespace std;


int main(){
	int ia[]={123,343,12,100,343,5,5};
//	list<int> ls;
	list<int>ls(ia,ia+7);
//	list<int> ls(2,4);
//	list<int>ls(4);

	for(list<int>::iterator it=ls.begin(); it!=ls.end(); ++it)
		std::cout << *it<<endl;

}

