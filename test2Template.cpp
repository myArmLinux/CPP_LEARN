
#include <iostream>
#include <algorithm>
#include <iterator>
 
using namespace std;
int main()
{
		//初始化数组
		int b[ 9 ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		ostream_iterator< int > otpt( cout, " " );
		//通过copy+ostream_iterator的方式输出原始数组
		cout << "Array a contains:\n ";
		copy( b, b + 9, otpt );
		//调用iter_swap交换b[0]和b[1]
		iter_swap( &b[0], &b[1] );
		//调用swap交换b[2]和b[3]，展示两者的区别
		swap( b[2], b[3] );
		//通过copy+ostream_iterator的方式输出交换后的数组
		cout << "\n Array a after swapping :\n ";
		copy( b, b + 9, otpt );
		cout << endl;
		return 0;

}
