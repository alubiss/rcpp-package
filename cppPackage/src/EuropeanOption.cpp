#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"getOneGaussianByBoxMueller.h"
#include"EuropeanOption.h"


//definition of constructor

EuropeanOption::EuropeanOption(
  int nInt_,
  double strike_,
  double spot_,
  double vol_,
  double r_,
  double expiry_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		generatePath();
  	}

double EuropeanOption::GetOneGaussianByBoxMuller(){
	double result;

	double x;
	double y;

	double sizeSquared;
	do {
		x = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
		y = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
		sizeSquared = x * x + y * y;
	}
	while ( sizeSquared >= 1.0);

	result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

	return result;

}

//method definition
void EuropeanOption::generatePath(){
  double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
  double cumShocks = 0;
  thisPath.clear();
  
  	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}

//method definition
double EuropeanOption::getMaxEuropeanPrice(){
  
  	double Max = thisPath[0];
	double el;
  
  		for(int i = 0; i < nInt; i++){

			el = thisPath[i];

   			if (el > Max) {
      	
			Max = el;
   
	 			}
  			}
  
  	return Max;
}

double EuropeanOption::getPutUpAndIn(int nReps){
  
  double rollingSum = 0.0;
  double thisMax = 0.0;
  double barrier = 85;
  
  for(int i = 0; i < nReps; i++){
    	generatePath();
    	thisMax = getMaxEuropeanPrice();
    		if (thisMax > barrier){
      			double PayOff = strike - thisPath[i-1];
      			if (PayOff > 0) 
				rollingSum += PayOff;
    }
  }
  
  return exp(-r*expiry)*rollingSum/double(nReps);
  
}

double EuropeanOption::operator()(char char1, char char2, int nReps){
  if ((char1 == 'A') & (char2 =='C')) return getPutUpAndIn(nReps);
  else return -99;
}