// LinearRegression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include "Matrices.h"
#include "Random.h"
#include "StatisticalVector.h"
#include "LinearModel.h"

using namespace std;


int main()
{
	SetSeed();
	StatVec X1;
	X1.v = UnifRnd(0.0, 1.0, 100);
	StatVec X2;
	X2.v = UnifRnd(3.0, 5.0, 100);
	Matrix Xmat = MatrixFromStatVecs({ ones(100),X1,X2 });
	StatVec Err;
	Err.v= NormRnd(0.0, 0.01, 100);
	StatVec Y = ((X1*0.0) + (X2*5.0) + 10.0) + Err;
	LinearModel mod ( { ones(100),X1,X2 }, Y );
	cout << mod.betav[0] << " , " << mod.betav[1] << " , " << mod.betav[2] << "\n";
	cout << mod.beta.v[0] << " , " << mod.beta.v[1] << " , " << mod.beta.v[2] << "\n";
	system("pause");
    return 0;
}

