#include <iostream>
#include <cstdlib>

using namespace std;

double abs(double x)
{
	if (x<0) return (-x);
		else return x;
}

struct Coord
{
	int x,y;
	Coord(int x, int y) {this->x=x; this->y=y;}
	int getx(){return x;}
	int gety(){return y;}
};

class Matrix
{
private:
	double** a;
	int x,y;
public:
	void Create(int x, int y);
	void WriteRow(int i);
	void ShowRow(int i);
	void SwapRows(int i, int j);
	void SwapCols(int i, int j);
	Coord Max(int i);
	double Elem(int i, int j);
	void SubRows(int i, int j, double t);
	void SetElem(int i, int j, double t);
};

double Matrix::Elem(int i, int j)
{
	return a[i][j];
}

void Matrix::WriteRow(int i)
{
	for (int j=0; j<y; j++)
	{	
		cin >> a[i][j];
	}
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

void Matrix::ShowRow(int i)
{
	for (int j=0; j<y; j++)
		cout << " " << a[i][j] << " ";
}

void Matrix::SwapRows(int i, int j)
{
	double* tmp;
	if (i!=j)
	{
		tmp=a[i];
		a[i]=a[j];
		a[j]=tmp;
	}
}

void Matrix::SwapCols(int i, int j)
{
	double tmp;
	if (i!=j)
		for (int k=0; k<x; k++)
		{
			tmp=a[k][i];
			a[k][i]=a[k][j];
			a[k][j]=tmp;
		}
}

void Matrix::SubRows(int i, int j, double t) //Не вычитает нулевые по идее метода Гаусса элементы,
//обнуляет элементы непосредственно под диагональным, чтобы не было ереси типа 1.3248796934e-11
{
	a[j][i]=0;
	for (int k=i+1; k<y; k++)
	{
		a[j][k]=a[j][k]-t*a[i][k];
	}
}

Coord Matrix::Max(int i)
{
	int maxx=i, maxy=i;
	for (int j=i; j<x; j++)
	{
		for (int k=i; k<y; k++)
		{
			if (abs(a[j][k])>abs(a[maxx][maxy]))
			{
				maxx=j;
				maxy=k;
			}
		}
	}
	return Coord(maxx,maxy);
}

void Matrix::SetElem(int i, int j, double t)
{
	a[i][j]=t;
}


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
	void SubElems(int i, int j, double t);
	double Elem(int i);
	void SubFromMatrix(int i, double t);
};

void Vector::Write(int i)
{
	if (i<=x)
		cin >> a[i];
	else throw "Wrong";
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

void Vector::ShowElem(int i)
{
	cout << a[i];
}

void Vector::Show()
{
	for (int i=0; i<x; i++)
		cout << " " << a[i] << " ";
}

void Vector::Swap(int x, int y)
{
	double tmp;
	tmp=a[x];
	a[x]=a[y];
	a[y]=tmp;
}

void Vector::SubElems(int i, int j, double t)
{
	a[j]=a[j]-t*a[i];
}

double Vector::Elem(int i)
{
	return a[i];
}

void Vector::SubFromMatrix(int i, double t)
{
	a[i]-=t;
}


class System
{
private:
	Matrix a;
	Vector right;
	Vector perm;
	int x,y,ranksys,rankright;
protected:
	
public:
	void Data();
	void Show();
	void Gauss();
	void Rank();
	void Solve();
	void RevGauss();
	void Solution();
};

void System::Data()
{
	int i;
	cout << "Кол-во уравнений и переменных\n";
	cin >> x >> y;
	a.Create(x,y);
	right.Create(x);
	perm.Create(y);
	cout << "Система уравнений\n";
	for (i=0; i<x; i++)
	{
		a.WriteRow(i);
		right.Write(i);
	}
	perm.SetPerm();
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
	cout << endl;
}

void System::Gauss()
{
	int i;
	Coord max(0,0);
	double t;
	for (i=0; (i<x) && (i<y); i++)
	{
		max=a.Max(i);
		if (a.Elem(max.getx(),max.gety())!=0)
		{
			a.SwapRows(i,max.getx());
			a.SwapCols(i,max.gety());
			right.Swap(i,max.getx());
			perm.Swap(i,max.gety());
			for (int k=i+1; k<x; k++)
			{
				t=a.Elem(k,i)/a.Elem(i,i);
				a.SubRows(i,k,t);
				right.SubElems(i,k,t);
			}
		} else
		{
			break;
		}
	}
}

void System::Rank() //Исхожу из предположения, что проделан прямой ход
{
	int i,j;
	bool flag=false;
	for (i=x-1; i>=0; i--)
	{
		for (j=0; j<y; j++)
		{
			if (a.Elem(i,j)!=0)
			{
				flag=true;
				break;
			}
		}
		if (flag) break;
	}
	ranksys=i;
	for (i=x-1; i>=0; i--)
	{
		if (right.Elem(i)!=0)
		{
			flag=true;
			break;
		}
	}
	rankright=i;
	
}

void System::RevGauss()
{
	double t;
	for (int i=ranksys; i>=0; i--)
	{
		for (int k=i-1; k>=0; k--)
		{
			t=a.Elem(k,i)/a.Elem(i,i);
			a.SetElem(k,i,0);
			right.SubElems(i,k,t);
		}
	}
}

void System::Solve()
{
	if (rankright>ranksys)
	{
		cout << "Решений нет";
	} else
	{
		cout << "Система совместна" << endl;
		if (ranksys==y-1)
		{
			RevGauss();
			cout << "Система имеет единственное решение:" << endl;
			for (int i=0; i<y; i++)
			{
				cout << "x";
				perm.ShowElem(i);
				cout << "=" << right.Elem(i)/a.Elem(i,i) << endl;
			}
		} else
		{
			cout << "Несколько решений" << endl;
			int k=y-1-ranksys;
			double t;
			for (int i=y-1; k>0; k--,i--)
			{
				cout << "Введите x" << perm.Elem(i) << "=";
				cin >> t;
				for (int j=0; j<= /*или без =*/ranksys; j++)
				{
					right.SubFromMatrix(j,a.Elem(j,i)*t);
				}
			}
			RevGauss();
			cout << "Решение:" << endl;
			for (int i=0; i<=ranksys; i++)
			{
				cout << "x";
				perm.ShowElem(i);
				cout << "=" << right.Elem(i)/a.Elem(i,i) << endl;
			}
		}
	}
}

void System::Solution()
{
	Gauss();
	Rank();
	Solve();
}

int main()
{
	System sys;
	sys.Data();
	sys.Solution();
	return 0;
}
