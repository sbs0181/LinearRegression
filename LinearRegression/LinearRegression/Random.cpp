#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "Matrices.h"
#include <cstdlib>
#include <ctime>

#define PI 3.1415926535 

using namespace std;

void SetSeed() {
	srand(time(NULL));
}

double UnifRnd() {
	return (double)rand() / RAND_MAX;
}

double UnifRnd(double a, double b) {
	return a + (b - a)*UnifRnd();
}

vector<double> UnifRnd(double a, double b,int n) {
	vector<double> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(UnifRnd(a, b));
	}
	return vec;
}

double NormRnd() {
	return sqrt(-2.0*log(UnifRnd()))*cos(2 * PI*UnifRnd());
}

double NormRnd(double mu, double sigma) {
	return mu + sigma*NormRnd();
}

vector<double> NormRnd(double mu, double sigma, int n) {
	vector<double> vec;
	for (int i = 0; i < n; i++) {
		vec.push_back(NormRnd(mu, sigma));
	}
	return vec;
}

void PrintVector(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << ",";
	}
}