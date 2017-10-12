#pragma once

void SetSeed();

double UnifRnd();

double UnifRnd(double a, double b);

double NormRnd();

double NormRnd(double mu, double sigma);

vector<double> NormRnd(double mu, double sigma, int n);

void PrintVector(vector<double> vec);