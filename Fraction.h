#include "defines.h"

using namespace std;

struct Fraction
{
	// Variables
	int numerator, denominator;
	int number;

	// Basic functions
	void printFraction();
	void printMixedNumber();
	void printOperation(Fraction *f1, int op, Fraction *f2);
	void printResult();
	void printMix();
	void printReduction();
	int euclid(int n, int m);
	void checkSign();
	void setValues(int _num, int _den);

	// Operations
	Fraction add(Fraction *f2);
	Fraction xadd(Fraction *f2);
	Fraction sub(Fraction *f2);
	Fraction mul(Fraction *f2);
	Fraction div(Fraction *f2);
	Fraction xdiv(Fraction *f2);
	void rec();
	void red();
	void d2f(float decimal);
	void mix();
	Fraction unm();
	Fraction amix(Fraction *f2);
	bool less(Fraction *f2);

	// Constructors
	Fraction() {
		number = 0;
		numerator = 0;
		denominator = 1;
	}
	Fraction(int num, int den) {
		number = 0;
		numerator = num;
		if (den == 0) denominator = 1;
		else if (den < 0) {
			denominator = 0-den;
			numerator = 0-num;
		}
		else denominator = den;
		red();
	}
	// Mixed number
	Fraction(int nbr, int num, int den) {
		number = nbr;
		numerator = num;
		if (den == 0) denominator = 1;
		else if (den < 0) {
			denominator = 0-den;
			numerator = 0-num;
		}
		else denominator = den;
		red();
	}
};

