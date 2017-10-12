#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Matrices.h"

using namespace std;

/* Vector stuff*/

vector<double> AddTwoVectors(vector<double> v1, vector<double> v2) {
	vector<double> v3;
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<double>());
	return v3;
}

vector<double> SubtractTwoVectors(vector<double> v1, vector<double> v2) {
	vector<double> v3;
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), minus<double>());
	return v3;
}

double VectorDotProduct(vector<double> v1, vector<double> v2) {
	vector<double> v3 (v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), multiplies<double>());
	return accumulate(v3.begin(), v3.end(), 0.0);
}

/* Matrix stuff*/

vector<double> Matrix::Row(int i) {
	return M[i];
}

vector<double> Matrix::Col(int i) {
	vector<double> ColVec;
	int nrows = M.size();
	for (int j = 0; j < nrows; j++) {
		ColVec.push_back(M[j][i]);
	}
	return ColVec;
}

Matrix Matrix::Transpose() {
	Matrix C;
	int ncols = M[0].size();
	for (int i = 0; i < ncols; i++) {
		C.M.push_back(Col(i));
	}
	return C;
}

Matrix Matrix::PrincipalMinor(int i, int j) {
	Matrix C;
	vector<double> EmptyVector;
	int nrows = M.size();
	int ncols = M[0].size();
	int indexk = 0;
	for (int k = 0; k < nrows; k++) {
		if (k != i) {

			C.M.push_back(EmptyVector);
			for (int l = 0; l < ncols; l++) {
				if (l != j) {

					C.M[indexk].push_back(M[k][l]);
				}
			}
			indexk += 1;
		}
	}
	return C;
}

double Matrix::Determinant() {
	double det;
	vector<vector<double>>mat = M;
	int nrows = mat.size();
	if (nrows == 1) {
		det = mat[0][0];
	}
	else if (nrows == 2) {
		det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}
	else {
		det = 0.0;
		for (int i = 0; i < nrows; i++) {
			det += ((double)pow(-1, i))*mat[0][i] * ((PrincipalMinor(0, i)).Determinant());
		}

	}
	return det;
}

Matrix Matrix::Adjoint() {
	Matrix C;
	vector<double> EmptyVector;
	int nrows = M.size();
	int ncols = M[0].size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(EmptyVector);
		for (int j = 0; j < ncols; j++) {
			C.M[i].push_back(pow(-1, i - j)*(PrincipalMinor(i, j).Determinant()));
		}
	}
	return C;
}

Matrix Matrix::operator*(const double &c) {
	Matrix C = (*this);
	int nrows = C.M.size();
	int ncols = C.M[0].size();
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			C.M[i][j] *= c;
		}
	}
	return C;
}

Matrix Matrix::Inverse() {
	return (Adjoint().Transpose())*pow(Determinant(), -1.0);
}

void Matrix::PrintMatrix() {
	int nrows = M.size();
	int ncols = M[0].size();
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			cout << M[i][j] << ",";
		}
		cout << "\n";
	}
}

StatVec Matrix::diag() {
	StatVec vec;
	for (int i = 0; i < M.size(); i++) {
		vec.v.push_back(M[i][i]);
	}
	return vec;
}

Matrix Matrix::operator+(Matrix &B) {
	Matrix C;
	int nrows = M.size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(AddTwoVectors(Row(i), B.Row(i)));
	}
	return C;
}

Matrix Matrix::operator*(Matrix &B) {
	Matrix C;
	vector<double> EmptyVector;
	int nrowsA = M.size();//p
	int ncolsA = M[0].size();//N
	int nrowsB = B.M.size();//N
	int ncolsB = B.M[0].size();//p
	for (int i = 0; i < nrowsA; i++) {
		C.M.push_back(EmptyVector);
		for (int j = 0; j < ncolsB; j++){
			C.M[i].push_back(VectorDotProduct(Row(i), B.Col(j)));
		}
	}
	return C;
}



Matrix Matrix::operator-(Matrix &B) {
	Matrix C;
	int nrows = M.size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(SubtractTwoVectors(Row(i), B.Row(i)));
	}
	return C;
}

Matrix Matrix::operator/(Matrix &B) {
	return (*this)*(B.Inverse());
}