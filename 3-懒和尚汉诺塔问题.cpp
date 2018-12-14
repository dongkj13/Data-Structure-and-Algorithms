#include<stdio.h>
//using namespace std;


int main()
{ 
	int n;
	scanf("%d",&n);
	int x=0;
	int y=1;
	int z=2;
	if (n%2==1) {int temp=y;y=z;z=temp;}
	int s=0;
	int i,j;
	for (i=1;i<=n-1;i++)
	{
		printf("%d %d\n",x,y);
		//cout<<x<<" "<<y<<endl;
		s++;
		for (j=1;j<=i-1;j++)
		{
			printf("%d %d\n",z,y);
			//cout<<z<<" "<<y<<endl;
			s++;
		}
		int temp=y;y=z;z=temp;
	}
	for (i=n;i>=1;i--)
	{
		printf("%d %d\n",x,y);
		//cout<<x<<" "<<y<<endl;
		s++;
		for (j=1;j<=i-2;j++)
		{
			printf("%d %d\n",z,x);
			//cout<<z<<" "<<x<<endl;
			s++;
		}
		int temp=x;x=z;z=temp;
	}
	//cout<<endl<<s<<endl;
}