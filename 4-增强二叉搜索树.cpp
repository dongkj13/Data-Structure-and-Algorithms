#include<iostream>
using namespace std;

class Node
{
public:
	int data;
	Node *left;
	Node *right;
	Node(int data):data(data){left=right=NULL;};
};

class BTree
{
public:
	Node *head;
	BTree(){head=NULL;};
	void build(Node *BT,int d)
	{
		if (head==NULL) {Node *p=new Node(d);head=p;}
		else
		if (d<BT->data) 
		{
			if (BT->left!=NULL) build(BT->left,d);
			else
			{
				Node *p=new Node(d);
				BT->left=p;
			}
		}
		else
		{
			if (BT->right!=NULL) build(BT->right,d);
			else
			{
				Node *p=new Node(d);
				BT->right=p;
			}
		}
	}
	void pre(Node *BT,int a[],int &i)
	{
		if (BT!=NULL)
		{
			a[i++]=0;
			pre(BT->left,a,i);
			pre(BT->right,a,i);
		}
		else
			a[i++]=1;
	}
	void preorder(Node *BT)
	{
		if (BT!=NULL)
		{
			cout<<BT->data<<" ";
			preorder(BT->left);
			preorder(BT->right);
		}
		else
		{
			cout<<"#"<<" ";
		}
	}
	void inorder(Node *BT)
	{
		if (BT!=NULL)
		{
			inorder(BT->left);
			cout<<BT->data<<" ";
			inorder(BT->right);
		}
		else
			cout<<"# ";
	}
	void postorder(Node *BT)
	{
		if (BT!=NULL)
		{
			postorder(BT->left);
			postorder(BT->right);			
			cout<<BT->data<<" ";
		}
		else
			cout<<"# ";
	}
	int Depth(Node *BT)
	{
		if (BT==NULL) return(0);
		else
		{
			int i=Depth(BT->left);
			int j=Depth(BT->right);
			if (i>j) return (++i); else return(++j);
		}
	}
};


int main()
{
	int n;
	cin>>n;
	BTree *root=new BTree;
	for (int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		root->build(root->head,x);
	}
	int a[5000];
	int t=0;
	root->pre(root->head,a,t);
	root->preorder(root->head);
	cout<<endl;
	root->inorder(root->head);
	cout<<endl;
	root->postorder(root->head);
	cout<<endl;
	cout<<root->Depth(root->head)<<endl;
	int m;
	cin>>m;

	BTree*sroot=new BTree;
	for (int i=0;i<m;i++)
	{
		int x;
		cin>>x;
		sroot->build(sroot->head,x);
	}
	int b[5000];
	int s=0;
	sroot->pre(sroot->head,b,s);
	int next[5000];
	next[0]=0;
	int i=1;
	int j=0;
	while (i<s)
	{
		if (b[i]==b[j])
		{
			next[i]=j+1;
			i++;j++;
		}
		else if (j>0) j=next[j-1];
		else {next[i++]=0;}
	}
	i=0;j=0;
	int ans=0;
	while (i<t)
	{
		if (a[i]==b[j])
		{
			if (j==s-1) {ans++;i++;j=0;}
			else {i++;j++;}
		}
		else
		{
			if (j>0) j=next[j-1];
			else i++;
		}
	}
	cout<<ans<<endl;
}
