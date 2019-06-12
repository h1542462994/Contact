#pragma once
#include<string>
#include"Log.h"
#include"consolecolor.h"

using namespace std;

//检查str2是否是str1的子串，一种最简单的模糊查找方法
bool hasSubString(string str1, string str2);

//用于检查文件名是否合法。
int checkFileName(string fileName);
