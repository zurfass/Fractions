#include "Fraction.h"

// Print proper fraction
void Fraction::printFraction() {
	checkSign();
	cout<<numerator<<"/"<<denominator;
}

// Print mixed number if fraction >1 or <-1
void Fraction::printMixedNumber() {
	if (number == 0) printFraction();
	else {
		cout<<number<<" ";
		printFraction();
	}
}

// Print operation
void Fraction::printOperation(Fraction *f1, int op, Fraction *f2) {
	cout<<"\n";
	f1->printMixedNumber();
	if (op == ADD) cout<<" + ";
	else if (op == SUB) cout<<" - ";
	else if (op == MUL) cout<<" * ";
	else if (op == DIV) cout<<" / ";
	else if (op == LESS) cout<<" < ";
	f2->printMixedNumber();
}

// Print result
void Fraction::printResult() {
	cout<<" = ";
	printMixedNumber();
}

// Print conversion from fraction to mixed number
void Fraction::printMix() {
	cout<<"\n Converting ";
	printMixedNumber();
	cout<<" to mixed number ";
}

// Print reduction
void Fraction::printReduction() {
	cout<<"\n Reducing ";
	printFraction();
}

// Euclid's algorithm to find GCD
int Fraction::euclid(int n, int m) {
	int r = n % m;
	if (r == 0) return m;
	else return euclid(m,r);
}

// If fraction is negative, numerator is negative and denominator positive
void Fraction::checkSign() {
	if (denominator < 0) {
		denominator = 0-denominator;
		numerator = 0-numerator;
	}
}

// Reset numerator and denominator, and reduce to GCD
void Fraction::setValues(int _num, int _den) {
	numerator = _num;
	if (_den == 0) _den = 1;
	else denominator = _den;
	red();
}

// Find the sum of F1 and F2 and report the result as a fraction
Fraction Fraction::add(Fraction *f2) {
	printOperation(this,ADD,f2);
	int num, den;
	den = denominator * f2->denominator;
	num = numerator * f2->denominator;
	num += f2->numerator * denominator;
	Fraction result(num, den);
	result.red();
	result.printResult();
	return result;
}

// Find the sum of F1 and F2 and report the result as a mixed number if the
// result is an improper fraction
Fraction Fraction::xadd(Fraction *f2) {
	Fraction result = add(f2);
	result.mix();
	result.printResult();
	return result;
}

// Subtract F2 from F1
Fraction Fraction::sub(Fraction *f2) {
	printOperation(this,SUB,f2);
	int num, den;
	den = denominator * f2->denominator;
	num = numerator * f2->denominator;
	num -= f2->numerator * denominator;
	Fraction result(num, den);
	result.printResult();
	return result;
}

// Find the product of the two fractions and report the result as a fraction
Fraction Fraction::mul(Fraction *f2) {
	printOperation(this,MUL,f2);
	int num, den;
	num = numerator * f2->numerator;
	den = denominator * f2->denominator;
	Fraction result(num, den);
	result.printResult();
	return result;
}

// Divide F1 by F2 and report the result as a fraction
Fraction Fraction::div(Fraction *f2) {
	printOperation(this,DIV,f2);
	int num, den;
	num = numerator * f2->denominator;
	den = denominator * f2->numerator;
	if ((f2->number == 0) && (f2->numerator == 0)) {
		cout<<"\n Error: Illegal input, attempted division by 0";
		return Fraction(numerator,denominator);
	}
	Fraction result(num, den);
	result.printResult();
	return result;
}

// Divide F1 by F2 and report the result as mixed number if improper fraction
Fraction Fraction::xdiv(Fraction *f2) {
	Fraction result = div(f2);
	result.mix();
	result.printResult();
	return result;
}

// Find the reciprocal of F (ie invert F)
void Fraction::rec() {
	cout<<"\n Reciprocal of ";
	printFraction();
	int temp = denominator;
	denominator = numerator;
	numerator = temp;
	printResult();
}

// Reduce fraction to lowest terms
void Fraction::red() {
	int reduction = euclid(numerator,denominator);
	numerator /= reduction;
	denominator /= reduction;
}

// Convert the decimal to a fraction
void Fraction::d2f(float r) {
	cout<<"\n Converting "<<r<<" to fraction ";
	int num, den;
	numerator = int(r*1000);
	denominator = 1000;
	red();
	printResult();
}

// Change an improper fraction to a mixed number
void Fraction::mix() {
	number = numerator/denominator;
	numerator = numerator % denominator;
}

// Change a mixed number to a fraction - N is the integer part and F is the
// Fractional part of the mixed number
Fraction Fraction::unm() {
	cout<<"\n Converting ";
	printMixedNumber();
	cout<<" to improper fraction ";
	numerator += number*denominator;
	number = 0;
	Fraction result(numerator,denominator);
	printFraction();
	return result;
}

// Add two mixed numbers and report the answer as a mixed number
Fraction Fraction::amix(Fraction *f2) {
	Fraction result = xadd(f2);
	result.number += number + f2->number;
	result.printResult();
	return result;
}

// Determine which fraction is smaller
bool Fraction::less(Fraction *f2) {
	printOperation(this,LESS,f2);
	int num1, num2;
	num1 = numerator * f2->denominator;
	num2 = f2->numerator * denominator;
	if (num1 < num2) {
		cout<<" = TRUE";
		return true;
	}
	else {
		cout<<" = FALSE";
		return false;
	}
}

