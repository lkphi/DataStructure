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
			//���ѭ������i < patternLengthʱ�ⲽ��ѭ������i=patternLength-1ʱ
			//����ǰ��++i,����i=patternLength
			//match[patternLength]���������Խ��
			//�����++��ǰi��ֵ����ǰ׺j����ͬ��
			//����ȣ���֤����ǰ����ǰ׺����ͬ����˿���ֱ��ʹ��ǰ׺����next��ֵ���������ظ��ȽϹ���
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
		//ע���ⲽ�Ǳ���ģ���������-1<strlen(pattern),��strlen(pattern)�����޷�������
		//�޷����������з������ͱȽϴ�Сʱ���з������ͻ�ǿ��ת�����޷������ͣ�-1�ͱ��255
		///�����-1>strlen(pattern)�Ĵ������
		int patternLength = strlen(pattern);//O(m)
		int* next = new int[patternLength];//��GetMatch��ѭ������Ϊi < patternLength�����1,
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