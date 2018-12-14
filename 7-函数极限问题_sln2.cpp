#include<iostream>
using namespace std;

int main()
{
	int k,s;
	cin>>k>>s;
	int a[1000],ans[1000];
	for (int i=0;i<s+5;i++) {a[i]=0;ans[i]=0;}
	a[s+5]=1;
	int l=s+6;
	int j=1;
	while (l>0)
	{
		for (int i=k;i<l;i++) a[i-k]=a[i];
		l-=k;
		j++;
		int temp=0;
		for (int i=l-1;i>=0;i--)
		{
			int t=temp*10+a[i];
			temp=t%j;
			a[i]=t/j;
		}
		for (int i=l-1;i>=0;i--)
			ans[i]+=a[i];
		while ((l>=1)&&(a[l-1]==0)) l--;
	}
	cout<<"1.";
	for (int i=0;i<s+5;i++) 
	{
		ans[i+1]+=ans[i]/10;
		ans[i]=ans[i]%10;
	}
	for (int i=s+4;i>=6;i--) cout<<ans[i];
	if (ans[4]>=5) cout<<ans[5]+1; else cout<<ans[5];
	cout<<endl;
}