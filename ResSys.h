#pragma once

class ResSys
{
private:
	int val{ 0 };
	int base{ 0 };

public:
	ResSys() {};
	ResSys(int _val, int _base);
	void SetVal(int _val);
	const int& GetVal() const { return val; }

	friend ResSys operator +(const ResSys &left, const ResSys &right);
	friend ResSys operator -(const ResSys& left, const ResSys& right);
	friend ResSys operator *(const ResSys& left, const ResSys& right);
	friend ResSys operator /(const ResSys& numerator, const ResSys& denominator);
	friend bool operator !=(const ResSys& left, const ResSys& right);
	friend bool operator ==(const ResSys& left, const ResSys& right);
	friend bool operator >(const ResSys& left, const ResSys& right);
	friend bool operator >=(const ResSys& left, const ResSys& right);
	friend bool operator <(const ResSys& left, const ResSys& right);
	friend bool operator <=(const ResSys& left, const ResSys& right);

	ResSys& operator = (const int& right);
	bool operator ==(const int& right);
	bool operator !=(const int& right);
	bool operator >(const int& right);
	bool operator >=(const int& right);
	bool operator <(const int& right);
	bool operator <=(const int& right);

	ResSys& operator ++();
	ResSys& operator --();
	ResSys operator ++(int);
	ResSys operator --(int);
	ResSys& operator +=(const ResSys& right);
	ResSys& operator -=(const ResSys& right);
	ResSys& operator +=(const int& right);
	ResSys& operator -=(const int& right);

	ResSys operator-()const;

	std::ostream& operator<<(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, const ResSys& objectobject);
};
