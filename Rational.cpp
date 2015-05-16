#include <cmath>

#include "Rational.h"

Rational::Rational(const int_t num, const int_t denum) :
	mNum(num),
	mDen(denum)
{
	normalize();
}

Rational Rational::operator-() const
{
	return Rational(-mNum, mDen);
}

Rational Rational::operator + (const Rational& other) const
{
	return Rational(mNum * other.mDen + other.mNum*mDen, 
		mDen * other.mDen);
}

Rational Rational::operator-(const Rational& other) const
{
	return *this + (-other);
}

Rational Rational::operator*(const Rational& other) const
{
	return Rational(mNum * other.mNum, mDen*other.mDen);
}

Rational Rational::operator/(const Rational& other) const
{
	return *this * Rational(other.mDen, other.mNum);
}

bool Rational::isValid() const
{
	return mDen != 0;
}

std::pair<Rational::int_t, Rational>Rational::split() const
{
	if (!isValid())
	{
		return std::pair<int_t, Rational>(0, *this);
	}
	
	auto whole = mNum / mDen;
	
	auto temp = *this - Rational(whole, 1);
	if (whole < 0)
	{
		temp.mNum *= -1;
	}
	return std::pair<int_t, Rational>(whole, temp);
}

void Rational::normalize()
{
	if (!isValid())
	{
		// this is an invalid ratio anyway
		return;
	}

	if (mNum == 0)
	{
		// nothing to do
		return;
	}

	if (mDen < 0)
	{
		// The denominator will be always non-negative
		mNum *= -1;
		mDen *= -1;
	}

	auto gcd_ = gcd(std::abs(mNum), std::abs(mDen));
	if (gcd_ > 1)
	{
		mNum /= gcd_;
		mDen /= gcd_;
	}
}

Rational::int_t Rational::gcd(int_t a, int_t b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return gcd(b, a % b);
	}
}

std::ostream& operator<<(std::ostream& out, const Rational& r)
{
	if (!r.isValid())
	{
		out << "Inf";
	}
	else
	{
		const auto isNegative = r.mNum < 0;
		if (isNegative)
		{
			out << "(";
		}

		const auto s = r.split();
		if (s.first != 0)
		{
			out << s.first << " ";
		}
		if (s.second.mNum != 0 || s.first == 0)
		{
			out << s.second.mNum << '/' << s.second.mDen;
		}

		if (isNegative)
		{
			out << ")";
		}
	}

	return out;
}