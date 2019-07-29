/****************************************************************
*                              String
* 						=====================
* File Name: string.hpp
* Related files: string.cpp string_test.cpp
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Ayala Rosel    
* Last update: 23/07/19
****************************************************************/
#ifndef ILHRD_STRING_HPP
#define ILHRD_STRING_HPP

#include <iosfwd> //ostream forward declarations

namespace hrd9
{

class String;
//non member functions:
const String operator+(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);

class String
{

public:
	// explicitly non explicit constructor
	String(const char* str = "");
	String(const String& other);
	String& operator=(const String& other);
	~String();

	String& operator+=(const String& other);
	size_t length() const;

	const char& operator[](size_t index) const; //read string[]
	char& operator[](size_t index);             //string[i] assignment

	const char* to_c_str() const;

private:
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& os, const String& str);
	friend std::istream& operator>>(std::istream& is, String& str);

	char* init_new_str(const char *str);

	char* m_str;
};
} //namespace hrd9




#endif /* ILHRD_STRING_HPP */