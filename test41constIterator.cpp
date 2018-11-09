/****
若需增加const_iterator则需要进行重写另一个iterator，也可以通过修改iterator模板声明格式进行修改，满足其iterator格式
****/

#include <iostream>
#include <iterator>
 
using namespace std;
 
template <typename T>
struct _A_node {
    _A_node *next;
    _A_node *prev;
    T data;
};
 
template <class T,class Ref,class Ptr>
class A_Iterator:public iterator<forward_iterator_tag,T>
{
public:
    typedef A_Iterator<T,T&,T*> iterator;
    typedef A_Iterator<T,const T&,const T*> const_iterator;
private:
    typedef A_Iterator<T,Ref,Ptr> self;
 
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
     
    Ref operator*() const { return _node->data;}
    Ptr operator->() const {return &(operator*());}
     
    bool operator==(const self& __x) const {
        return _node == __x._node;
    }
 
    bool operator!=(const self& __x) const {
        return _node != __x._node;
    }
 
    self& operator++() { incr(); return *this;}
    self operator++(int) { self __tmp = *this; incr(); return __tmp;}
};
 
 
 
template <typename T>
class A {
private:
    typedef T Node;
    _A_node<T> *pNode;
public:
    typedef typename A_Iterator<T,T&,T*>::iterator iterator;
    typedef typename A_Iterator<T,const T&,const T*>::const_iterator const_iterator;
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
     
    const_iterator const_begin() const {return (_Node *)(pNode->next);}
    const_iterator const_end() const {return pNode;}
     
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
    //a.pop();
    /*
    for(A<int>::iterator iter = a.begin();iter != a.end();iter++) {
            *iter = 3;
            std::cout << "value:" << *iter << std::endl;
    }
    */
    //A<int>::const_iterator iter = a.const_begin();
     
    for(A<int>::const_iterator iter = a.const_begin();iter != a.const_end();iter++) {
        //*iter = 3;
        std::cout << "value:" << *iter << std::endl;
    }
     
    int b = a.pop();
 
    std::cout << (a.begin() == a.end()) << ",b:" << b << std::endl;
    return 0;
}