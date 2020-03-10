#pragma once
#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>
///
///
///
class OutOfRange :public std::exception
{
public:
	const char* what()const noexcept
	{
		return "Error! Out Of Range.\n";
	}
};

class BadSize :public std::exception
{
public:
	const char* what()const noexcept
	{
		return "Error! Bad Size.\n";
	}
};

class FailedApplyForSpace :public std::exception
{
public:
	const char* what()const noexcept
	{
		return "Error! Apply For Space Failed.\n";
	}
};

#endif // !_EXCEPTION_H
