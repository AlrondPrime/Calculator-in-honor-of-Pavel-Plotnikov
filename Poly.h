#include <initializer_list>
#include <iostream>
//#include <sstream>
#pragma once

template<typename T>
class Poly
{
private:
	int degree{ 0 };
	T* coefficients{ nullptr };
	inline static bool remainder_flag{ 0 };
	static Poly<T> remainder_;

public:
	Poly();
	Poly(int degree_);
	Poly(const Poly& copy);
	Poly(const std::initializer_list<int>& list);
	Poly(const int& base, const std::initializer_list<int>& list);
	~Poly();
	//void InputFromConsole();
	void print() const;
	template<typename T1> static Poly<T1>& Remainder()
	{
		if (Poly<T1>::remainder_flag == 0)
			Poly<T1>::remainder_ = Poly<T1>();
		return Poly<T1>::remainder_;
	}
	int Degree() { return degree; }

	template<typename T1> friend Poly<T1> operator + (const Poly<T1>& left, const Poly<T1>& right);
	template<typename T1> friend Poly<T1> operator - (const Poly<T1>& left, const Poly<T1>& right);
	template<typename T1> friend Poly<T1> operator * (const Poly<T1>& left, const Poly<T1>& right);
	template<typename T1> friend Poly<T1> operator / (const Poly<T1>& numerator, const Poly<T1>& denominator);

	T& operator[](const int index);
	const T& operator[](const int index) const;
	Poly operator -() const;
	Poly operator = (const Poly& copy);

};

template<typename T> Poly<T> Poly<T>::remainder_;

#pragma region Constructors and destructor
template<typename T>
inline Poly<T>::Poly()
{

}

template<typename T>
inline Poly<T>::Poly(int degree_)
{
	degree = degree_;
	coefficients = new T[degree + 1];
	for (int i{ 0 }; i <= degree; ++i)
		coefficients[i] = 0;
}

template<typename T>
inline Poly<T>::Poly(const Poly& copy)
{
	degree = copy.degree;
	coefficients = new T[degree + 1];

	for (int i{ degree }; i >= 0; --i)
		coefficients[i] = copy.coefficients[i];
}

template<typename T>
Poly<T>::Poly(const std::initializer_list<int>& list)
{
	degree = list.size() - 1;

	coefficients = new T[list.size()];

	int i{ degree };
	for (auto& element : list)
		coefficients[i--] = element;
}

template<typename T>
Poly<T>::Poly(const int& base, const std::initializer_list<int>& list)
{
	degree = list.size() - 1;

	coefficients = new T[list.size()];

	int i{ degree };
	for (auto& element : list)
		coefficients[i--] = ResSys(element, base);
}

template<typename T>
inline Poly<T>::~Poly()
{
	delete[] coefficients;
	coefficients = nullptr;
}
#pragma endregion

#pragma region Operators
template<typename T>
inline T& Poly<T>::operator[](const int index)
{
	return coefficients[index];
}

template<typename T>
inline const T& Poly<T>::operator[](const int index) const
{
	return coefficients[index];
}

template<typename T>
Poly<T> Poly<T>::operator-() const
{
	Poly<T> temp(this->degree);

	for (int i{ degree }; i >= 0; --i)
		temp[i] = -coefficients[i];

	return temp;
}

template<typename T>
Poly<T> Poly<T>::operator = (const Poly<T>& copy)
{
	if (&copy == this)
		return *this;

	degree = copy.degree;

	if (this->coefficients)
		delete[] coefficients;
	coefficients = new T[degree + 1];

	for (int i{ degree }; i >= 0; --i)
		coefficients[i] = copy.coefficients[i];

	return *this;
}

template <typename T1>
Poly<T1> operator+(const Poly<T1>& left, const Poly<T1>& right)
{
	auto greater_poly = (left.degree > right.degree) ? left : right;
	auto lower_poly = (left.degree < right.degree) ? left : right;

	int greater_degree = greater_poly.degree;
	int lower_degree = lower_poly.degree;

	Poly<T1> result(greater_degree);

	for (int i{ greater_degree }; i > lower_degree; --i)
		result[i] = greater_poly[i];

	for (int i{ lower_degree }; i >= 0; --i)
		result[i] = greater_poly[i] + lower_poly[i];


	return result;
}

template <typename T1>
Poly<T1> operator-(const Poly<T1>& left, const Poly<T1>& right)
{
	return left + (-right);
}

template <typename T1>
Poly<T1> operator*(const Poly<T1>& left, const Poly<T1>& right)
{
	Poly<T1> result(left.degree + right.degree);

	for (int i{ left.degree }; i >= 0; --i)
		for (int j{ right.degree }; j >= 0; --j)
			result[i + j] += left[i] * right[j];

	return result;
}

template <typename T1>
Poly<T1> operator /(const Poly<T1>& numerator, const Poly<T1>& denominator)
{
	Poly<T1> temp(numerator);
	Poly<T1> result(numerator.degree - denominator.degree);
	//std::cout << "temp: "; temp.print();
	//Цикл поиска частного
	for (int i{ numerator.degree }; i >= denominator.degree; --i)
	{
		//Нахождение коэффициента текущего слагаемого частного
		result[i - denominator.degree] = temp[i] / denominator[(denominator.degree)];
		//std::cout << "result: "; result.print();
		//std::cout << result[i - denominator.degree] << std::endl;

		//Вычитание из делимого произведения делителя на текущее слагаемое частного
		for (int j{ i - 1 }; j >= 0; --j)
			temp[j] -= denominator[j-result.degree] * result[i - denominator.degree];
		//for (int j{ denominator.degree - 1}; j >= 0; --j) {
		//temp[j+1] -= denominator[j] * result[i - denominator.degree];
		//std::cout << "denominator: ";  denominator.print();
		//std::cout << "temp: "; temp.print();
		//std::cout << temp[j] << std::endl;
	//}
		//std::cout << "temp: "; temp.print();
		temp[i] = 0;
	}
	//std::cout << "temp: "; temp.print();
	//Если в итоге делимое не равно нулю, значит, есть остаток, который сохраняется в чтатическом члене класса
	Poly<T1>::remainder_flag = 0;
	for (int i{ temp.degree }; i >= 0; --i)
		if (temp[0] != 0)
		{
			Poly<T1>::remainder_flag = 1;
			Poly<T1>::remainder_ = temp;
			break;
		}

	return result;


}

#pragma endregion

//template<typename T>
//void Poly<T>::InputFromConsole()
//{
//	std::cout << "Input coefficients as X1 X2 X3 Xn\n";
//
//	std::string temp;
//	getline(std::cin, temp);
//	std::stringstream temp1(temp);
//	int temp2;
//	while (temp1 >> temp2)
//		coefficients.push_back(temp2);
//	degree = coefficients.size() - 1;
//}

template<typename T>
void Poly<T>::print() const
{

	if (coefficients[degree] > 0)
		std::cout << coefficients[degree] << "x^" << degree;
	else if (coefficients[degree] < 0)
		std::cout << "-" << -coefficients[degree] << "x^" << degree;


	for (int i{ degree - 1 }; i > 0; --i)
		if (coefficients[i] > 0)
			std::cout << " + " << coefficients[i] << "x^" << i;
		else if (coefficients[i] < 0)
			std::cout << " - " << -coefficients[i] << "x^" << i;

	if (degree > 0)
	{
		if (coefficients[0] > 0)
			std::cout << " + " << coefficients[0];
		else if (coefficients[0] < 0)
			std::cout << " - " << -coefficients[0];
	}
	std::cout << std::endl;
}
//
//template<typename T1> 
//Poly<T1>& Poly<T1>::Remainder()
//{
//	if (Poly<T1>::remainder_flag == 1)
//		return Poly<T1>::remainder_;
//	else return Poly<T1>();
//}