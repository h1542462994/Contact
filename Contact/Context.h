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
	//联系人的存储
	ContactGroup group;
private:
	inline void init()
	{
		page = "home";
		menus["home"] = { "新建/打开文件","退出程序" };
		menus["file"] = { "新建/打开联系人","列出联系人清单","查找(姓名)","查找(电话)","查找(住址)","查找(分组)","显示当前分组信息","排序","回到上一级菜单" };
		menus["contact"] = { "显示详细内容","修改姓名","修改性别","修改电话","修改地址","修改邮政编码","修改邮箱","修改QQ信息","移动分组","删除联系人","回到上一级菜单" };
		subpage = "";
	}
	map<string, Menu> menus;
	string page;
	IOnPageChangedListener* pageChangedListener = NULL;
	
};
