#include <iostream>


using namespace std;

int main()
{
int a[3]={1,2,3};

   int b[3];
   std::copy(a,a+3,b);
   for(int j=0;j<3;j++)
     cout<<b[j]<<endl;
}
