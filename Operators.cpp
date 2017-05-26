#include <iostream>
using namespace std;
class Fraction
{
	long long numerator;
	long long denominator;
	bool flag;//1 == +,0 == -
public:

	Fraction(long long numer = 0, long long deno = 1,bool fl = 1) : numerator(numer), denominator(deno), flag(fl) {}
	void setFraction() { cin >> flag; cin >> numerator; cin >> denominator; }
	// No side effects: const member function:
	const Fraction& operator+() const
	{
		cout << "+Fraction\n";
		return *this;
	}

	const Fraction operator-() const
	{
		cout << "-Fraction\n";
		return Fraction(numerator, denominator, !flag);
	}
	
	Fraction* operator&()
	{
		cout << "&Fraction\n";
		return this;
	}
	// Side effects: non-const member function:
	Fraction reduction()
	{
		long long min;
		if (numerator >= denominator)
			min = denominator;
		else
			min = numerator;
		while (true)
		{
			if (denominator % min == 0 && numerator % min == 0)// find the gcd
			{
				denominator /= min;
				numerator /= min;
				break;
			}
			min--;
		}
	}

	const Fraction operator+(const Fraction& right) const//a/b + c/d
	{
		if(flag == right.flag)// a/b > 0; c/d > 0////////// a/b < 0; c/d < 0
			return Fraction(numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, flag);
		else if (flag == 1 && right.flag == 0)// a/b > 0; c/d < 0
		{
			if((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, denominator * right.denominator, 1);
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, 1, 1);
			else// result < 0
				return Fraction(- numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, 0);
		}
		else if (flag == 0 && right.flag == 1)// a/b < 0; c/d > 0
		{
			if ((- numerator * right.denominator + denominator * right.numerator) > 0)// result > 0
				return Fraction(- numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, 1);
			else if ((- numerator * right.denominator + denominator * right.numerator) == 0)//result == 0
				return Fraction(- numerator * right.denominator + denominator * right.numerator, 1, 1);
			else// result < 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, denominator * right.denominator, 0);
		}
	}
	const Fraction operator-(const Fraction& right) const
	{
		if ((flag == 1 && right.flag == 0) || (flag == 0 && right.flag == 1))// a/b > 0; c/d > 0////////// a/b < 0; c/d < 0
			return Fraction(numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, flag);
		else if (flag == 1 && right.flag == 1)// a/b > 0; c/d > 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, denominator * right.denominator, 1);
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, 1, 1);
			else// result < 0
				return Fraction(-numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, 0);
		}
		else if (flag == 0 && right.flag == 0)// a/b < 0; c/d < 0
		{
			if ((-numerator * right.denominator + denominator * right.numerator) > 0)// result > 0
				return Fraction(-numerator * right.denominator + denominator * right.numerator, denominator * right.denominator, 1);
			else if ((-numerator * right.denominator + denominator * right.numerator) == 0)//result == 0
				return Fraction(-numerator * right.denominator + denominator * right.numerator, 1, 1);
			else// result < 0
				return Fraction(numerator * right.denominator - denominator * right.numerator, denominator * right.denominator, 0);
		}
	}
	const Fraction operator*(const Fraction& right) const
	{
		bool f = 0;
		if ((flag == 1 && right.flag == 1) || (flag == 0 && right.flag == 0))
			f = 1;
		else if ((flag == 0 && right.flag == 1) || (flag == 1 && right.flag == 0))
			f = 0;
		return Fraction(numerator * right.numerator, denominator * right.denominator, f);
	}
	const Fraction operator/(const Fraction& right) const 
	{
		if (right.numerator == 0)
		{
			cout << "Error! the right number can not be 0!" << endl;
			return Fraction(1, 0, 1);
		}
		bool f = 0;
		if ((flag == 1 && right.flag == 1) || (flag == 0 && right.flag == 0))
			f = 1;
		else if ((flag == 0 && right.flag == 1) || (flag == 1 && right.flag == 0))
			f = 0;
		return Fraction(numerator * right.denominator, denominator * right.numerator, f);
	}

	// Assignments modify & return lvalue.
	// operator= can only be a member function:
	Fraction& operator=(const Fraction& right) 
	{
		// Handle self-assignment:
		if (this == &right) return *this;
		flag = right.flag;
		numerator = right.numerator;
		denominator = right.denominator;
		return *this;
	}
	// Conditional operators return true/false:
	bool operator==(const Fraction& right) const 
	{
		return (flag == right.flag) && (numerator == right.numerator) && (denominator == right.denominator);
	}
	bool operator!=(const Fraction& right) const
	{
		return (flag != right.flag) || (numerator != right.numerator) || (denominator != right.denominator);
	}
	bool operator<(const Fraction& right) const
	{
		if (flag == 1 && right.flag == 0)// a/b > 0; c/d < 0
			return 0;
		else if (flag == right.flag && flag == 1)// a/b > 0; c/d > 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 0;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 0;
			else// result < 0
				return 1;
		}
		else if (flag == right.flag && flag == 0)// a/b < 0; c/d < 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 1;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 0;
			else// result < 0
				return 0;
		}
		else// if (flag == 0 && right.flag == 1)// a/b < 0; c/d > 0
		{
			return 1;
		}
	}
	bool operator>(const Fraction& right) const
	{
		if (flag == 1 && right.flag == 0)// a/b > 0; c/d < 0
			return 1;
		else if (flag == right.flag && flag == 1)// a/b > 0; c/d > 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 1;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 0;
			else// result < 0
				return 0;
		}
		else if (flag == right.flag && flag == 0)// a/b < 0; c/d < 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 0;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 0;
			else// result < 0
				return 1;
		}
		else// if (flag == 0 && right.flag == 1)// a/b < 0; c/d > 0
		{
			return 0;
		}
	}
	bool operator<=(const Fraction& right) const
	{
		if (flag == 1 && right.flag == 0)// a/b > 0; c/d < 0
			return 0;
		else if (flag == right.flag && flag == 1)// a/b > 0; c/d > 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 1;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 1;
			else// result < 0
				return 0;
		}
		else if (flag == right.flag && flag == 0)// a/b < 0; c/d < 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 0;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 1;
			else// result < 0
				return 1;
		}
		else// if (flag == 0 && right.flag == 1)// a/b < 0; c/d > 0
		{
			return 1;
		}
	}
	bool operator>=(const Fraction& right) const
	{
		if (flag == 1 && right.flag == 0)// a/b > 0; c/d < 0
			return 0;
		else if (flag == right.flag && flag == 1)// a/b > 0; c/d > 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 1;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 1;
			else// result < 0
				return 0;
		}
		else if (flag == right.flag && flag == 0)// a/b < 0; c/d < 0
		{
			if ((numerator * right.denominator - denominator * right.numerator) > 0)// result > 0
				return 0;
			else if ((numerator * right.denominator - denominator * right.numerator) == 0)//result == 0
				return 1;
			else// result < 0
				return 1;
		}
		else// if (flag == 0 && right.flag == 1)// a/b < 0; c/d > 0
		{
			return 1;
		}
	}
};
int main()
{
	cout << "Please enter A" << endl;
	Fraction A;
	A.setFraction();
	cout << "Please enter B" << endl;
	Fraction B;
	B.setFraction();
	Fraction C;
	C = A + B;
	C = A - B;
	C = A * B;
	C = A / B;
	C = 0;
	C = 1;
	bool test = 0;

	test = A < B;
	test = A > B;
	return 0;
}