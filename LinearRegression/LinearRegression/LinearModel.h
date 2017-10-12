#pragma once
#include "StatisticalVector.h"

using namespace std;

class LinearModel {
public:
	LinearModel(vector<StatVec> X, StatVec Y);
	double RSS;
	StatVec Yhat;
	double TSS;
	double Rsquared;
	double ErrorVar;
	StatVec SEbeta;
	StatVec tbeta;
	StatVec beta;
	vector<double> betav;
	vector<bool> signif;

	
	StatVec Predict(vector<StatVec> Xtest);
};
