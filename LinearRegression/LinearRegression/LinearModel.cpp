
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matrices.h"
#include "Random.h"
#include "StatisticalVector.h"
#include "LinearModel.h"

using namespace std;

LinearModel::LinearModel(vector<StatVec> X, StatVec Y) {
	int n = Y.size();
	int p = X.size();
	Matrix Xmat = MatrixFromStatVecs(X);
	StatVec beta = MatrixTimesStatVec(((Xmat.Transpose()*Xmat).Inverse())*Xmat.Transpose(), Y);
	
	Yhat = MatrixTimesStatVec(Xmat, beta);
	
	RSS = ElementwiseMultiply(Yhat - Y, Yhat - Y).sum();
	TSS = ElementwiseMultiply(Y + (-Y.mean()), Y + (-Y.mean())).sum();
	Rsquared = 1.0 - RSS / TSS;
	ErrorVar = RSS / (n - p);
	SEbeta = (((Xmat.Transpose()*Xmat).Inverse())*ErrorVar).diag();
	tbeta = beta / SEbeta;
	
	signif = trues(p);
	transform(tbeta.v.begin(), tbeta.v.end(), signif.begin(), [](double x) {return (x >= 1.98 || x <= -1.98) ? true : false; });
	betav = beta.v;
}

StatVec LinearModel::Predict(vector<StatVec> Xtest) {
	return MatrixTimesStatVec(MatrixFromStatVecs(Xtest), beta);
}
