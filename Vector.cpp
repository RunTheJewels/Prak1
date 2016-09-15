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

void Vector::Write(int i)
{
	if (i<=x)
		cin >> a[i];
	else throw "Cyka blyad'";
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
