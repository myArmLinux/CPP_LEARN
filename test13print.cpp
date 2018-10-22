#include <iostream>
#include <vector>
#include <list>
//#include <vector>

using namespace std;
template <typename T>
void print_container(const T&);

template <typename T>
void print(const T& e) { std::cout << e; }

template <typename T>
void print_container(const T& c) {
    std::cout << "[";
    bool isFirst = true;
    for (const auto& e : c) {
        if (isFirst) isFirst = false;
        else std::cout << ",";
        print(e);
    }
    std::cout << "]";
}

int main()
{
    std::vector<int> v = {0, 1, 3, 5, 7, 9};
    std::list<int> l =  {0, 1, 3, 5, 7, 9};

	vector<char> vec_A(8);  //定义容器vec_A
 
	cout<<"Fill vec_A with 'A':"<<endl;
	fill(vec_A.begin(),vec_A.end(),'A');  //填充数据元素
 
	print_container(vec_A);

    print_container(v); 
    print_container(l);
}
