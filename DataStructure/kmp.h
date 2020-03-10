#pragma once
#include <cstring>

using Position=int;

void BuildNext(const char* pattern, int* next)
{
	int i = 0;
	int j = -1;
	next[0] = -1;
	int patternLength = strlen(pattern);
	while (i < patternLength - 1)
	{
		if (j == -1 || pattern[i] == pattern[j])
		{
			++i;
			++j;
			//如果循环条件i < patternLength时这步当循环进入i=patternLength-1时
			//由于前面++i,导致i=patternLength
			//match[patternLength]会出现数组越界
			//如果在++后当前i的值不与前缀j处相同则
			//若相等，则证明当前串与前缀串相同，因此可以直接使用前缀串的next的值，而不用重复比较过程
			if (pattern[i] == pattern[j])
				next[i] = next[j];
			else
				next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

Position KMP(const char* str, const char* pattern)//O(n+m+Tm),n=strlen(str),m=strlen(pattern)
{
	try
	{
		int i = 0, j = 0;
		int strLength = strlen(str);//O(n)
		//注意这步是必须的，后面会出现-1<strlen(pattern),而strlen(pattern)返回无符号整型
		//无符号整型与有符号整型比较大小时，有符号整型会强制转换成无符号整型，-1就变成255
		///会出现-1>strlen(pattern)的错误情况
		int patternLength = strlen(pattern);//O(m)
		int* next = new int[patternLength];//当GetMatch中循环条件为i < patternLength必须加1,
		if (!next) throw FailedApplyForSpace();
		BuildNext(pattern, next);
		while (i < strLength && j < patternLength)
		{
			if (j == -1 || str[i] == pattern[j])
			{
				++i;
				++j;
			}
			else {
				j = next[j];
			}
		}
		delete[] next;
		next = nullptr;
		//if (j == patternLength)
		//	return i - j;
		//return -1;
		return (j == patternLength) ? i - j : -1;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

}

///if(pattern[match[i-1]+1]==pattern[i])
///match[i]=match[i-1]+1
void BuildMatch(const char* pattern, int* match)
{
	int i = 0;
	int j = -1;
	match[0] = -1;
	int patternLength = strlen(pattern);//O(m)
	for (int i = 1; i < patternLength; ++i)//O(m)
	{
		j = match[i - 1];
		while (j >= 0 && pattern[j + 1] != pattern[i])//while (match[i - 1] >= 0 && pattern[match[i - 1] + 1] != pattern[i])
			j = match[j];
		if (pattern[j + 1] == pattern[i])
			match[i] = j + 1;
		else match[i] = -1;//j=-1
	}
}

Position Kmp(const char* str, const char* pattern)
{
	try
	{
		int i = 0, j = 0;
		int strLength = strlen(str);
		int patternLength = strlen(pattern);
		int* match = new int[patternLength];
		if (!match) throw FailedApplyForSpace();
		BuildMatch(pattern, match);
		while (i < strLength && j < patternLength)
		{
			if (str[i] == pattern[j])
			{
				++i;
				++j;
			}
			else if (j > 0) {
				j = match[j - 1] + 1;
			}
			else ++i;
		}
		delete[] match;
		match = nullptr;
		return j == patternLength ? i - j : -1;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

}