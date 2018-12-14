#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class node
{
private:
public:	
	int x,y;
	double v;
	node *right,*down;
	node(){x = 0; y= 0; v = 0; right = NULL; down = NULL;};
	node(int x,int y,double v):x(x),y(y),v(v){right=NULL;down=NULL;}
	~node(){}
	void insertrow(node*p)
	{	
		this->right=p->right;
		p->right=this;
	}
	void insertcolumn(node*p)
	{
		this->down=p->down;
		p->down=this;
	}
};

double calclength(node *p,node*q)
{
	double len=0;
	while ((p!=NULL) && (q!=NULL))
	{
		if (p->x==q->x) {len+=p->v*q->v;p=p->down;q=q->down;}
		if ((p!=NULL)&&(q!=NULL)&&(p->x>q->x)) q=q->down;
		if ((p!=NULL)&&(q!=NULL)&&(p->x<q->x)) p=p->down;
	}
	return len;
}

int main()
{
	double acc=0.000001;
	const int maxn=300;
	int m,n,l;
	cin>>m>>n>>l;
	node *row[10000];
	node *column[maxn+1];
	for (int i=0;i<maxn;i++) {column[i]=NULL;}
	for (int i=0;i<m;i++) {row[i]=NULL;}
	for (int i=0;i<l;i++)
	{
		int x,y;
		double v;
		cin>>x>>y>>v;
		node *p1=new node(x,y,v);

		if (row[x]==NULL) row[x]=p1;
		else
			if (y<row[x]->y) {p1->right=row[x];row[x]=p1;}
			else
			{
				node *cur=row[x];
				node *pre=row[x];
				while ((cur!=NULL)&&(cur->y<y)) {pre=cur;cur=cur->right;}
				p1->insertrow(pre);
			}

		if (column[y]==NULL) column[y]=p1;
		else
			if (x<column[y]->x) {p1->down=column[y];column[y]=p1;}
			else
			{
				node *cur=column[y];
				node *pre=column[y];
				while ((cur!=NULL)&&(cur->x<x)) {pre=cur;cur=cur->down;}
				p1->insertcolumn(pre);
			}

	}
	for (int i=0;i<m;i++) 
	{
		double b;
		cin>>b;
		node *p1=new node(i,n,b);
		int x=i;
		int y=n;

		if (row[x]==NULL) row[x]=p1;
		else
			if (y<row[x]->y) {p1->right=row[x];row[x]=p1;}
			else
			{
				node *cur=row[x];
				node *pre=row[x];
				while ((cur!=NULL)&&(cur->y<y)) {pre=cur;cur=cur->right;}
				p1->insertrow(pre);
			}

		if (column[y]==NULL) column[y]=p1;
		else
			if (x<column[y]->x) {p1->down=column[y];column[y]=p1;}
			else
			{
				node *cur=column[y];
				node *pre=column[y];
				while ((cur!=NULL)&&(cur->x<x)) {pre=cur;cur=cur->down;}
				p1->insertcolumn(pre);
			}

	}
	double a[maxn][maxn];
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<=i;j++)
		{
			node*c1=column[i];
			node*c2=column[j];
			a[i][j]=0;
			while ((c1!=NULL)&&(c2!=NULL))
			{
				if (c1->x==c2->x) {a[i][j]+=c1->v*c2->v;c1=c1->down;c2=c2->down;}
				while ((c1!=NULL) && (c2!=NULL) && (c1->x<c2->x)) c1=c1->down;
				while ((c2!=NULL) && (c1!=NULL) && (c1->x>c2->x)) c2=c2->down;
			}
			a[j][i]=a[i][j];
		}
		node*c1=column[i];
		node*c2=column[n];
		a[i][n]=0;
		while ((c1!=NULL)&&(c2!=NULL))
		{
			if (c1->x==c2->x) {a[i][n]+=c1->v*c2->v;c1=c1->down;c2=c2->down;}
			while ((c1!=NULL) && (c2!=NULL) && (c1->x<c2->x)) c1=c1->down;
			while ((c2!=NULL) && (c1!=NULL) &&  (c1->x>c2->x)) c2=c2->down;
		}
	}
	for (int i=0;i<n;i++)
	{
		a[i][i]=sqrt(a[i][i]);
		for (int k=i+1;k<n;k++)
		{
			a[k][i]=a[k][i]/a[i][i];
			for (int j=i+1;j<=k;j++)
			{
				a[k][j]-=a[k][i]*a[j][i];
			}
		}
	}
	double z[maxn],ans[maxn];
	for (int i=0;i<n;i++)
	{
		z[i]=a[i][n]/a[i][i];
		for (int j=i+1;j<n;j++)
			a[j][n]-=z[i]*a[j][i];
	}
	for (int i=n-1;i>=0;i--)
	{
		ans[i]=z[i]/a[i][i];
		for (int j=i-1;j>=0;j--)
			z[j]-=ans[i]*a[i][j];
	}
	for (int i=0;i<n;i++) cout<<setprecision(6)<<std::fixed<<ans[i]<<endl;
	double delta=0;
	for (int i=0;i<m;i++)
	{
		node*r=row[i];
		double temp=0;
		while ((r!=NULL)&&(r->y<n))
		{
			temp+=r->v*ans[r->y];
			r=r->right;
		}
		if (r==NULL) delta+=pow(temp,2);
		else delta+=pow(r->v-temp,2);
	}
	cout<<setprecision(6)<<std::fixed<<sqrt(delta)<<endl;
}