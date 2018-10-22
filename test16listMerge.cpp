//链表合并
#include <iostream>


using namespace std;

struct node
{
	int value;
	node *next;
};

node *make_list(void);
void display(node *);
void sort(node *);
node *merge(node *, node *);

int main()
{
	node *node1;
	node1=make_list();
	cout<<"display node1"<<endl;
	display(node1);
	sort(node1);
	display(node1);

	node *node2;
	node2=make_list();
	cout<<"display node2"<<endl;
	display(node2);
	sort(node2);
	display(node2);

	node *mnode;
	mnode=merge(node1, node2);
	cout<<"display mnode"<<endl;
	display(mnode);

	cout << "end test "<< endl;
	
	return 0;

}

node *make_list(void)
{
	node *head=new node();
	node *cur=head;
	for(int i=0; i<10; i++)
	{
		cur->value =rand()%10;
		cout<< cur->value<<endl;
		cur->next =new node();
		cur = cur->next;
	}
	cur->value = 0;
	cur->next = NULL;
	return head;
}


void display(node *head)
{
	node *cur = head;
	while(cur)
	{
		cout<< cur->value<< "	";
		cur=cur->next;
	}
	cout<<endl;
}

void sort(node *head)  
{ 
	node *cur = head;
	node *min, *pos;
	while(cur)
	{
		min = cur; 
		pos= cur->next;
		while(pos)
		{		 
			if(min->value > pos->value)
			{
				min = pos;
			}
			pos=pos->next;
		}
		int tempvalue= cur->value;
		cur->value = min->value;
		min->value = tempvalue;
		cur=cur->next;
	}	

}

//确保输入的两个list是经过排序的 否则不可merge
node *merge(node *h1, node *h2)
{
	node* cur1=h1;
	node* cur2=h2;
	node* mcur=NULL;

	if (!cur1 && !cur2)
	{
		return NULL;
	}

	while(cur1&&cur2)
	{
		if (cur1->value < cur2->value)
		{
			if (NULL == mcur)
			{
				mcur = cur1;
			}
			else
			{
				mcur->next = cur1;
				mcur = cur1;
			}
			cur1=cur1->next;
		}
		else
		{
			if (NULL == mcur)
			{
				mcur = cur2;
			}
			else
			{
				mcur->next = cur2;
				mcur = cur2;
			}
			cur2= cur2->next;
		}
	}

	if(cur1)
	{
		mcur->next = cur1;
	}
	else
	{
		mcur->next = cur2;
	}

	return h1->value < h2->value?h1:h2;
}




















