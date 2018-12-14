#include <iostream>
using namespace std;

void quick_sort(int s[], int l, int r)  
{  
    if (l < r)  
    {  
        int i = l, j = r, x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j] >= x)  j--;    
            if(i < j)   
                s[i++] = s[j];  
            while(i < j && s[i] < x)   i++;    
            if(i < j)   
                s[j--] = s[i];  
        }  
        s[i] = x;  
        quick_sort(s, l, i - 1);    
        quick_sort(s, i + 1, r);  
    }  
}  

int find(int a[],int t,int j)
{
	int i=0;
	while (i<=j)
	{
		int mid=(i+j)/2;
		int temp=a[mid];
		if (t==temp) return mid;
		if (t<temp) j=mid-1;
		if (t>temp) i=mid+1;
	}
	if (i>j) return -1;
}

int main()
{
	int n1,n2;
	cin>>n1>>n2;
	int a[3000],b[3000],d[3000],n[3000];
	for (int i=0;i<n1;i++) {cin>>a[i];b[i]=0;d[i]=0;n[i]=-1;}
	quick_sort(a,0,n1-1);
	int wrongpos=0;
	int correctnum=0;
	int pre=-1;
	int min=10000000;
	int minc=10000000;
	int ans=10000000;
	int num;
	for (int i=0;i<n2;i++)
	{
		cin>>num;
		int j=find(a,num,n1-1);
		if (j!=-1)
		{
			if (b[j]<=wrongpos) 
			{
				b[j]=i;
				correctnum++;
				if (correctnum<minc) minc=correctnum;
				d[j]=correctnum;
				if (pre!=-1) n[pre]=j;
				pre=j;
				if (min==10000000) min=b[j];
				if (correctnum-minc+1==n1) 
					if (i-min+1<ans) ans=i-min+1;
			}
			else
			{
				correctnum++;
				if (n[j]==-1) {min=i;minc=correctnum;} else {min=b[n[j]];minc=d[n[j]];}
				wrongpos=b[j];
				b[j]=i;
				if (correctnum-d[j]==n1)
					if (i-min+1<ans) ans=i-min+1;
				d[j]=correctnum;
				n[pre]=j;
				pre=j;
			}
		}
	}
	cout<<ans;
}