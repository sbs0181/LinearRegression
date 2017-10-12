#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

/* Vector stuff*/

vector<double> AddTwoVectors(vector<double> v1, vector<double> v2);

vector<double> SubtractTwoVectors(vector<double> v1, vector<double> v2);

double VectorDotProduct(vector<double> v1, vector<double> v2);

/* Matrix stuff*/
class Matrix {
public:
	vector<vector<double>>M;

	vector<double> Row(int i);
	vector<double> Col(int i);
	Matrix Transpose();
	Matrix PrincipalMinor(int i, int j);
	double Determinant();
	Matrix Adjoint();
	Matrix Inverse();
	void PrintMatrix();

	Matrix operator+(Matrix &B);
	Matrix operator*(Matrix &B);
	Matrix operator*(const double &c);
	Matrix operator-(Matrix &B);
	Matrix operator/(Matrix &B);

};