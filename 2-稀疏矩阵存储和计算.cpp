#include <iostream>
using namespace std;

class node
{
private:
public:	
	int x,y,v;	
	node *right,*down;
	node(){x = 0; y= 0; v = 0; right = NULL; down = NULL;};
	node(int x,int y,int v):x(x),y(y),v(v){right=NULL;down=NULL;}
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

//class head
//{
//pubilc:
//	node* 
int main()
{
	int m,n,l;
	cin>>m>>n>>l;
	node *row[1000];
	node *column[1000];
	for (int i=0;i<m;i++) {row[i]=NULL;column[i]=NULL;}
	node *row1[1000];
	node *column1[1000];
	for (int i=0;i<m;i++) {row1[i]=NULL;column1[i]=NULL;}
	for (int i=0;i<l;i++)
	{
		int x,y,v;
		cin>>x>>y>>v;
		if (v==0) continue;
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

//生成A+A的转置的和
		node *p2=new node(x,y,v);
		if (row1[x]==NULL) row1[x]=p2;
		else
			if (y<row1[x]->y) {p2->right=row1[x];row1[x]=p2;}
			else
			{
				node *cur=row1[x];
				node *pre=row1[x];
				while ((cur!=NULL)&&(cur->y<y)) {pre=cur;cur=cur->right;}
				if ((cur!=NULL)&&(cur->y==y)) {cur->v+=v;/*delete(p2);*/}
				else
					p2->insertrow(pre);
			}
		if (column1[y]==NULL) column1[y]=p2;
		else
			if (x<column1[y]->x) {p2->down=column1[y];column1[y]=p2;}
			else
			{
				node *cur=column1[y];
				node *pre=column1[y];
				while ((cur!=NULL)&&(cur->x<x)) {pre=cur;cur=cur->down;}
				if ((cur!=NULL)&&(cur->x==x)) {}
				else
					p2->insertcolumn(pre);
			}

		int temp=x;x=y;y=temp;
		node *p3=new node(x,y,v);
		if (row1[x]==NULL) row1[x]=p3;
		else
			if (y<row1[x]->y) {p3->right=row1[x];row1[x]=p3;}
			else
			{
				node *cur=row1[x];
				node *pre=row1[x];
				while ((cur!=NULL)&&(cur->y<y)) {pre=cur;cur=cur->right;}
				if ((cur!=NULL)&&(cur->y==y)) {cur->v+=v;/*delete(p3);*/}
				else
					p3->insertrow(pre);
			}
		if (column1[y]==NULL) column1[y]=p3;
		else
			if (x<column1[y]->x) {p3->down=column1[y];column1[y]=p3;}
			else
			{
				node *cur=column1[y];
				node *pre=column1[y];
				while ((cur!=NULL)&&(cur->x<x)) {pre=cur;cur=cur->down;}
				if ((cur!=NULL)&&(cur->x==x)) {}
				else
					p3->insertcolumn(pre);
			}
	}
	for (int i=0;i<n;i++)
	{
		node *t=column[i];
		while (t!=NULL)
		{
			cout<<t->y<<" "<<t->x<<" "<<t->v<<endl;
			t=t->down;
		}
	}
	
	for (int i=0;i<n;i++)
	{
		node *t=row1[i];
		while (t!=NULL)
		{
			if (t->v!=0) cout<<t->x<<" "<<t->y<<" "<<t->v<<endl;
			t=t->right;
		}
	}
	int sum[5000];
	for (int i=0;i<m;i++)
		if (row[i]!=NULL)
		{
			for (int j=0;j<n;j++) sum[j]=0;
			node*r=row[i];
			while (r!=NULL)
			{
				int t=r->v;
				int j=r->y;
				if (column[j]!=NULL)
				{
					node*c=column[j];
					while (c!=NULL)
					{
						sum[c->x]+=t*c->v;
						c=c->down;
					}
				}
				r=r->right;
			}
			for (int j=0;j<n;j++)
				if (sum[j]!=0) cout<<i<<" "<<j<<" "<<sum[j]<<endl;
		}
}