#include <iostream>
#include <cmath>
using namespace std;

double a, b, x, xnach, xkon, dx, zmax = 0, zmin = 10, res, e = 2.71;

double function1(double x) { return pow(e, x); }
double function2(double x) { return pow(x, 2) + cos(x); }
double function3(double x) { return tan(x); }

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "Xнач = ";
	cin >> xnach;
	cout << "Хкон = ";
	cin >> xkon;
	cout << "dx = ";
	cin >> dx;

	if (xnach > xkon) { xnach = xnach + xkon; xkon = xnach - xkon; xnach = xnach - xkon; }

	cout << "|---------|" << "x" << "|---------|" << "y" << "|---------|" << endl;

	for (int i = 0; i <= (xkon - xnach) / dx; i++) {
		x = xnach + dx * i;

		if (x <= a)
		{
			res = function1(x);
			cout << "|---------|" << x << "|---------|" << res << "|---------|";
			if (zmin > res)
				zmin = res;

			if (zmax < res)
				zmax = res;
		}

		if ((a < x) and (x < b))
		{
			res = function2(x);
			cout << "|---------|" << x << "|---------|" << res << "|---------|";
			if (zmin > res)
				zmin = res;

			if (zmax < res)
				zmax = res;
		}

		if (x >= b)
		{
			res = function3(x);
			cout << "|---------|" << x << "|---------|" << res << "|---------|";
			if (zmin > res)
				zmin = res;

			if (zmax < res)
				zmax = res;
		}
		cout << endl;

	}
	cout << "Zmax = " << zmax << "|---------|" << "Zmin = " << zmin << endl;
	return 0;
}