#include <iostream>
#include <vector>
#include<iterator>

using namespace std;

template<typename BidirectionalIterator,typename Compare>
void sort_me(BidirectionalIterator first,BidirectionalIterator last,Compare comp)
{
	for(BidirectionalIterator i = first; i != last; ++i)
	{
		 BidirectionalIterator _last = last;
		 while(i != _last--)
		 {
			if (comp(*i,*_last))
				iter_swap(i,_last);
		 }
   }
}


int main()
{
	int ia[] = {123,343,12,100,343,5,5};
	vector<int> vec(ia,ia+7);
	sort_me(vec.begin(),vec.end(),less<int>());
	copy(vec.begin(),vec.end(),ostream_iterator<int>(cout," "));
	std::cout << endl;
}
