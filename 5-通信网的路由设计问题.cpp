#include<iostream>
using namespace std;

bool flag=true;

class node 
{
public:
	int e;
	int w;
	node *next;
	node(){next=NULL;};
	node(int e,int w):e(e),w(w){next=NULL;};
};

class gnode
{
public:
	node* head;
	gnode(){head=NULL;};
	void insert(node*p)
	{			
		if (head==NULL)
			head=p;
		else
		{

			p->next=head;
			head=p;
		}
	}
};

	

int minedge(int dist[],bool visit[],int n)
{
	int min=1000000;
	int minelem=-1;
	for (int i=0;i<n;i++)
	{
		if(visit[i]) continue;
		if(dist[i]<min)
		{
			min=dist[i];
			minelem=i;
		}
	}
	return minelem;
}

void Dijkstra(gnode g[],int dist[],int p[],int n)
{
	node *t=g[0].head;
	while (t!=NULL) {dist[t->e]=t->w;t=t->next;}
	bool visit[1000];
	for (int i=0;i<n;i++) visit[i]=false;
	visit[0]=true;
	for (int i=1;i<n;i++)
	{
		int pathnum=minedge(dist,visit,n);
		if (pathnum==-1) {flag=false;return;}
		int v=pathnum;
		visit[v]=true;
		node *t=g[v].head;
		while (t!=NULL) 
		{
			if (!visit[t->e])
				if (dist[v]+t->w<dist[t->e])
				{
					p[t->e]=v;
					dist[t->e]=dist[v]+t->w;
				}
			t=t->next;
		}		
	}
}

void prim(gnode g[],int dist[],int p[],int n)
{
	node *t=g[0].head;
	while (t!=NULL) {dist[t->e]=t->w;t=t->next;}
	bool visit[1000];
	for (int i=0;i<n;i++) visit[i]=false;
	visit[0]=true;
	for (int i=1;i<n;i++)
	{
		int pathnum=minedge(dist,visit,n);
		int v=pathnum;
		visit[v]=true;
		node *t=g[v].head;
		while (t!=NULL) 
		{
			if (!visit[t->e])
				if (t->w<dist[t->e])
				{
					p[t->e]=v;
					dist[t->e]=t->w;
				}
			t=t->next;
		}		
	}
}

void swap(int &a,int&b)
{
	int temp=a;
	a=b;
	b=temp;
}

void qsort(int p[],int end[],int dist[],int left,int right)
{
	if (left>=right) return;
	int l=left;
	int r=right;
	int pt=p[l];int endt=end[l];int distt=dist[l];
	while (l<r)
	{
		while((l<r)&&((p[r]>pt)||((p[r]==pt)&&(end[r]>endt)))) r--;
		swap(p[l],p[r]);
		swap(end[l],end[r]);
		swap(dist[l],dist[r]);
		while((l<r)&&((p[l]<pt)||((p[l]==pt)&&(end[l]<endt)))) l++;
		swap(p[l],p[r]);
		swap(end[l],end[r]);
		swap(dist[l],dist[r]);
	}
	p[l]=pt;
	end[l]=endt;
	dist[l]=distt;
	qsort(p,end,dist,left,l-1);
	qsort(p,end,dist,l+1,right);
};

int main()
{
	int n,e;
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin>>n>>e;
	//scanf("%d %d",&n,&e);
	gnode g[1000];
	for (int i=0;i<e;i++)
	{
		int x,y,t;
		//scanf("%d %d &d",&x,&y,&t);
		cin>>x>>y>>t;
		node *p1=new node(y,t);
		g[x].insert(p1);
		node *p2=new node(x,t);
		g[y].insert(p2);
	}
	int dist[1000];
	int p[1000];
	for (int i=0;i<n;i++) {dist[i]=1000000;p[i]=0;}
	Dijkstra(g,dist,p,n);
	for (int i=1;i<n;i++)
		if (dist[i]==1000000)
			//printf("%d 16777215 -1\n",i);
			cout<<i<<" 16777215 -1"<<endl;
		else
			//printf("%d %d %d\n",i,dist[i],p[i]);
			cout<<i<<" "<<dist[i]<<" "<<p[i]<<endl;
	if (flag)
	{
	for (int i=0;i<n;i++) {dist[i]=1000000;p[i]=0;}
	prim(g,dist,p,n);
	int min=0;
	for (int i=1;i<n;i++) min+=dist[i];
	//printf("%d %d\n",n-1,min);
	cout<<n-1<<" "<<min<<endl;
	int end[1000];
	for (int i=1;i<n;i++) {end[i]=i;if (i<p[i]) swap(end[i],p[i]);}
	qsort(p,end,dist,0,n-1);
	for (int i=1;i<n;i++)
		//printf("%d %d %d\n",p[i],end[i],dist[i]);
		cout<<p[i]<<" "<<end[i]<<" "<<dist[i]<<endl;
	}
	else cout<<"0 0"<<endl;
}
	