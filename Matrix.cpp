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
