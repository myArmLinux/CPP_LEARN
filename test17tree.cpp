//一棵树是否某条路径结点之和等于给定值。并描述算法复杂度

#include <iostream>
using namespace std;  
  
struct node  
{  
    int value;  
    node *left;  
    node *right;  
};  
  
node * build_tree(void);  
bool find(node *,int);  
  
int main()  
{  
    node *tree=build_tree();  
    int t;  
    cout<<"Enter your number:";  
    cin>>t;  
    cout<<endl;  
    cout<<find(tree,t)<<endl;  
}  
  
node *build_tree()  
{  
    int a;  
    cin>>a;  
    if(a == 0)  
        return NULL;  
    node *root=new node();  
    root->value=a;  
    root->left=build_tree();  
    root->right=build_tree();  
  
    cout<<"build tree success"<<endl;  
    return root;  
}  
  
bool find(node *root,int v)  
{  
    if(!root)  
        return false;  
    if(root->value == v)  
        return true;  
    else find(root->left,v-root->value) || find(root->right,v-root->value);  
}