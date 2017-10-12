#pragma once

using namespace std;
class Matrix;
class StatVec {
public:
	vector<double> v;

	int size();
	void print();
	double sum();
	double mean();
	double var();
	double sd();


	StatVec operator+(StatVec& b);
	StatVec operator-(StatVec& b);
	double operator*(StatVec& b);
	StatVec operator/(StatVec &b);
	StatVec operator+(const double& c);
	StatVec operator*(const double& c);
};

StatVec ElementwiseMultiply(StatVec a, StatVec b);

double Cov(StatVec a, StatVec b);

double Corr(StatVec a, StatVec b);

StatVec ones(int n);

vector<bool> trues (int n);

Matrix MatrixFromStatVecs(vector<StatVec> svecvec);

StatVec MatrixTimesStatVec(Matrix mat, StatVec vec);