#include <iostream>
#include <cstdlib>

using namespace std;

class Matrix
{
private:
	double** a;
	int x,y;
public:
	void Create(int x, int y);
	void WriteRow(int i);
	void ShowRow(int i);
	void SwapRows(int x, int y);
	int MaxInACol(int i);
};

class Vector
{
private:
	double* a;
	int x;
public:
	void Create(int x);
	void Write(int i);
	void SetPerm();
	void ShowElem(int i);
	void Show();
	void Swap(int x, int y);
};

class System
{
private:
	Matrix a;
	Vector right;
	Vector perm;
	int x,y;
protected:
	
public:
	void Data();
	void Show();
	void Gauss();
};

void System::Data()
{
	int i;
	cout << "Кол-во уравнений и переменных\n";
	cin >> x >> y;
	a.Create(x,y);
	right.Create(x);
	perm.Create(x);
	cout << "Система уравнений\n";
	for (i=0; i<x; i++)
	{
		a.WriteRow(i);
		right.Write(i);
	}
	perm.SetPerm();
}

void Matrix::WriteRow(int i)
{
	for (int j=0; j<y; j++)
	{	
		cin >> a[i][j];
	}
}

void Vector::Write(int i)
{
	if (i<=x)
		cin >> a[i];
	else throw "Cyka blyad'";
}

void Matrix::Create(int x, int y)
{
	int i;
	a = new double*[x];
	for (i=0; i<x; i++)
		a[i] = new double[y];
	this->x = x;
	this->y = y;
}

void Vector::Create(int x)
{
	a = new double[x];
	this->x = x;
}

void Vector::SetPerm()
{
	for (int i=0; i<x; i++)
		a[i]=i;
}

void System::Show()
{
	int i;
	for (i=0; i<x; i++)
	{
		a.ShowRow(i);
		cout << " | ";
		right.ShowElem(i);
		cout << endl;
	}
	perm.Show();
}

void Matrix::ShowRow(int i)
{
	for (int j=0; j<y; j++)
		cout << " " << a[i][j] << " ";
}

void Vector::ShowElem(int i)
{
	cout << a[i];
}

void Vector::Show()
{
	for (int i=0; i<x; i++)
		cout << " " << a[i] << " ";
}

void Matrix::SwapRows(int x, int y)
{
	double* tmp;
	tmp=a[x];
	a[x]=a[y];
	a[y]=tmp;
}

int Matrix::MaxInACol(int i)
{
	int max=0;
	for (int j=i; j<y; j++)
	{
		if (abs(a[j][i])<abs(a[max][i]))
			max=j;
	}
	return max;
}

void Vector::Swap(int x, int y)
{
	double tmp;
	tmp=a[x];
	a[x]=a[y];
	a[y]=tmp;
}

void System::Gauss()
{
	int i,j,k=max(x,y);
	double max,zero=y;
	for (i=0; i<k,i<y; i++)
	{
		max=a.MaxInACol(i);
		if (a[max][i]!=0)
		{
			
		} else
		{
			a.SwapRows(i,y-1)
		}
	}
}

int main()
{
	System sys;
	sys.Data();
	sys.Show();
	return 0;
}
