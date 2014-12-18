#include "BezierCurve.h"


BezierCurve::BezierCurve()
{
}

double BezierCurve::bCoef(double n, double i, double t)
{
	//double n: is the degree of our curve, in the case of a cubic curve it is 3
	//double i: the index of the Bernstein coefficient and the control point
	//double t: is the time we are evaluating at

	//Calculate the Bernstein coefficient
	return combo(n, i) * pow(1.0 - t, n - i) * pow(t, i);
}

double BezierCurve::combo(double n, double i)
{
	//C(n, i) = n! / ((n-1)! * i!)
	return factorial(n) / (factorial(n - i) * factorial(i));
}

double BezierCurve::factorial(double n)
{
	double result = 1;

	//If n is 0, by definition 0! is equal to 1
	if (n <= 0)
		return result;

	//Calculate the factorial, n * n-1 * n-2 * ... * 1
	for (double i = n; i > 0; --i)
	{
		result *= i;
	}

	return result;
}


Matrix4 BezierCurve::setMatrix(int a, int b, int c, int d){

	Matrix4 bc;
	Vector4 p0 = points[a];
	Vector4 p1 = points[b];
	Vector4 p2 = points[c];
	Vector4 p3 = points[d];
	bc.set(0, 0, p0.get(0));
	bc.set(1, 0, p0.get(1));
	bc.set(2, 0, p0.get(2));
	bc.set(3, 0, 0);

	bc.set(0, 1, p1.get(0));
	bc.set(1, 1, p1.get(1));
	bc.set(2, 1, p1.get(2));
	bc.set(3, 1, 0);

	bc.set(0, 2, p2.get(0));
	bc.set(1, 2, p2.get(1));
	bc.set(2, 2, p2.get(2));
	bc.set(3, 2, 0);

	bc.set(0, 3, p3.get(0));
	bc.set(1, 3, p3.get(1));
	bc.set(2, 3, p3.get(2));
	bc.set(3, 3, 0);

	return bc;
}

Matrix4 BezierCurve::setMatrix(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {

	Matrix4 bc;
	bc.set(0, 0, p0.get(0));
	bc.set(1, 0, p0.get(1));
	bc.set(2, 0, p0.get(2));
	bc.set(3, 0, 0);

	bc.set(0, 1, p1.get(0));
	bc.set(1, 1, p1.get(1));
	bc.set(2, 1, p1.get(2));
	bc.set(3, 1, 0);

	bc.set(0, 2, p2.get(0));
	bc.set(1, 2, p2.get(1));
	bc.set(2, 2, p2.get(2));
	bc.set(3, 2, 0);

	bc.set(0, 3, p3.get(0));
	bc.set(1, 3, p3.get(1));
	bc.set(2, 3, p3.get(2));
	bc.set(3, 3, 0);

	return bc;
}
Vector3 BezierCurve::evalBCurve(double t) {
	//Create a vector with our Bernstein coefficients
    double C0 = bCoef(3, 0, t);
    double C1 = bCoef(3, 1, t);
    double C2 = bCoef(3, 2, t);
    double C3 = bCoef(3, 3, t);
    
    Vector4 C(C0, C1, C2, C3);

    Matrix4 Mp = Matrix4(points[0].getValue(0), points[1].getValue(0),
                         points[2].getValue(0), points[3].getValue(0),
                         points[0].getValue(1), points[1].getValue(1),
                         points[2].getValue(1), points[3].getValue(1),
                         points[0].getValue(2), points[1].getValue(2),
                         points[2].getValue(2), points[3].getValue(2),
                         0.0, 0.0, 0.0, 0.0);
    
	//Calculate the final point q
	Vector4 q = Mp.mult(C);
    Vector3 temp = Vector3(q.getValue(0), q.getValue(1), q.getValue(2));
	return temp;
}

void BezierCurve::setPoints(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3) {
	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	points[3] = p3;
}
