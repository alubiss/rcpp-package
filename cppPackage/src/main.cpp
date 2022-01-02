#include<Rcpp.h>
#include<vector>
#include"EuropeanOption.h"
#include<ctime>
#include<cstdlib>

using std::vector;
using std::cout;
using std::cin;

using namespace Rcpp;

// [[Rcpp::export]]
double getPutUpAndIn(int nInt = 100,
			double S0 = 105,
                      	double StrikeK = 100,
                       	double VolR = 0.22,
                       	double Rfr = 0.05,
                       	double Time = 0.5,
                       	int nReps = 100){

	// // set the seed
	srand( time(NULL) );

	// create a new instance of class
	EuropeanOption EuropeanOption(nInt, S0, StrikeK, VolR, Rfr, Time);

	double OptionPrice =	EuropeanOption.getPutUpAndIn(nReps);

	return OptionPrice;
}