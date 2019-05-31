#pragma once

#include<iostream>
#include<vector>
#include<tuple>
#include"Menu.h"
#include"listener.h"
#include"Contact.h"
#include<map>
#include<algorithm>
#include<fstream>
#include"ContactGroup.h"
#include"Log.h"
//#include"AppBase.h"

using namespace std;


//@attach("android.Context")
class Context
{
public:
	Context()
	{
		init();
	}

	Menu& getMenu(string key) {
		return menus[key];
	}
	Menu& getCurrentMenu()
	{
		return menus[page];
	}

	void setOnPageChangedListener(IOnPageChangedListener* listener)
	{
		pageChangedListener = listener;
	}

	string getPage()
	{
		return page;
	}
	void setPage(string page)
	{
		this->page = page;
		if (pageChangedListener != NULL)
		{
			pageChangedListener->onPageChanged(page);
		}
	}

	
	string subpage;
	//��ϵ�˵Ĵ洢
	ContactGroup group;
private:
	inline void init()
	{
		page = "home";
		menus["home"] = { "�½�/���ļ�","�˳�����" };
		menus["file"] = { "�½�/����ϵ��","�г���ϵ���嵥","����(����)","����(�绰)","����(סַ)","����(����)","��ʾ��ǰ������Ϣ","����","�ص���һ���˵�" };
		menus["contact"] = { "��ʾ��ϸ����","�޸�����","�޸��Ա�","�޸ĵ绰","�޸ĵ�ַ","�޸���������","�޸�����","�޸�QQ��Ϣ","�ƶ�����","ɾ����ϵ��","�ص���һ���˵�" };
		subpage = "";
	}
	map<string, Menu> menus;
	string page;
	IOnPageChangedListener* pageChangedListener = NULL;
	

	//���str2�Ƿ���str1���Ӵ���һ����򵥵�ģ�����ҷ���
	bool hasSubString(string str1,string str2)
	{
		if (str1.find(str2)!= string::npos)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};
