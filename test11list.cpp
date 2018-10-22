#include <iostream>

using namespace std;



template <class TYPE>
class ListNode
{
private:
	TYPE data;
	ListNode *next;
	static ListNode *CurNode;
	static ListNode *head;

public:
	ListNode()
	{
		next = NULL;
		head=CurNode=this;
	}
	ListNode(TYPE NewData)
	{
		data = NewData;
		next = NULL;
	}

};


int main()
{




}



