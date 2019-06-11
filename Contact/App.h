#pragma once

#include"AppBase.h"
#include"Context.h"
#include"Log.h"
#include<sstream>
#include"listener.h"
#include"Contact.h"
#include<iomanip>

using namespace std;

class App :public AppBase
{
public:
	App(Context* context) :AppBase(context) {}

protected:
	virtual void onLoad() override
	{
		Log::i("欢迎来到电话簿系统，请敬请享用吧。");
	}

	virtual string onTip() override
	{
		string tip = "";
		string page = getContext().getPage();
		string subpage = getContext().subpage;

		if (subpage == "")
		{
			cout << getContext().getCurrentMenu();
		}

		if (page == "home")
		{
			if (subpage == "")
			{
				tip = "请选择菜单中的一项";
			}
			else if (subpage == "create")
			{
				tip = "请输入新建/打开的文件名";
			}
		}
		else if (page == "file")
		{
			if (subpage == "")
			{
				getContext().group.saveFile();
				tip = "请选择菜单中的一项";
			}
			else if (subpage == "create")
			{
				tip = "请输入新建/打开联系人的姓名";
			}
			else if (subpage == "search-name")
			{
				tip = "请输入想要查询人的姓名";
			}
			else if (subpage == "search-phone")
			{
				tip = "请输入想要查询人的电话";
			}
			else if (subpage == "search-address")
			{
				tip = "请输入想要查询人的地址";
			}
			else if (subpage == "search-group")
			{
				tip = "请输入想要查询的分组信息";
			}
			else if (subpage == "select")
			{
				tip = "选择第几个呢？你可以输入-1取消该操作";
			}
			else if (subpage == "sort")
			{
				cout << "0:退出排序" << endl
					<< "1:姓名" << endl
					<< "2:电话" << endl
					<< "3:地址" << endl
					<< "4:分组" << endl;
				tip = "请选择排序的键";
			}
		}
		else if (page == "contact")
		{
			if (subpage == "")
			{
				tip = "请选择菜单中的一项";
			}
			else if (subpage == "name")
			{
				tip = "请输入姓名";
			}
			else if (subpage == "sex")
			{
				tip = "请输入性别(M/W)";
			}
			else if (subpage == "phone")
			{
				tip = "请输入电话";
			}
			else if (subpage == "address")
			{
				tip = "请输入地址";
			}
			else if (subpage == "postCode")
			{
				tip = "请输入邮政编码";
			}
			else if (subpage == "email")
			{
				tip = "请输入邮箱";
			}
			else if (subpage == "qq")
			{
				tip = "请输入QQ号";
			}
			else if (subpage == "delete")
			{
				tip = "你确认要删除该联系人吗(Y/N)";
			}
			else if (subpage == "group")
			{
				tip = "请输入分组信息";
			}
		}
		return tip;
	}

	virtual bool onHandleInput(string command) override
	{
		string page = getContext().getPage();
		string& subpage = getContext().subpage;
		istringstream istr(command);

		if (page == "home")
		{
			if (subpage == "")
			{
				int cmd = -1;
				istr >> cmd;
				//新建/打开文件
				if (cmd == 1)
				{
					subpage = "create";
				}
				//退出程序
				else if (cmd == 2)
				{
					return false;
				}
				else
				{
					Log::e("输入错误，请重新输入。");
				}
			}
			else if (subpage == "create")
			{
				int check = checkFileName(command);
				if (check == 1)
				{
					Log::e("文件名不能为空");
				}
				else if (check == 2)
				{
					Log::e("文件名太长，不应该超过40个字符");
				}
				else if (check == 3)
				{
					Log::e("文件名不应该含有[/\\:*\"<>|?]这些非法字符");
				}
				else
				{

					bool r = getContext().group.loadFile(command);
					if (r)
					{
						Log::w("已打开文件" + command);
					}
					else
					{
						Log::w("已创建文件" + command);
					}
					getContext().subpage = "";
					getContext().setPage("file");
				}
			}
		}
		else if (page == "file")
		{
			if (subpage == "")
			{
				int cmd = -1;
				istr >> cmd;

				if (cmd == 1)
				{
					subpage = "create";
				}
				else if (cmd == 2)
				{
					getContext().group.clearSearch(); //deprecated;
					getContext().group.display();
					subpage = "select";
				}
				else if (cmd == 3)
				{
					subpage = "search-name";
				}
				else if (cmd == 4)
				{
					subpage = "search-phone";
				}
				else if (cmd == 5)
				{
					subpage = "search-address";
				}
				else if (cmd == 6)
				{
					subpage = "search-group";
				}
				else if (cmd == 7)
				{
					getContext().group.displayGroup();
					subpage = "select";
				}
				else if (cmd == 8)
				{
					subpage = "sort";
				}
				else if (cmd == 9)
				{
					getContext().group.exitFile();
					getContext().setPage("home");
				}
				else
				{
					Log::e("输入错误，请重新输入。");
				}
			}
			else if (subpage == "create")
			{
				//verbose :: any !!
				if (command == "")
				{
					Log::e("姓名不能为空");
				}
				else if (command.size() > 20)
				{
					Log::e("姓名太长，应不大于20个字符");
				}
				else
				{
					getContext().group.select(command);

					getContext().subpage = "";
					getContext().setPage("contact");
				}


			}
			//选择界面
			else if (subpage == "select")
			{
				int index = -2;
				istr >> index;
				if (index == -1)
				{
					subpage = "";
				}
				else if (index == -2)
				{
					Log::e("输入并不合法");
				}
				else
				{
					if (getContext().group.select(index))
					{
						subpage = "";
						getContext().setPage("contact");
					}
					else
					{
						Log::e("输入的下标不在合理的范围内");
					}
				}

				getContext().group.clearSearch();
			}
			//按照人员来查找
			else if (subpage == "search-name" || subpage == "search-phone" || subpage == "search-address" || subpage == "search-group")
			{
				bool re = false;

				if (subpage == "search-name")
				{
					re = getContext().group.search("name", command);
				}
				else if (subpage == "search-phone")
				{
					re = getContext().group.search("phone", command);
				}
				else if (subpage == "search-address")
				{
					re = getContext().group.search("address", command);
				}
				else if (subpage == "search-group")
				{
					re = getContext().group.search("group", command);
				}

				getContext().group.display();

				if (re)
				{
					subpage = "select";
				}
				else
				{
					subpage = "";
				}
			}
			else if (subpage == "sort")
			{
				int cmd = -1;
				istr >> cmd;
				if (cmd < 0 || cmd > 4)
				{
					Log::e("输入错误");
				}
				else
				{
					if (cmd == 0)
					{
						Log::w("已退出排序");
					}
					else if (!getContext().group.empty())
					{
						if (cmd == 1)
						{
							getContext().group.sortContact("name");
						}
						else if (cmd == 2)
						{
							getContext().group.sortContact("phone");
						}
						else if (cmd == 3)
						{
							getContext().group.sortContact("address");
						}
						else if (cmd == 4)
						{
							getContext().group.sortContact("group");
						}
						Log::w("已排序完成");
					}
					else
					{
						Log::w("无联系人，无法完成排序");
					}

					getContext().subpage = "";
				}


			}
		}
		else if (page == "contact")
		{
			if (subpage == "")
			{
				Contact* current = getContext().group.currentContact;

				int cmd = -1;
				istr >> cmd;
				if (cmd == 1)
				{
					cout << *current;
				}
				else if (cmd == 2)
				{
					cout << consoleforecolor::yellow << "当前姓名为 " << current->name << endl << consoleforecolor::normal;
					subpage = "name";
				}
				else if (cmd == 3)
				{
					cout << consoleforecolor::yellow << "当前性别为 " << current->Fsex() << endl << consoleforecolor::normal;
					subpage = "sex";
				}
				else if (cmd == 4)
				{
					cout << consoleforecolor::yellow << "当前电话为 " << current->phone << endl << consoleforecolor::normal;
					subpage = "phone";
				}
				else if (cmd == 5)
				{
					cout << consoleforecolor::yellow << "当前地址为 " << current->address << endl << consoleforecolor::normal;
					subpage = "address";
				}
				else if (cmd == 6)
				{
					cout << consoleforecolor::yellow << "当前邮政编码为 " << current->postCode << endl << consoleforecolor::normal;
					subpage = "postCode";
				}
				else if (cmd == 7)
				{
					cout << consoleforecolor::yellow << "当前邮箱为 " << current->email << endl << consoleforecolor::normal;
					subpage = "email";
				}
				else if (cmd == 8)
				{
					cout << consoleforecolor::yellow << "当前QQ为 " << current->qq << endl << consoleforecolor::normal;
					subpage = "qq";
				}
				else if (cmd == 9)
				{
					cout << consoleforecolor::yellow << "当前分组为 " << current->Fgroup() << endl << consoleforecolor::normal;
					subpage = "group";
				}
				else if (cmd == 10)
				{
					subpage = "delete";
				}
				else if (cmd == 11)
				{
					if (getContext().group.currentContact->isValid())
					{
						subpage = "";
						getContext().setPage("file");
						getContext().group.currentContact = NULL;
					}
					else
					{
						Log::e("当前联系人缺少必要的字段：性别和电话，你可以选择删除联系人或者将这些信息补充完整。");
					}
				}
				else
				{
					Log::e("输入错误，请重新输入。");
				}
			}
			else if (subpage == "name")
			{
				if (command == "")
				{
					Log::e("姓名字段不能为空");
				}
				else if (command.size() > 20)
				{
					Log::e("姓名字段长度应不大于20个字符");
				}
				else
				{
					if (getContext().group.hasName(command))
					{
						Log::w("在联系人中已有该人，所以无法修改姓名为当前值");
					}
					else
					{
						getContext().group.currentContact->name = command;
						getContext().group.notify();
						Log::w("修改姓名字段成功");
					}
					subpage = "";
					//getContext().saveFile();
				}
			}
			else if (subpage == "sex")
			{
				if (command == "M" || command == "W" || command == "m" || command == "w")
				{
					if (command == "M" || command == "m")
					{
						getContext().group.currentContact->sex = "M";
					}
					else
					{
						getContext().group.currentContact->sex = "W";
					}
					Log::w("修改性别字段成功");
					subpage = "";
					//getContext().saveFile();
					getContext().group.notify();
				}
				else if (command == "")
				{
					Log::e("性别字段不能为空");
				}
				else
				{
					Log::e("非法的输入");
				}
			}
			else if (subpage == "phone")
			{
				if (command == "")
				{
					Log::e("电话不能为空");
				}
				else
				{
					if (Contact::isPhoneValid(command))
					{
						getContext().group.currentContact->phone = command;
						Log::w("修改电话字段成功");
						subpage = "";
						getContext().group.notify();
					}
					else
					{
						Log::e("电话格式不符合");
					}
				}
				//getContext().group.currentContact->phone = command;

			}
			else if (subpage == "address")
			{
				getContext().group.currentContact->address = command;
				Log::w("修改地址字段成功");
				subpage = "";
				getContext().group.notify();
			}
			else if (subpage == "postCode")
			{
				if (Contact::isPostCodeValid(command))
				{
					getContext().group.currentContact->postCode = command;
					Log::w("修改邮政编码字段成功");
					getContext().group.notify();
					subpage = "";
				}
				else
				{
					Log::w("修改邮政编码字段失败，正确输入应为空或者6位数字");
				}



			}
			else if (subpage == "email")
			{
				getContext().group.currentContact->email = command;
				Log::w("修改邮箱字段成功");
				subpage = "";
				getContext().group.notify();
			}
			else if (subpage == "delete")
			{
				if (command == "Y")
				{
					getContext().group.deleteContact();
					getContext().group.notify();

					subpage = "";
					getContext().setPage("file");
					Log::w("已删除联系人");
				}
				else if (command == "N")
				{
					subpage = "";
				}
				else
				{
					Log::e("输入错误");
				}

			}
			else if (subpage == "group")
			{
				getContext().group.currentContact->type = command;
				Log::w("修改分组信息成功");
				subpage = "";
				getContext().group.notify();
			}
			else if (subpage == "qq")
			{
				if (Contact::isQQValid(command))
				{
					getContext().group.currentContact->qq = command;
					Log::w("修改QQ信息成功");
					getContext().group.notify();
					subpage = "";
				}
				else
				{
					Log::w("修改QQ信息失败，正确输入应该为空或者5-12位数字");
				}


			}
		}
		return true;
	}
private:
};