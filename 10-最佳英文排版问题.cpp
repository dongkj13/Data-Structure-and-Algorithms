#include<iostream>
using namespace std;

	long long c[500000],b[500000];

int main()
{
	int n,m;
	cin>>n>>m;
	int l[500000];

	for (int i=0;i<n;i++) cin>>l[i];
	int s=n-1;
	int d=l[s];
	c[s]=0;
	while (d+l[s-1]+1<=m)
	{
		d+=l[--s]+1;
		c[s]=0;
	}
	for (int i=s-1;i>=0;i--)
	{
		int j=i;
		d=l[j];
		c[i]=(m-d)*(m-d)+c[i+1];
		while (d+l[j+1]+1<=m)
		{
			d+=l[++j]+1;
			long long temp=(m-d)*(m-d)+c[j+1];
			if (temp<c[i]) c[i]=temp;
		}
	}
	s=0;
	d=l[s];
	b[s]=0;
	while (d<=m)
	{
		s++;
		b[s]=(m-d)*(m-d);
		d+=l[s]+1;
	}
	for (int i=s+1;i<n;i++)
	{
		int j=i-1;
		d=l[j];
		b[i]=(m-d)*(m-d)+b[j];
		while (d+l[j-1]+1<=m)
		{
			d+=l[--j]+1;
			long long temp=(m-d)*(m-d)+b[j];
			if (temp<=b[i]) {b[i]=temp;}
		}
	}
    unsigned long long total=9999999999999999999;
	int ansa,ansb;
	for (int i=0;i<n-1;i++)
	{
		long long p1=b[i];
		int j=i;
		d=l[j];
		while ((j+1<n)&&(d<=m))
		{
			if (p1+c[j+1]<total)
			{
				ansa=i;
				ansb=j+1;
				total=p1+c[j+1];
			}
			d+=l[++j]+1;
		}
	}
	cout<<total<<" "<<ansa<<" "<<ansb<<endl;
}
