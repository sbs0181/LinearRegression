#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matrices.h"
#include "Random.h"
#include "StatisticalVector.h"
#include <functional>

using namespace std;

StatVec ElementwiseMultiply(StatVec a, StatVec b) {
	vector<double> av = a.v;
	vector<double> bv = b.v;
	vector<double> cv(av.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), multiplies<double>());
	StatVec c;
	c.v = cv;
	return c;
}

double Cov(StatVec a, StatVec b) {
	return (ElementwiseMultiply(a+(-a.mean()), b+(-b.mean())).sum())/(a.size());
}

double Corr(StatVec a, StatVec b) {
	return Cov(a, b) / (a.sd()*b.sd());
}

int StatVec::size() {
	return this->v.size();
}

void StatVec::print() {
	for (int i = 0; i < this->size(); i++) {
		cout << this->v[i] << " , ";
	}
	cout << "\n";
}

double StatVec::sum() {
	vector<double> v = this->v;
	return accumulate(v.begin(), v.end(), 0.0);
}

double StatVec::mean() {
	return (this->sum()) / (this->size());
}

double StatVec::var() {
	StatVec vec2 = ElementwiseMultiply(*this, *this);
	return vec2.mean() - pow(this->mean(), 2.0);
}

double StatVec::sd() {
	return sqrt(this->var());
}

StatVec StatVec::operator+(StatVec &b) {
	vector<double> av = this->v;
	vector<double> bv = b.v;
	vector<double> cv(b.v.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), plus<double>());
	StatVec c;
	c.v = cv;
	return c;
}

StatVec StatVec::operator-(StatVec &b) {
	vector<double> av = this->v;
	vector<double> bv = b.v;
	vector<double> cv(b.v.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), minus<double>());
	StatVec c;
	c.v = cv;
	return c;
}

double StatVec::operator*(StatVec& b) {
	vector<double> av = this->v;
	vector<double> bv = b.v;
	vector<double> cv(bv.size());
	transform(av.begin(), av.end(), bv.begin(), cv.begin(), multiplies<double>());
	return accumulate(cv.begin(), cv.end(), 0.0);
}

StatVec StatVec::operator/(StatVec& b) {
	StatVec c;
	vector<double> cv(b.v.size());
	transform(v.begin(), v.end(), b.v.begin(), cv.begin(), divides<double>());
	c.v = cv;
	return c;
}

StatVec StatVec::operator+(const double& c) {
	vector<double> av = this->v;
	vector<double> bv(av.size());
	transform(av.begin(), av.end(), bv.begin(), [&c](double x) {return c + x; });
	StatVec b;
	b.v = bv;
	return b;
}

StatVec StatVec::operator*(const double& c) {
	vector<double> av = this->v;
	vector<double> bv(av.size());
	transform(av.begin(), av.end(), bv.begin(), [&c](double x) {return c*x; });
	StatVec b;
	b.v = bv;
	return b;
}

StatVec ones(int n) {
	StatVec svec;
	for (int i = 0; i < n; i++) {
		svec.v.push_back(1.0);
	}
	return svec;
}

vector<bool> trues(int n) {
	vector<bool> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(true);
	}
	return vec;
}

Matrix MatrixFromStatVecs(vector<StatVec> svecvec) {
	Matrix mat;
	vector<vector<double>> m;
	for (int i = 0; i < svecvec.size(); i++) {
		mat.M.push_back(svecvec[i].v);
	}
	return mat.Transpose();
}

StatVec MatrixTimesStatVec(Matrix mat, StatVec vec) {
	Matrix vecm;
	StatVec sv;
	vecm.M = { vec.v };
	sv.v = ((mat*(vecm.Transpose())).Transpose()).M[0];
	return sv;
}