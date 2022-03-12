#include <iostream>
#include <cassert>
#include "ResSys.h"

ResSys::ResSys(int _val, int _base)
{
	assert(_base > 0 && "The base must be greater than zero.");
	base = _base;

	if (_val >= 0)
		val = _val % base;
	else
		val = base - std::abs(_val) % base;
}

void ResSys::SetVal(int _val)
{
	if (base == 0)
		return;
	if (_val >= 0)
		val = _val % base;
	else
		val = base - std::abs(_val) % base;
}

ResSys& ResSys::operator=(const int& right)
{
	this->SetVal(right);
	return *this;
}

bool ResSys::operator==(const int& right)
{
	return this->val == right;
}

bool ResSys::operator!=(const int& right)
{
	return this->val != right;
}

bool ResSys::operator>(const int& right)
{
	return this->val > right;
}

bool ResSys::operator>=(const int& right)
{
	return this->val >= right;
}

bool ResSys::operator<(const int& right)
{
	return this->val < right;
}

bool ResSys::operator<=(const int& right)
{
	return this->val <= right;
}

ResSys& ResSys::operator++()
{
	this->SetVal(this->val + 1);
	return *this;
}

ResSys& ResSys::operator--()
{
	this->SetVal(this->val - 1);
	return *this;
}

ResSys ResSys::operator++(int)
{
	ResSys temp(this->val + 1, this->base);
	return temp;
}

ResSys ResSys::operator--(int)
{
	ResSys temp(this->val - 1, this->base);
	return temp;
}

ResSys& ResSys::operator+=(const ResSys& right)
{
	assert(this->base == right.base && "Objects of addition must have the same base.");
	this->SetVal(this->val + right.val);
	return *this;
}

ResSys& ResSys::operator-=(const ResSys& right)
{
	assert(this->base == right.base && "Objects of substraction must have the same base.");
	this->SetVal(this->val - right.val);
	return *this;
}

ResSys& ResSys::operator+=(const int& right)
{
	this->SetVal(this->val + right);
	return *this;
}

ResSys& ResSys::operator-=(const int& right)
{
	this->SetVal(this->val - right);
	return *this;
}

ResSys ResSys::operator-() const
{
	return ResSys(base - std::abs(val) % base, base);
}

std::ostream& ResSys::operator<<(std::ostream& out)
{
	out << '<' << this->val << ",[" << this->base << "]>";
	return out;
}

ResSys operator +(const ResSys &left, const ResSys &right)
{
	assert(left.base == right.base && "Objects of addition must have the same base.");
	return ResSys((left.val + right.val)%left.base, left.base);
}

ResSys operator -(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of substraction must have the same base.");
	return ResSys((left.val - right.val) % left.base, left.base);
}

ResSys operator *(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of multipclicaction must have the same base.");
	return ResSys((left.val * right.val) % left.base, left.base);
}

ResSys operator /(const ResSys& numerator, const ResSys& denominator)
{
	assert(denominator.val != 0 && "The denominator must be not equal to zero");

	int num = numerator.val;
	
	while (1)
	{
		if (num % denominator.val == 0)
			return ResSys((num / denominator.val) % denominator.base, denominator.base);

		num += denominator.base;
	}
}

bool operator!=(const ResSys& left, const ResSys& right)
{
	return left.base != right.base && left.val != right.val;
}

bool operator==(const ResSys& left, const ResSys& right)
{
	return left.base == right.base && left.val == right.val;
}

bool operator>(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of comparison must have the same base.");
	return left.val > right.val;
}

bool operator>=(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of comparison must have the same base.");
	return left.val >= right.val;
}

bool operator<(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of comparison must have the same base.");
	return left.val < right.val;
}

bool operator<=(const ResSys& left, const ResSys& right)
{
	assert(left.base == right.base && "Objects of comparison must have the same base.");
	return left.val <= right.val;
}

std::ostream& operator<<(std::ostream& out, const ResSys& object)
{
	//out << '<' << object.val << ",[" << object.base << "]>";
	out << object.val;
	return out;
}
