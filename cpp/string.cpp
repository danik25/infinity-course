/****************************************************************
*                              String
* 						=====================
* File Name: string.cpp
* Related files: string.hpp string_test.cpp
* #Version: V 1.0
* Writer: Dani Benjamin      
* Reviewer: Ayala Rosel    
* Last update: 23/07/19
****************************************************************/
#include <cstring> /* strlen */
#include <iostream> /* cout */
#include "string.hpp"

namespace hrd9
{
	/* constructor */
	String::String(const char* str)
	{
		size_t len = strlen(str);
		m_str = new char [len + 1];
		strcpy(m_str, str);
	}

	/* distructor */
	String::~String()
	{
		delete [](m_str);
	}

	/* copy constructor */
	String::String(const String& other) : m_str(init_new_str(other.m_str))
	{
		;
	}

	/* copy assignment operator */
	String& String :: operator=(const String& other)
	{
		delete[] m_str;
		m_str = init_new_str(other.m_str);

		return(*this);
	}

/*===================== non member functions =====================*/

/*===================== member functions =====================*/

	String& String::operator+=(const String& other)
	{
		size_t total_len = strlen(m_str) + strlen(other.m_str);

		String tmp = m_str;
		delete [] m_str;

		m_str = new char [total_len + 1];
		char * runner = m_str;

		strcpy(runner, tmp.m_str);
		strcat(runner, other.m_str);

		return(*this);
	}

	size_t String::length() const
	{
		return(strlen(m_str));
	}

	const char& String::operator[](size_t index) const
	{
		return(m_str[index]);
	}

	char& String::operator[](size_t index)
	{
		return(m_str[index]);
	}

	const char* String::to_c_str() const
	{
		return(m_str);
	}

/*===================== friend functions =====================*/

	const String operator+(const String& lhs, const String& rhs)
	{
		String ans = lhs;
		ans += rhs;

		return(ans);
	}

	bool operator==(const String& lhs, const String& rhs)
	{
		return(!strcmp(lhs.m_str, rhs.m_str));
	}

	bool operator!=(const String& lhs, const String& rhs)
	{
		return(strcmp(lhs.m_str, rhs.m_str));
	}

	bool operator>(const String& lhs, const String& rhs)
	{
		return(strcmp(lhs.m_str, rhs.m_str));
	}

	bool operator<(const String& lhs, const String& rhs)
	{
		return(strcmp(rhs.m_str, lhs.m_str));
	}

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		os << str.m_str;
		return(os);
	}

/*===================== assistance functions =====================*/

	char* String::init_new_str(const char *str)
	{
		size_t len = strlen(str);
		char *new_str = new char [len + 1];
		strcpy(new_str, str);

		return(new_str);
	}
}