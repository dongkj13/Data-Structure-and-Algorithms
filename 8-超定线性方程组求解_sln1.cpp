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
	const int maxn=1000;
	int m,n,l;
	cin>>m>>n>>l;
	node *column[maxn+1];
	for (int i=0;i<maxn;i++) {column[i]=NULL;}
	int pivot=-1;
	for (int i=0;i<l;i++)
	{
		int x,y;
		double v;
		cin>>x>>y>>v;
		if ((x==0)&&(pivot==-1)) pivot=y;
		node *p1=new node(x,y,v);

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

	bool f[maxn];
	for (int i=0;i<=n;i++) f[i]=false;
	node *r[maxn];
	for (int i=0;i<n;i++) r[i]=NULL;
	int x[maxn];
	for (int i=0;i<n;i++)
	{
		//node *p=row[i];
		//while ((f[p->y]) ||(abs(p->v)<acc)) p=p->right;
		node *p=column[pivot];
		while (p->x<i) 
		{
			node *rr=new node(p->x,p->y,p->v);
			if (r[i]==NULL) 
				r[i]=rr;
			else
			{
				rr->down=r[i];
				r[i]=rr;
			}

			p=p->down;
		}
		pivot=-1;
		x[i]=p->y;
		node *vhead=new node(p->x,p->y,p->v);
		node *vtemp=vhead;
		p=p->down;
		while (p!=NULL)
		{
			node *temp=new node(p->x,p->y,p->v);
			vtemp->down=temp;
			vtemp=temp;
			p=p->down;
		}

		double len=sqrt(calclength(vhead,vhead));
		if (vhead->v>acc) len=-len;
		double lenv=len*len-(vhead->v)*(vhead->v)+(vhead->v-len)*(vhead->v-len);
		vhead->v-=len;

			node *rr=new node(vhead->x,vhead->y,len);
			if (r[i]==NULL) 
				r[i]=rr;
			else
			{
				rr->down=r[i];
				r[i]=rr;
			}

		for (int j=0;j<=n;j++)
			if (!f[j])
			{
				double lenvu=calclength(vhead,column[j]);
				double lenvu1;
				if (j==vhead->y) lenvu1=lenvu;
				vtemp=vhead;
				node *ctemp=column[j];
				double ci1=0,vi1=0;
				if (ctemp->x==i+1) ci1=ctemp->v;
				node *pre1=column[j];
				int yy=ctemp->y;
				while (vtemp!=NULL)
				{
					while ((ctemp!=NULL) &&(ctemp->x<vtemp->x)) {if (ctemp->x==i+1) ci1=ctemp->v;pre1=ctemp;ctemp=ctemp->down;}
					if ((ctemp!=NULL)&&(ctemp->x==vtemp->x)) 
					{
						if (vtemp->x==i+1) {vi1=vtemp->v;ci1=ctemp->v;}
						ctemp->v-=2*lenvu/lenv*vtemp->v;
					}
					else
					{
						node *newc=new node(vtemp->x,yy,-2*lenvu/lenv*vtemp->v);

						if (vtemp->x<pre1->x) {newc->down=column[yy];column[yy]=newc;pre1=newc;}
						else
						{newc->insertcolumn(pre1);pre1=newc;}
					}
					vtemp=vtemp->down;
				}

				if ((abs(ci1-2*lenvu1/lenv*vi1)>acc)&&(j!=n)&&(j!=vhead->y)&&(pivot==-1)) pivot=j;

			}
		f[vhead->y]=true;

	}

	double b[maxn];
	for (int i=0;i<n;i++) b[i]=0;
	node* vtemp=column[n];
	while ((vtemp!=NULL)&&(vtemp->x<n))
	{
		b[vtemp->x]=vtemp->v;
		vtemp=vtemp->down;
	}

	double anst[maxn],ans[maxn];
	for (int i=n-1;i>=0;i--)
	{
		anst[i]=b[i]/r[i]->v;
		node *rr=r[i];
		while (rr!=NULL) {b[rr->x]-=anst[i]*rr->v;rr=rr->down;}
	}
	for (int i=0;i<n;i++) ans[x[i]]=anst[i];
	for (int i=0;i<n;i++) cout<<setprecision(6)<<std::fixed<<ans[i]<<endl;
	double delta=0;
	while (vtemp!=NULL)
	{
		delta+=pow(vtemp->v,2);
		vtemp=vtemp->down;
	}

	cout<<setprecision(6)<<std::fixed<<sqrt(delta)<<endl;
}



