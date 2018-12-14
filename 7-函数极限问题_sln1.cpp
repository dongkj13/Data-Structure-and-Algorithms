#include<iostream>
#include <cassert>
#include<string>
using namespace std;

class jiaogu{
public:
	int data[10000];
	int l;
	jiaogu(){}
	jiaogu(int len){ l=len;data[len-1]=1;for (int i=0;i<len-1;i++) data[i]=0;}
	~jiaogu(){};
	void divide(int d)
	{
		int temp=0;
		for (int i=l-1;i>=0;i--)
		{
			int t=temp*10+data[i];
			temp=t%d;
			data[i]=t/d;
		}
		while ((l>=1)&&(data[l-1]==0)) l--;
	}
};


int main()
{
	int k,s;
	cin>>k>>s;
	if (s==0) cout<<1<<endl;
	else
	{
	int size=s+k;
	int p=size/k;
	int f=2;
	int ans[10000];
	for (int i=0;i<10000;i++) ans[i]=0;
	for (int i=1;i<=p;i++)
	{
		jiaogu a(size-i*k+2);
		for (int j=2;j<=i+1;j++)
			a.divide(j);
		int temp=a.l;
		if (a.l>size) temp=size; 
		for (int j=temp-1;j>0;j--)
			ans[j-1]+=a.data[j];
		/*if (a.data[0]>=5) ans[0]+=1;*/
	}
	cout<<"1.";
	for (int i=0;i<size;i++) 
	{
		ans[i+1]+=ans[i]/10;
		ans[i]=ans[i]%10;
	}
	for (int i=size-1;i>=k+1;i--) cout<<ans[i];
	if (ans[k-1]>=5) cout<<ans[k]+1; else cout<<ans[k];
	cout<<endl;
	}
}