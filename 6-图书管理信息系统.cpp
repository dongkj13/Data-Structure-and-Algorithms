#include<iostream>
#include<string>
using namespace std;
class node 
{
public:
	string s[7];
	int time;
	int state;
	node*next;
	node(){next=NULL;};
	node(string s0,string s1,string s2,string s3,string s4,string s5,string s6,int time,int state):time(time),state(state)
	{
		next=NULL;
		s[0]=s0;
		s[1]=s1;
		s[2]=s2;
		s[3]=s3;
		s[4]=s4;
		s[5]=s5;
		s[6]=s6;
	};
};

class node1
{
public:
	node *no;
	node1*next;
	node1(){next=NULL;};
	node1(node* no):no(no){next=NULL;};
};

class cate
{
public:
	node1*head;
	cate(){head=NULL;};
	void insert(node1*p)
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

int calc(string s)
{
	int temp=0;
	int l=s.length();
	if (l>5) l=5;
	for (int i=0;i<l;i++)
	{
		int t=int(s[i]);
		temp+=t*t;
	}
	return temp%9997;
};

int main()
{
	cate c[7][9997];
	char req;
	cin>>req;
	int booknum=0;
	while (req!='q')
	{
		switch (req)
		{
		case 'a':
			{
				string s[7];
				for (int i=0;i<7;i++)
					cin>>s[i];
				node* p1=new node(s[0],s[1],s[2],s[3],s[4],s[5],s[6],-1,0);
				
				for (int i=0;i<7;i++)
				{
					int temp=calc(s[i]);
					node1 *p=new node1(p1);
					c[i][temp].insert(p);
				}
				break;
			}
		case 'l':
			{
				string str;
				cin>>str;
				int t;
				cin>>t;
				int temp=calc(str);
				node1 *p=c[0][temp].head;
				while (p!=NULL)
				{
					if (p->no->s[0]==str)
					{
						p->no->time=t;
						p->no->state=1;
					}
					p=p->next;
				}
				break;
			}
		case 'd':
			{
				string str;
				cin>>str;
				int temp=calc(str);
				node1 *p=c[0][temp].head;
				while (p!=NULL)
				{
					if (p->no->s[0]==str)
						p->no->state=-1;
					p=p->next;
				}
				break;
			}
		case 'g':
			{
				string str;
				cin>>str;
				int temp=calc(str);
				node1 *p=c[0][temp].head;
				while (p!=NULL)
				{
					if (p->no->s[0]==str)
						p->no->state=0;
					p=p->next;
				}
				break;
			}
		case 's':
			{
				int re;
				cin>>re;					
				string str;
				cin>>str;
				int t;
				cin>>t;
				int temp=calc(str);
				node1 *p=c[re][temp].head;
				bool flag=false;
				if (p==NULL) cout<<-1<<endl;
				else
					while (p!=NULL)
					{
						if ((p->no->state!=-1)&&(p->no->s[re]==str)) 
						{
							flag=true;
							if (p->no->state==0)
							{
								cout<<"Book State: 0"<<endl;
								cout<<"Book Info: ";
								for (int i=0;i<7;i++)
									cout<<p->no->s[i]<<" ";
								cout<<endl;
							}
							else
								if (t<=p->no->time+10)
								{
									cout<<"Book State: 1 "<<p->no->time+10<<endl;
									cout<<"Book Info: ";
									for (int i=0;i<7;i++)
										cout<<p->no->s[i]<<" ";
									cout<<endl;
								}
								else 
								{
									cout<<"Book State: 2"<<endl;
									cout<<"Book Info: ";
									for (int i=0;i<7;i++)
										cout<<p->no->s[i]<<" ";
									cout<<endl;
								}
						}
						p=p->next;
					};
				if (!flag) cout<<-1<<endl;
				break;

			}
			}
			cin>>req;
			}
}