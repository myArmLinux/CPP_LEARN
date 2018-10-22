#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int ia[]={123,343,12,100,343,5,5};
	vector<int> vec(ia,ia+7);
	vector<int> vec1(2,4);
	vector<int> vec2(4);

	vector<int>::iterator itEnd = vec.end();
	for(vector<int>::iterator it=vec.begin(); it!=itEnd; ++it)
		std::cout << *it<<endl;
	vector<int>::iterator it(vec.rbegin().base());
	vec.insert(it,1);

	//vector<int>::iterator it = vec.begin();
	//vec.insert(it,1);
	for(vector<int>::iterator it=vec.begin(); it!=vec.end(); ++it)
		std::cout << *it<<endl;

}