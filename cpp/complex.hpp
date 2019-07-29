/****************************************************************
*                              Complex
* 						=====================
* File Name: complex.hpp
* Related files: complex_test.cpp
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Idan Argaman  
* Last update: 23/07/19
****************************************************************/
#ifndef ILHRD_COMPLEX_HPP
#define ILHRD_COMPLEX_HPP


#include <iostream> //ostream

namespace hrd9
{

class Complex;

// + is our friend
const Complex operator+(const Complex& lhs, const Complex& rhs);
const Complex operator-(const Complex& lhs, const Complex& rhs);
const Complex operator*(const Complex& lhs, const Complex& rhs);
const Complex operator/(const Complex& lhs, const Complex& rhs);
std::ostream& operator<<(std::ostream& os, const Complex& complex);
std::istream& operator>>(std::istream& in_s, Complex& complex);
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);


class Complex
{
public: 

	//non explicit Ctor intentionally
	//using generated function for CCtor, copy assignment and Dtor
	Complex(double real = 0, double imaginary = 0);
	
	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);
	
	void set_real(double real);
	void set_img(double imaginary);
	double get_real()const;
	double get_img()const;

private:
	friend const Complex operator+(const Complex& lhs, const Complex& rhs);
	double m_real;
	double m_img;
};

/* constructor */
Complex::Complex(double real, double imaginary) : m_real(real), m_img(imaginary)
{
    ;
}


/*===========================================================================*/
/* operators */

inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex obj(lhs.m_real + rhs.m_real, lhs.m_img + rhs.m_img);

    return(obj);
}

inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex obj;
    obj.set_real(lhs.get_real() - rhs.get_real());
    obj.set_img(lhs.get_img() - rhs.get_img());

    return(obj);
}

inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex obj;
    obj.set_real(lhs.get_real() * rhs.get_real() - lhs.get_img() * rhs.get_img());
    obj.set_img(lhs.get_real() * rhs.get_img() + rhs.get_real() * lhs.get_img());

    return(obj);
}

inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex obj;
    obj.set_real(lhs.get_real() / rhs.get_real());
    obj.set_img(lhs.get_img() / rhs.get_img());

    return(obj);
}

inline std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    return (os << complex.get_real() << ", " << complex.get_img());
}

inline std::istream& operator>>(std::istream& in_s, Complex& complex)
{
    double real = 0;
    double img = 0;
    in_s >> real;
    in_s >> img;

    complex.set_real(real);
    complex.set_img(img);

    return (in_s);
}

inline bool operator==(const Complex& lhs, const Complex& rhs)
{
    return(lhs.get_real() == rhs.get_real() && lhs.get_img() == rhs.get_img());
}

inline bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return(!(lhs == rhs));
}

/*===========================================================================*/

inline double Complex::get_real() const
{
    return(m_real);
}

inline double Complex::get_img() const
{
    return(m_img);
}

inline void Complex::set_real(double real)
{
    m_real = real;
}

inline void Complex::set_img(double imaginary)
{
    m_img = imaginary;
}

/*===========================================================================*/
/* member functions */

inline Complex& Complex::operator+=(const Complex& other)
{
    set_real(get_real() + other.get_real());
    set_img(get_img() + other.get_img());

    return(*this);
}

inline Complex& Complex::operator-=(const Complex& other)
{
    set_real(get_real() - other.get_real());
    set_img(get_img() - other.get_img());

    return(*this);
}

inline Complex& Complex::operator*=(const Complex& other)
{
    set_real(get_real() * other.get_real());
    set_img(get_img() * other.get_img());

    return(*this);
}

inline Complex& Complex::operator/=(const Complex& other)
{
    set_real(get_real() / other.get_real());
    set_img(get_img() / other.get_img());

    return(*this);
}

} //namespace hrd9

#endif /* ILHRD_COMPLEX */