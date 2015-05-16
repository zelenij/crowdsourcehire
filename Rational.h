#ifndef __H_RATIONAL_HEADER__
#define __H_RATIONAL_HEADER__

#pragma once

#include <iostream>
#include <algorithm>

class Rational
{
public:
	typedef long int int_t;
	Rational(const int_t num, const int_t denum);

	Rational operator-() const;

	Rational operator+(const Rational& other) const;

	Rational operator-(const Rational& other) const;

	Rational operator/(const Rational& other) const;

	Rational operator*(const Rational& other) const;

	// split into a whole integer and the remainder
	std::pair<int_t, Rational>split() const;

	bool isValid() const;

	friend std::ostream& operator<<(std::ostream& out, const Rational& r);
private:
	int_t mNum;
	int_t mDen;

	void normalize();

	static int_t gcd(int_t a, int_t b);
};

std::ostream& operator<<(std::ostream& out, const Rational& r);

#endif /* __H_RATIONAL_HEADER__ */