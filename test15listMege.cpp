//链表合并
#include <iostream>


using namespace std;

struct node
{
	int value;
	node *next;
}

node *make_list(void);
void display(node *);
void sort(node *);
node *merge(node *, node *);

int main()
{
	node *node1=make_list();
	display(node1);
	sort(node1);

	node *node2=make_list();
	display(node2);
	sort(node2);

	node *mode=merge(node1, node2);
	display(mnode);

	
	return 0;

}

node *make_list(void)
{
	node *head=new node();
	node *cur=head;
	for(int i=0; i<10; i++)
	{
		cur->value =rand()%10;
		cur->next =new node();
		cur = cur->next;
	}
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






}

















