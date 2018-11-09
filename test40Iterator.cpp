/****

STL模板库中有大量迭代器实现，这些迭代器隔离了算法实现与访问接口，我们也可以编写属于自己的迭代器。STL中的迭代器均继承至一个通用迭代器接口：

template <class _Category, class _Tp, class _Distance = ptrdiff_t,
          class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator {
  typedef _Category  iterator_category; //迭代器类型
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};
迭代器类型用于指明实例化迭代器的标签，如:输入迭代器(写)、输出迭代器(读)、随机访问迭代器等，算法可通过不同迭代器种类来实现各版本。


所有的迭代器种类声明如下:
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


迭代器的重要方法如下:
T& operator*() const
T* operator->() const   //smart pointer
bool operator==(const iterator & __x) const
bool operator!=(const iterator & __x) const
iterator& operator++()
iterator operator++(int)  

*****/


#include <iostream>
#include <iterator>
 
using namespace std;
 
template <typename T>
struct _A_node {
    _A_node *next;
    _A_node *prev;
    T data;
};
 
template <typename T>
class A_Iterator:public iterator<forward_iterator_tag,T>
{
private:
    typedef A_Iterator<T> self;
 
    _A_node<T> *_node;
    void incr()
    {
        _node = _node->next;
    }
     
    void decr()
    {
        _node = (_A_node<T>*)_node->prev;
    }
     
public:
    A_Iterator():_node(0) {}
    A_Iterator(_A_node<T> *x):_node(x) {}
    ~A_Iterator() {}
     
    T& operator*() const { return _node->data;}
    T* operator->() const {return &(operator*());}
     
    bool operator==(const self& __x) const {
        return _node == __x._node;
    }
 
    bool operator!=(const self& __x) const {
        return _node != __x._node;
    }
 
    self& operator++() { incr(); return *this;}
    self operator++(int) { self __tmp = *this; incr(); return __tmp;}
     
    self& operator--() {decr();return *this;}
    self operator--(int) {self __tmp = *this; decr();return __tmp;}
 
};
 
template <typename T>
class A {
private:
    typedef T Node;
    _A_node<T> *pNode;
public:
    typedef A_Iterator<T> iterator;
    typedef _A_node<T> _Node;
 
    A() {
        pNode = new _A_node<T>;
        pNode->next = pNode;
        pNode->prev = pNode;
    }
    ~A() {
        //add delete node function here
        delete pNode;
    }
 
    iterator begin() {return (_Node *)(pNode->next);}
    iterator end() {return pNode;} 
 
    ///////////////// method /////////////////////
    void push(T value)
    {
        _A_node<T> *v = new _A_node<T>;
        v->data = value;
 
        v->next = pNode->next;
        pNode->next->prev = v;
 
        pNode->next = v;
        v->prev = pNode;
         
    }
 
    T pop()
    {
        T value;
 
        _Node *next = pNode->next;
        pNode->next = next->next;
        next->next->prev = pNode;
 
        next->prev = next;
        next->next = next;
         
        value =  next->data;
        delete next;
         
        return value;
    }
};
 
int main(int argc, char *argv[])
{
    A<int> a;
    a.push(1);
    a.push(2);
    a.push(10);
    a.pop();
    for(A<int>::iterator iter = a.begin();iter != a.end();iter++) {
            std::cout << "befor change value:" << *iter << std::endl;
            *iter = 3;
            std::cout << "after change value:" << *iter << std::endl;
    }
     
    int b = a.pop();
 
    std::cout << (a.begin() == a.end()) << ",b:" << b << std::endl;
    return 0;
}