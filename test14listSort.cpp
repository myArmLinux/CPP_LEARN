//链表逆序

#include <iostream>
#include <list>

using namespace std;

struct Node
{
	int value;
	Node* next;
};

Node* makeList()
{
	Node* head=new Node();
	Node* cur ;
	cur = head;
	for(int i=0; i<10; i++)
	{
		cur->next = new Node();
		cur->value = rand()%10; 
		cur = cur->next;
	}
	return head;
}

Node* reverseList(Node *head)
{
	Node *prv, *cur, *next;
	if((NULL == head) || (NULL == head->next) )
		return NULL;
	prv = head;
	cur = head->next;
	next = NULL;
	while(cur)
	{
		next=cur->next;
		cur->next=prv;
		prv = cur;
		cur = next;
	}
	head->next=NULL;
	return prv;
}

void display(Node *head)
{
	Node* cur=head;

	while(cur)
	{
		cout<<cur->value<<endl;
		cur=cur->next;
	}
}

int main()
{
	Node* head;
	
	head = makeList();
	display(head);
	cout<<"...................................."<<endl;
	head = reverseList(head);
	cout<<"...................................."<<endl;
	display(head);
}





