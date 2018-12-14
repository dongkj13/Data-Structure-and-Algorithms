#include<iostream>
#include <cassert>
#include<string>
using namespace std;

class jiaogu{
public:
	int data[20];
	int l;
	jiaogu(){}
	jiaogu(int d[],int len){ l=len;for (int i=0;i<len;i++) data[i]=d[i];}
	jiaogu(jiaogu &a)
	{
		l=a.l;
		for (int i=0;i<l;i++)
			data[i]=a.data[i];
	}
	~jiaogu(){};
	void multiply()
	{
		data[0]=data[0]*3+1;
		for (int i=1;i<l;i++)
		{
			data[i]*=3;
			data[i]+=data[i-1]/10;
			data[i-1]=data[i-1]%10;
		}
		if (data[l-1]>9) {data[l]=data[l-1]/10;data[l-1]=data[l-1]%10;l++;}
	}
	void divide()
	{
		int temp=0;
		for (int i=l-1;i>=0;i--)
		{
			int t=temp*10+data[i];
			temp=t%2;
			data[i]=t/2;
		}
		if (data[l-1]==0) l--;
	}
};

template <class T> 
class Array {
private:
	T* list;	
	int size;	
public:
	Array(int sz = 50);			
	Array(const Array<T> &a);
	~Array();	
	Array<T> & operator = (const Array<T> &rhs); 
	T & operator [] (int i);	
	const T & operator [] (int i) const;	
	operator T * ();	
	operator const T * () const;	
	int getSize() const;	
	void resize(int sz);	
};

template <class T>
Array<T>::Array(int sz) {
	assert(sz >= 0);	
	size = sz;	
	list = new T [size];	
}

template <class T>
Array<T>::~Array() {
	delete [] list;
}

template <class T>
Array<T>::Array(const Array<T> &a) {
	size = a.size;
	list = new T[size];	
	for (int i = 0; i < size; i++)
		list[i] = a.list[i];
}

template <class T>
Array<T> &Array<T>::operator = (const Array<T>& rhs) {
	if (&rhs != this) {
		if (size != rhs.size) {
			delete [] list;		
			size = rhs.size;	
			list = new T[size];
		}  
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this;	
}


template <class T>
T &Array<T>::operator[] (int n) {
	assert(n >= 0 && n < size);
	return list[n];		
}

template <class T>
const T &Array<T>::operator[] (int n) const {
	assert(n >= 0 && n < size);	
	return list[n];			
}


template <class T>
Array<T>::operator T * () {
	return list;	
}

template <class T>
Array<T>::operator const T * () const {
	return list;	
}

template <class T>
int Array<T>::getSize() const {
	return size;
}

template <class T>
void Array<T>::resize(int sz) {
	assert(sz >= 0);	
	if (sz == size)	
		return;
	T* newList = new T [sz];	
	int n = (sz < size) ? sz : size;	
	for (int i = 0; i < n; i++)
		newList[i] = list[i];
	delete[] list;		
	list = newList;
	size = sz;	
}

bool isbig(jiaogu x,jiaogu y)
{
	if (y.l>x.l) return true;
	if (y.l<x.l) return false;
	for (int i=y.l-1;i>=0;i--)
	{
		if (y.data[i]>x.data[i]) return true;
		if (y.data[i]<x.data[i]) return false;
	}
};

int main()
{
	Array<jiaogu> a(50);
	string str;
	int num;
	cin>>str>>num;
	if (str=="1") cout<<1<<endl;
	else
	{
	a[0].l=str.length();
	for (int i=0;i<a[0].l;i++)
	{
		a[0].data[i]=int(str[a[0].l-i-1])-48;
	}
	bool flag=true;
	int i=0;
	while (flag)
	{
		if (a[i].data[0]%2==0) 
		{
			a[i+1]=a[i];
			a[i+1].divide();
		}
		else
		{
			a[i+1]=a[i];
			a[i+1].multiply();
		}
		i++;
		if ((a[i].l==1)&&(a[i].data[0]==1)) flag=false;
		if (i>=a.getSize()-2) a.resize(i*2);
	}

	for (int j=0;j<=i-1;j++)
		for (int k=j+1;k<=i;k++)
			if (isbig(a[j],a[k])) 
			{
				jiaogu t=a[j];
				a[j]=a[k];
				a[k]=t;
			}

	for (int k=a[num-1].l-1;k>=0;k--)
		cout<<a[num-1].data[k];
	cout<<endl;
	}
}
