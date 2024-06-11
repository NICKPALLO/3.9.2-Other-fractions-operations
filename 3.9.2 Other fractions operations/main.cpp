#include <iostream>
#include <Windows.h>

class Fraction
{
private:
	int numerator_;
	int denominator_;

public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	friend void common_denominator(Fraction& left, Fraction& right);
	friend bool operator== (Fraction left, Fraction right);
	friend bool operator!= (Fraction left, Fraction right);
	friend bool operator< (Fraction left, Fraction right);
	friend bool operator> (Fraction left, Fraction right);
	friend bool operator<= (Fraction left, Fraction right);
	friend bool operator>= (Fraction left, Fraction right);

	friend std::ostream& operator<< (std::ostream& left, Fraction right);

	friend Fraction operator+ (Fraction left, Fraction right);
	friend Fraction operator- (Fraction left, Fraction right);
	friend Fraction operator* (Fraction left, Fraction right);
	friend Fraction operator/ (Fraction left, Fraction right);

	friend void reduction(Fraction& fraction);

	Fraction operator++ ()
	{
		this->numerator_ += this->denominator_;
		reduction(*this);
		return *this;
	}
	Fraction operator++ (int)
	{
		Fraction temp = *this;
		this->numerator_ += this->denominator_;
		reduction(*this);
		return temp;
	}
	Fraction operator-- ()
	{
		this->numerator_ -= this->denominator_;
		reduction(*this);
		return *this;
	}
	Fraction operator-- (int)
	{
		Fraction temp = *this;
		this->numerator_ -= this->denominator_;
		reduction(*this);
		return temp;
	}
};


void common_denominator(Fraction& left, Fraction& right)
{
	Fraction nLeft = left;
	left.numerator_ *= right.denominator_;
	left.denominator_ *= right.denominator_;
	right.numerator_ *= nLeft.denominator_;
	right.denominator_ *= nLeft.denominator_;
}

bool operator== (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ == right.numerator_)
	{
		return true;
	}
	else return false;
}

bool operator!= (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ != right.numerator_)
	{
		return true;
	}
	else return false;
}

bool operator< (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ < right.numerator_)
	{
		return true;
	}
	else return false;
}

bool operator> (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ > right.numerator_)
	{
		return true;
	}
	else return false;
}

bool operator<= (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ <= right.numerator_)
	{
		return true;
	}
	else return false;
}

bool operator>= (Fraction left, Fraction right)
{
	common_denominator(left, right);
	if (left.numerator_ >= right.numerator_)
	{
		return true;
	}
	else return false;
}


std::ostream& operator<< (std::ostream& left, Fraction right)
{
	left << right.numerator_ << "/" << right.denominator_;
	return left;
}

void reduction(Fraction& fraction)
{
	for (int i = min(abs(fraction.numerator_), abs(fraction.denominator_));i >1;i--)
	{
		if ((fraction.numerator_ % i == 0) && (fraction.denominator_ % i == 0))
		{
			fraction.numerator_ /= i;
			fraction.denominator_ /= i;
			i = min(abs(fraction.numerator_), abs(fraction.denominator_));
		}
	}
}

Fraction operator+ (Fraction left, Fraction right)
{
	common_denominator(left, right);
	left.numerator_ += right.numerator_;
	reduction(left);
	return left;
}

Fraction operator- (Fraction left, Fraction right)
{
	common_denominator(left, right);
	left.numerator_ -= right.numerator_;
	reduction(left);
	return left;
}

Fraction operator* (Fraction left, Fraction right)
{
	left.numerator_ *= right.numerator_;
	left.denominator_ *= right.denominator_;
	reduction(left);
	return left;
}

Fraction operator/ (Fraction left, Fraction right)
{
	left.numerator_ *= right.denominator_;
	left.denominator_ *= right.numerator_;
	reduction(left);
	return left;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int numerator1, denominator1, numerator2, denominator2;
	std::cout << "¬ведите числитель дроби 1: ";
	std::cin >> numerator1;
	std::cout << "¬ведите знаменатель дроби 1: ";
	std::cin >> denominator1;
	std::cout << "¬ведите числитель дроби 2: ";
	std::cin >> numerator2;
	std::cout << "¬ведите знаменатель дроби 2: ";
	std::cin >> denominator2;

	Fraction f1(numerator1, denominator1);
	Fraction f2(numerator2, denominator2);

	std::cout << f1 << " + " << f2 << " = " << f1 + f2 << std::endl;
	std::cout << f1 << " - " << f2 << " = " << f1 - f2 << std::endl;
	std::cout << f1 << " * " << f2 << " = " << f1 * f2 << std::endl;
	std::cout << f1 << " / " << f2 << " = " << f1 / f2 << std::endl;
	std::cout << "++" << f1 << " * " << f2 << " = ";
	std::cout << ++f1 * f2 << std::endl;
	std::cout << "«начение дроби 1: " << f1 << std::endl;
	std::cout << f1 << "-- * " << f2 << " = ";
	std::cout << f1-- * f2 << std::endl;
	std::cout << "«начение дроби 1: " << f1 << std::endl;
	return 0;
}