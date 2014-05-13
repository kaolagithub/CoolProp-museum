
#include "PolyMath.h"

#include "CoolPropTools.h"
#include "Exceptions.h"

#include <vector>
#include <string>
//#include <sstream>
//#include <numeric>
#include <math.h>

#include "Solvers.h"

namespace CoolProp{

BasePolynomial::BasePolynomial(){
  this->DEBUG = false;
}

/// Basic checks for coefficient vectors.
/** Starts with only the first coefficient dimension
 *  and checks the vector length against parameter n. */
bool BasePolynomial::checkCoefficients(const std::vector<long double> &coefficients, unsigned int n){
	if (coefficients.size() == n){
		return true;
	} else {
		throw ValueError(format("The number of coefficients %d does not match with %d. ",coefficients.size(),n));
	}
	return false;
}

bool BasePolynomial::checkCoefficients(std::vector< std::vector<long double> > const& coefficients, unsigned int rows, unsigned int columns){
	if (coefficients.size() == rows){
		bool result = true;
		for(unsigned int i=0; i<rows; i++) {
			result = result && checkCoefficients(coefficients[i],columns);
		}
		return result;
	} else {
		throw ValueError(format("The number of rows %d does not match with %d. ",coefficients.size(),rows));
	}
	return false;
}


/** The core of the polynomial wrappers are the different
 *  implementations that follow below. In case there are
 *  new calculation schemes available, please do not delete
 *  the implementations, but mark them as deprecated.
 *  The old functions are good for debugging since the
 *  structure is easier to read than the backward Horner-scheme
 *  or the recursive Horner-scheme.
 */

/// Simple polynomial function generator. <- Deprecated due to poor performance, use Horner-scheme instead
/** Base function to produce n-th order polynomials
 *  based on the length of the coefficient vector.
 *  Starts with only the first coefficient at T^0. */
long double BasePolynomial::simplePolynomial(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running simplePolynomial(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0.;
	for(unsigned int i=0; i<coefficients.size();i++) {
		result += coefficients[i] * pow(T,(int)i);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}
long double BasePolynomial::simplePolynomial(std::vector<std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running simplePolynomial(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0;
	for(unsigned int i=0; i<coefficients.size();i++) {
		result += pow(x,(int)i) * simplePolynomial(coefficients[i], T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

/// Simple integrated polynomial function generator.
/** Base function to produce integrals of n-th order
 *  polynomials based on the length of the coefficient
 *  vector.
 *  Starts with only the first coefficient at T^0 */
///Indefinite integral in T-direction
long double BasePolynomial::simplePolynomialInt(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running simplePolynomialInt(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0.;
	for(unsigned int i=0; i<coefficients.size();i++) {
		result += 1./(i+1.) * coefficients[i] * pow(T,(int)(i+1.));
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in y-direction only
long double BasePolynomial::simplePolynomialInt(std::vector<std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running simplePolynomialInt(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0.;
	for(unsigned int i=0; i<coefficients.size();i++) {
		result += pow(x,(int)i) * simplePolynomialInt(coefficients[i], T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}


/// Simple integrated polynomial function generator divided by independent variable.
/** Base function to produce integrals of n-th order
 *  polynomials based on the length of the coefficient
 *  vector.
 *  Starts with only the first coefficient at T^0 */
long double BasePolynomial::simpleFracInt(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running      simpleFracInt(std::vector, " << T << "): ";
	}
	long double result = coefficients[0] * log(T);
	if (coefficients.size() > 1) {
		for (unsigned int i=1; i<coefficients.size(); i++){
			result += 1./(i) * coefficients[i] * pow(T,(int)(i));
		}
	}
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

long double BasePolynomial::simpleFracInt(std::vector< std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running      simpleFracInt(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0;
	for (unsigned int i=0; i<coefficients.size(); i++){
		result += pow(x,(int)i) * polyfracint(coefficients[i],T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}


/** Simple integrated centred(!) polynomial function generator divided by independent variable.
 *  We need to rewrite some of the functions in order to
 *  use central fit. Having a central temperature Tbase
 *  allows for a better fit, but requires a different
 *  formulation of the fracInt function group. Other
 *  functions are not affected.
 *  Starts with only the first coefficient at T^0 */

///Helper functions to calculate binomial coefficients: http://rosettacode.org/wiki/Evaluate_binomial_coefficients#C.2B.2B
//long double BasePolynomial::factorial(long double nValue){
//   long double result = nValue;
//   long double result_next;
//   long double pc = nValue;
//   do {
//	   result_next = result*(pc-1);
//	   result = result_next;
//	   pc--;
//   } while(pc>2);
//   nValue = result;
//   return nValue;
//}
//long double BasePolynomial::factorial(long double nValue){
//	if (nValue == 0) return (1);
//	else return (nValue * factorial(nValue - 1));
//}
long double BasePolynomial::factorial(long double nValue){
    long double value = 1;
    for(int i = 2; i <= nValue; i++){
        value = value * i;
    }
    return value;
}

long double BasePolynomial::binom(long double nValue, long double nValue2){
   long double result;
   if(nValue2 == 1) return nValue;
   result = (factorial(nValue)) / (factorial(nValue2)*factorial((nValue - nValue2)));
   nValue2 = result;
   return nValue2;
}

///Helper functions to calculate the D vector:
std::vector<long double> BasePolynomial::fracIntCentralDvector(int m, long double T, long double Tbase){
	std::vector<long double> D;
	long double tmp;
	if (m<1) throw ValueError(format("You have to provide coefficients, a vector length of %d is not a valid. ",m));
	for (int j=0; j<m; j++){ // loop through row
		tmp = pow(-1.0,j) * log(T) * pow(Tbase,(int)j);
		for(int k=0; k<j; k++) { // internal loop for every entry
			tmp += binom(j,k) * pow(-1.0,k) / (j-k) * pow(T,j-k) * pow(Tbase,k);
		}
		D.push_back(tmp);
	}
	return D;
}

///Indefinite integral of a centred polynomial divided by its independent variable
long double BasePolynomial::fracIntCentral(std::vector<long double> const& coefficients, long double T, long double Tbase){
	if (this->DEBUG) {
		std::cout << "Running    fracIntCentral(std::vector, " << T << ", " << Tbase << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	int m = coefficients.size();
	std::vector<long double> D = fracIntCentralDvector(m, T, Tbase);
	long double result = 0;
	for(int j=0; j<m; j++) {
		result += coefficients[j] * D[j];
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}


/// Horner function generator implementations
/** Represent polynomials according to Horner's scheme.
 *  This avoids unnecessary multiplication and thus
 *  speeds up calculation.
 */
long double BasePolynomial::baseHorner(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running       baseHorner(std::vector, " << T << "): ";
	}
	long double result = 0;
	for(int i=coefficients.size()-1; i>=0; i--) {
		result *= T;
		result += coefficients[i];
	}
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

long double BasePolynomial::baseHorner(std::vector< std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running       baseHorner(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0;
	for(int i=coefficients.size()-1; i>=0; i--) {
		result *= x;
		result += baseHorner(coefficients[i], T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction
long double BasePolynomial::baseHornerInt(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running       baseHornerInt(std::vector, " << T << "): ";
	}
	long double result = 0;
	for(int i=coefficients.size()-1; i>=0; i--) {
		result *= T;
		result += coefficients[i]/(i+1.);
	}
	result = result * T;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction only
long double BasePolynomial::baseHornerInt(std::vector<std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running       baseHornerInt(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0;
	for(int i=coefficients.size()-1; i>=0; i--) {
		result *= x;
		result += baseHornerInt(coefficients[i], T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction of a polynomial divided by its independent variable
long double BasePolynomial::baseHornerFra(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running      baseHornerFra(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = 0;
	if (coefficients.size() > 1) {
		for(int i=coefficients.size()-1; i>=1; i--) {
			result *= T;
			result += coefficients[i]/(i);
		}
		result *= T;
	}
	result += coefficients[0] * log(T);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction of a polynomial divided by its 2nd independent variable
long double BasePolynomial::baseHornerFra(std::vector<std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running      baseHornerFra(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;

	long double result = 0;
	for(int i=coefficients.size()-1; i>=0; i--) {
		result *= x;
		result += baseHornerFra(coefficients[i], T);
	}

	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}


/** Integrating coefficients for polynomials is done by dividing the
 *  original coefficients by (i+1) and elevating the order by 1.
 *  Some reslicing needs to be applied to integrate along the x-axis.
 */
std::vector<long double> BasePolynomial::integrateCoeffs(std::vector<long double> const& coefficients){
	std::vector<long double> newCoefficients;
	unsigned int sizeX = coefficients.size();
	if (sizeX<1) throw ValueError(format("You have to provide coefficients, a vector length of %d is not a valid. ",sizeX));
	// pushing a zero elevates the order by 1
	newCoefficients.push_back(0.0);
	for(unsigned int i=0; i<coefficients.size(); i++) {
		newCoefficients.push_back(coefficients[i]/(i+1.));
	}
	return newCoefficients;
}

///Integrating coefficients for polynomial in terms of x(axis=true) or y(axis=false).
std::vector< std::vector<long double> > BasePolynomial::integrateCoeffs(std::vector< std::vector<long double> > const& coefficients, bool axis){
	std::vector< std::vector<long double> > newCoefficients;
	unsigned int sizeX = coefficients.size();
	if (sizeX<1) throw ValueError(format("You have to provide coefficients, a vector length of %d is not a valid. ",sizeX));

	if (axis==true){
		std::vector< std::vector<long double> > tmpCoefficients;
		tmpCoefficients = transpose(coefficients);
		unsigned int sizeY = tmpCoefficients.size();
		for(unsigned int i=0; i<sizeY; i++) {
			newCoefficients.push_back(integrateCoeffs(tmpCoefficients[i]));
		}
		return transpose(newCoefficients);
	} else if (axis==false){
		for(unsigned int i=0; i<sizeX; i++) {
			newCoefficients.push_back(integrateCoeffs(coefficients[i]));
		}
		return newCoefficients;
	} else {
		throw ValueError(format("You can only use x-axis (0) and y-axis (1) for integration. %d is not a valid input. ",axis));
	}
	return newCoefficients;
}

/** Deriving coefficients for polynomials is done by multiplying the
 *  original coefficients with i and lowering the order by 1.
 */
std::vector<long double> BasePolynomial::deriveCoeffs(std::vector<long double> const& coefficients){
	std::vector<long double> newCoefficients;
	unsigned int sizeX = coefficients.size();
	if (sizeX<1) throw ValueError(format("You have to provide coefficients, a vector length of %d is not a valid. ",sizeX));
	// skipping the first element lowers the order
	for(unsigned int i=1; i<coefficients.size(); i++) {
		newCoefficients.push_back(coefficients[i]*i);
	}
	return newCoefficients;
}

//std::vector< std::vector<long double> > BasePolynomial::deriveCoeffs(std::vector< std::vector<long double> > coefficients, unsigned int axis){
//	std::vector< std::vector<long double> > newCoefficients;
//	unsigned int sizeX = coefficients.size();
//	if (sizeX<1) throw ValueError(format("You have to provide coefficients, a vector length of %d is not a valid. ",sizeX));
//
//	if (axis==0){
//		std::vector< std::vector<long double> > tmpCoefficients;
//		tmpCoefficients = transpose(coefficients);
//		unsigned int sizeY = tmpCoefficients.size();
//		for(unsigned int i=0; i<sizeY; i++) {
//			newCoefficients.push_back(deriveCoeffs(tmpCoefficients[i]));
//		}
//		return transpose(newCoefficients);
//	} else if (axis==1){
//		for(unsigned int i=0; i<sizeX; i++) {
//			newCoefficients.push_back(deriveCoeffs(coefficients[i]));
//		}
//		return newCoefficients;
//	} else {
//		throw ValueError(format("You can only use x-axis (0) and y-axis (1) for derivation. %d is not a valid input. ",axis));
//	}
//	return newCoefficients;
//}


/** Alternatives
 *  Simple functions that heavily rely on other parts of this file.
 *  We still need to check which combinations yield the best
 *  performance.
 */
///Derivative in T-direction
long double BasePolynomial::deriveIn2Steps(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running   deriveIn2Steps(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result =  polyval(deriveCoeffs(coefficients),T);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Derivative in terms of x(axis=true) or T(axis=false).
long double BasePolynomial::deriveIn2Steps(std::vector< std::vector<long double> > const& coefficients, long double x, long double T, bool axis){
	if (this->DEBUG) {
		std::cout << "Running   deriveIn2Steps(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = polyval(deriveCoeffs(coefficients,axis),x,T);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction
long double BasePolynomial::integrateIn2Steps(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running   integrateIn2Steps(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result =  polyval(integrateCoeffs(coefficients),T);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in terms of x(axis=true) or T(axis=false).
long double BasePolynomial::integrateIn2Steps(std::vector< std::vector<long double> > const& coefficients, long double x, long double T, bool axis){
	if (this->DEBUG) {
		std::cout << "Running   integrateIn2Steps(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = polyval(integrateCoeffs(coefficients,axis),x,T);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction of a polynomial divided by its independent variable
long double BasePolynomial::fracIntIn2Steps(std::vector<long double> const& coefficients, long double T){
	if (this->DEBUG) {
		std::cout << "Running    fracIntIn2Steps(std::vector, " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	long double result = coefficients[0] * log(T);
	if (coefficients.size() > 1) {
		std::vector<long double> newCoeffs(coefficients.begin() + 1, coefficients.end());
		result += polyint(newCoeffs,T);
	}
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction of a polynomial divided by its 2nd independent variable
long double BasePolynomial::fracIntIn2Steps(std::vector<std::vector<long double> > const& coefficients, long double x, long double T){
	if (this->DEBUG) {
		std::cout << "Running    fracIntIn2Steps(std::vector, " << x << ", " << T << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	std::vector<long double> newCoeffs;
	for (unsigned int i=0; i<coefficients.size(); i++){
		newCoeffs.push_back(polyfracint(coefficients[i],T));
	}
	long double result = polyval(newCoeffs,x);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}

///Indefinite integral in T-direction of a centred polynomial divided by its 2nd independent variable
long double BasePolynomial::fracIntCentral2Steps(std::vector<std::vector<long double> > const& coefficients, long double x, long double T, long double Tbase){
	if (this->DEBUG) {
		std::cout << "Running    fracIntCentral2Steps(std::vector, " << x << ", " << T << ", " << Tbase << "): ";
	}
	bool db = this->DEBUG;
	this->DEBUG = false;
	std::vector<long double> newCoeffs;
	for (unsigned int i=0; i<coefficients.size(); i++){
		newCoeffs.push_back(fracIntCentral(coefficients[i], T, Tbase));
	}
	long double result = polyval(newCoeffs,x);
	this->DEBUG = db;
	if (this->DEBUG) {
		std::cout << result << std::endl;
	}
	return result;
}


/** Here we define the functions that should be used by the
 *  respective implementations. Please do no use any other
 *  method since this would break the purpose of this interface.
 */

/// Evaluates an exponential function for the given coefficients
/// @param coefficients vector containing the ordered coefficients
/// @param T long double value that represents the current input
/// @param n int value that determines the kind of exponential function
long double BasePolynomial::expval(std::vector<long double> const& coefficients, long double T, int n){
	long double result = 0.;
	if (n==1) {
		checkCoefficients(coefficients,3);
		result = exp(coefficients[0]/(T+coefficients[1]) - coefficients[2]);
	} else if (n==2) {
		result = exp(polyval(coefficients, T));
	} else {
		throw ValueError(format("There is no function defined for this input (%d). ",n));
	}
	return result;
}

/// Evaluates an exponential function for the given coefficients
/// @param coefficients vector containing the ordered coefficients
/// @param x long double value that represents the current input in the 1st dimension
/// @param T long double value that represents the current input in the 2nd dimension
/// @param n int value that determines the kind of exponential function
long double BasePolynomial::expval(std::vector< std::vector<long double> > const& coefficients, long double x, long double T, int n){
	long double result = 0.;
	if (n==2) {
		result = exp(polyval(coefficients, x, T));
	} else {
		throw ValueError(format("There is no function defined for this input (%d). ",n));
	}
	return result;
}












PolynomialImpl1D::PolynomialImpl1D(const std::vector<long double> &coefficients){
	this->coefficients=coefficients;
}

long double PolynomialImpl1D::eval(long double x){
	return this->polyval(this->coefficients, x);
}

long double PolynomialImpl1D::integ(long double x){
	return this->polyint(this->coefficients, x);
}

long double PolynomialImpl1D::deriv(long double x){
	return this->polyder(this->coefficients, x);
}

long double PolynomialImpl1D::solve(long double y, long double x0){

	class Residual : public FuncWrapper1D {
	public:
		PolynomialImpl1D *poly;
		long double x, y;

		Residual(PolynomialImpl1D *poly, long double y){
			this->poly=poly;
			this->y=y;
		}

		double call(double x){
			this->x = x;
			return poly->eval(x) - y;
		};

		double deriv(double x){
			this->x = x;
			return poly->deriv(x);
		};
	};
	Residual resid(this, y);
	std::string errstring;
	return Newton(resid, x0, DBL_EPSILON*1e3, 100, errstring);

	//return Brent(resid,Tmin,Tmax,DBL_EPSILON,1e-12,100,errstring);
}


//
//class PolynomialImpl2D : public BasePolynomial{
//protected:
//	std::vector< std::vector<long double> > coefficients;
//public:
//	PolynomialImpl2D();
//	PolynomialImpl2D(const std::vector< std::vector<long double> > &coefficients);
//	virtual ~PolynomialImpl2D(){};
//	long double eval(long double x, long double z);
//	long double solve(long double y, long double z);
//};
//
//class PolynomialInt1D : public BasePolynomial{
//protected:
//	std::vector<long double> coefficients;
//public:
//	PolynomialInt1D();
//	PolynomialInt1D(const std::vector<long double> &coefficients);
//	virtual ~PolynomialImpl1D(){};
//	long double eval(long double x);
//	//long double integ(long double x);
//	//long double deriv(long double x);
//	long double solve(long double y);
//	//long double solveInt(long double y);
//};
//
//class PolynomialInt2D : public BasePolynomial{
//protected:
//	std::vector< std::vector<long double> > coefficients;
//public:
//	PolynomialInt2D();
//	PolynomialInt2D(const std::vector< std::vector<long double> > &coefficients);
//	virtual ~PolynomialImpl2D(){};
//	long double eval(long double x, long double z);
//	long double solve(long double y, long double z);
//};
//
//class PolynomialFracInt1D : public BasePolynomial{
//protected:
//	std::vector<long double> coefficients;
//public:
//	PolynomialFracInt1D();
//	PolynomialFracInt1D(const std::vector<long double> &coefficients);
//	virtual ~PolynomialFracInt1D(){};
//	long double eval(long double x);
//	long double solve(long double y);
//};
//
//class PolynomialFracInt2D : public BasePolynomial{
//protected:
//	std::vector< std::vector<long double> > coefficients;
//public:
//	PolynomialFracInt2D();
//	PolynomialFracInt2D(const std::vector< std::vector<long double> > &coefficients);
//	virtual ~PolynomialFracInt2D(){};
//	long double eval(long double x, long double z);
//	long double solve(long double y, long double z);
//};
//




















//
///// The classes for Polynomials
//class PolynomialImpl : public BasePolynomial{
//protected:
//	std::vector<long double> coefficients1D;
//	std::vector< std::vector<long double> > coefficients2D;
//	int dim; ///< Is it a 1D (true) or 2D (false) polynomial
//
//public:
//	PolynomialImpl();
//	PolynomialImpl(const std::vector<long double> &coefficients);
//	PolynomialImpl(const std::vector< std::vector<long double> > &coefficients);
//	virtual ~PolynomialImpl(){};
//	long double eval(long double x);
//	long double integ(long double x);
//	long double deriv(long double x);
//	long double solve(long double y);
//	long double solveInt(long double y);
//};
//
//PolynomialImpl::PolynomialImpl() {
//	this->dim = 0;
//}
//PolynomialImpl::PolynomialImpl(const std::vector<long double> &coefficients){
//	this->dim = 1;
//	this->coefficients1D = coefficients;
//}
//PolynomialImpl::PolynomialImpl(const std::vector< std::vector<long double> > &coefficients){
//	this->dim = 2;
//	this->coefficients2D = coefficients;
//}
//long double PolynomialImpl::eval(long double x){
//	if (dim == 1) {
//		return baseHorner(coefficients1D,x);
//	} else if (dim == 2) {
//		return baseHorner(coefficients2D,x);
//	}
//}
//long double PolynomialImpl::integ(long double x);
//long double PolynomialImpl::deriv(long double x);
//long double PolynomialImpl::solve(long double y);
//long double PolynomialImpl::solveInt(long double y);
//
//
//

}

//int main() {
//
//	SimpleIncompressible* liquid = new DowthermQClass();
//	long double AT      =  150.0 + 273.15;
//	long double Ap      =  3e5;
//    liquid->testInputs(AT,Ap);
//
//
//	SecCoolSolution* obj = new MethanolSolution();
//    long double x      =   0.25;
//    long double T      =   5.0 + 273.15;
//    long double p      =   3e5;
//
//	obj->testInputs(T+00,p,x);
//	obj->testInputs(T+05,p,x);
//	obj->testInputs(T+10,p,x);
//	obj->testInputs(T+15,p,x);
//
//
//}
