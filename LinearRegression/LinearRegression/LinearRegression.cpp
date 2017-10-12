// LinearRegression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matrices.h"
#include "Random.h"

using namespace std;

class vec {
public:
	vector<double> v;
	
	int size();
	void print();
	double sum();
	double mean();
	double var();
	double sd();


	vec operator+(vec& b);
	double operator*(vec& b);
	vec operator+(const double& c);
	vec operator*(const double& c);
};

vec ElementwiseMultiply(vec a, vec b) {
	vector<double> av = a.v;
	vector<double> bv = b.v;
	vector<double> cv (av.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), multiplies<double>());
	vec c;
	c.v = cv;
	return c;
}

double Cov(vec a, vec b) {
	vec ab = ElementwiseMultiply(a, b);
	return ab.mean() - (a.mean())*(b.mean());
}

double Corr(vec a, vec b) {
	return Cov(a, b) / (a.sd()*b.sd());
}

int vec::size() {
	return this->v.size();
}

void vec::print() {
	for (int i = 0; i < this->size(); i++) {
		cout << this->v[i] << " , ";
	}
	cout << "\n";
}

double vec::sum() {
	vector<double> v = this->v;
	return accumulate(v.begin(), v.end(), 0.0);
}

double vec::mean() {
	return (this->sum()) / (this->size());
}

double vec::var() {
	vec vec2 = ElementwiseMultiply(*this, *this);
	return vec2.mean() - pow(this->mean(), 2.0);
}

double vec::sd() {
	return sqrt(this->var());
}

vec vec::operator+(vec &b) {
	vector<double> av = this->v;
	vector<double> bv = b.v;
	vector<double> cv (b.v.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), plus<double>());
	vec c;
	c.v = cv;
	return c;
}

double vec::operator*(vec& b) {
	vector<double> av = this->v;
	vector<double> bv = b.v;
	vector<double> cv (bv.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), plus<double>());
	return accumulate(cv.begin(),cv.end(),0.0);
}

vec vec::operator+(const double& c) {
	vector<double> av = this->v;
	vector<double> bv (av.size());
	transform(av.begin(), av.end(), bv.begin(), [&c] (double x) {return c+x; });
	vec b;
	b.v = bv;
	return b;
}

vec vec::operator*(const double& c) {
	vector<double> av = this->v;
	vector<double> bv (av.size());
	transform(av.begin(), av.end(), bv.begin(), [&c](double x) {return c*x; });
	vec b;
	b.v = bv;
	return b;
}


int main()
{
	SetSeed();
	vec X;
	X.v = NormRnd(0.0, 1.0, 50);
	X.print();
	vec Err;
	Err.v= NormRnd(0.0, 10.0, 50);
	vec Y = ((X*3.0) + 1.0)+Err;
	Y.print();
	cout << X.var();
	system("pause");
    return 0;
}

