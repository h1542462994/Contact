#include "Tool.h"


//���str2�Ƿ���str1���Ӵ���һ����򵥵�ģ�����ҷ���
bool hasSubString(string str1, string str2)
{
	if (str1.find(str2) != string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//���ڼ���ļ����Ƿ�Ϸ���
int checkFileName(string fileName)
{
	if (fileName == "")
	{
		return 1;
	}
	else if (fileName.size() > 40)
	{
		return 2;
	}
	else
	{
		string except = "/\\:*\"<>|?";
		for (int i = 0; i < except.length(); i++)
		{
			if (fileName.find(except[i]) != string::npos)
			{
				return 3;
			}
		}
	}
	return 0;
}
