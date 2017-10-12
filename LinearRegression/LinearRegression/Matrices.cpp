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
	vector<double> v3;
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<double>());
	return accumulate(v3.begin(), v3.end(), 0.0);
}

/* Matrix stuff*/

vector<double> Matrix::Row(int i) {
	return this->M[i];
}

vector<double> Matrix::Col(int i) {
	vector<double> ColVec;
	int nrows = this->M.size();
	for (int j = 0; j < nrows; j++) {
		ColVec.push_back(this->M[j][i]);
	}
	return ColVec;
}

Matrix Matrix::Transpose() {
	Matrix C;
	int ncols = this->M[0].size();
	for (int i = 0; i < ncols; i++) {
		C.M.push_back(this->Col(i));
	}
	return C;
}

Matrix Matrix::PrincipalMinor(int i, int j) {
	Matrix C;
	vector<double> EmptyVector;
	int nrows = this->M.size();
	int ncols = this->M[0].size();
	int indexk = 0;
	for (int k = 0; k < nrows; k++) {
		if (k != i) {

			C.M.push_back(EmptyVector);
			for (int l = 0; l < ncols; l++) {
				if (l != j) {

					C.M[indexk].push_back(this->M[k][l]);
				}
			}
			indexk += 1;
		}
	}
	return C;
}

double Matrix::Determinant() {
	double det;
	vector<vector<double>>mat = this->M;
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
			det += ((double)pow(-1, i))*mat[0][i] * (this->PrincipalMinor(0, i)).Determinant();
		}

	}
	return det;
}

Matrix Matrix::Adjoint() {
	Matrix C;
	vector<double> EmptyVector;
	int nrows = this->M.size();
	int ncols = this->M[0].size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(EmptyVector);
		for (int j = 0; j < ncols; j++) {
			C.M[i].push_back(pow(-1, i - j)*(this->PrincipalMinor(i, j).Determinant()));
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
	return (this->Adjoint())*pow(this->Determinant(), -1.0);
}

void Matrix::PrintMatrix() {
	int nrows = this->M.size();
	int ncols = this->M[0].size();
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			cout << this->M[i][j] << ",";
		}
		cout << "\n";
	}
}

Matrix Matrix::operator+(Matrix &B) {
	Matrix C;
	int nrows = this->M.size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(AddTwoVectors(this->Row(i), B.Row(i)));
	}
	return C;
}

Matrix Matrix::operator*(Matrix &B) {
	Matrix C;
	vector<double> EmptyVector;
	int nrowsA = this->M.size();
	int ncolsA = this->M[0].size();
	int nrowsB = B.M.size();
	int ncolsB = B.M[0].size();
	for (int i = 0; i < nrowsA; i++) {
		C.M.push_back(EmptyVector);
		for (int j = 0; j < ncolsB; j++) {
			C.M[i].push_back(VectorDotProduct(this->Row(i), B.Col(j)));
		}
	}
	return C;
}



Matrix Matrix::operator-(Matrix &B) {
	Matrix C;
	int nrows = this->M.size();
	for (int i = 0; i < nrows; i++) {
		C.M.push_back(SubtractTwoVectors(this->Row(i), B.Row(i)));
	}
	return C;
}

Matrix Matrix::operator/(Matrix &B) {
	return (*this)*(B.Inverse());
}