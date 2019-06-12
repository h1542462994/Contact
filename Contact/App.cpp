#pragma once
#include "App.h"
#include<sstream>
#include"Tool.h"

using namespace std;

void App::onLoad()
{
	Log::i("��ӭ�����绰��ϵͳ���뾴�����ðɡ�");
}

string App::onTip()
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
			tip = "��ѡ��˵��е�һ��";
		}
		else if (subpage == "create")
		{
			tip = "�������½�/�򿪵��ļ���";
		}
	}
	else if (page == "file")
	{
		if (subpage == "")
		{
			getContext().group.saveFile();
			tip = "��ѡ��˵��е�һ��";
		}
		else if (subpage == "create")
		{
			tip = "�������½�/����ϵ�˵�����";
		}
		else if (subpage == "search-name")
		{
			tip = "��������Ҫ��ѯ�˵�����";
		}
		else if (subpage == "search-phone")
		{
			tip = "��������Ҫ��ѯ�˵ĵ绰";
		}
		else if (subpage == "search-address")
		{
			tip = "��������Ҫ��ѯ�˵ĵ�ַ";
		}
		else if (subpage == "search-group")
		{
			tip = "��������Ҫ��ѯ�ķ�����Ϣ";
		}
		else if (subpage == "select")
		{
			tip = "ѡ��ڼ����أ����������-1ȡ���ò���";
		}
		else if (subpage == "sort")
		{
			cout << "0:�˳�����" << endl
				<< "1:����" << endl
				<< "2:�绰" << endl
				<< "3:��ַ" << endl
				<< "4:����" << endl;
			tip = "��ѡ������ļ�";
		}
	}
	else if (page == "contact")
	{
		if (subpage == "")
		{
			tip = "��ѡ��˵��е�һ��";
		}
		else if (subpage == "name")
		{
			tip = "����������";
		}
		else if (subpage == "sex")
		{
			tip = "�������Ա�(M/W)";
		}
		else if (subpage == "phone")
		{
			tip = "������绰";
		}
		else if (subpage == "address")
		{
			tip = "�������ַ";
		}
		else if (subpage == "postCode")
		{
			tip = "��������������";
		}
		else if (subpage == "email")
		{
			tip = "����������";
		}
		else if (subpage == "qq")
		{
			tip = "������QQ��";
		}
		else if (subpage == "delete")
		{
			tip = "��ȷ��Ҫɾ������ϵ����(Y/N)";
		}
		else if (subpage == "group")
		{
			tip = "�����������Ϣ";
		}
	}
	return tip;
}

bool App::onHandleInput(string command)
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
			//�½�/���ļ�
			if (cmd == 1)
			{
				subpage = "create";
			}
			//�˳�����
			else if (cmd == 2)
			{
				return false;
			}
			else
			{
				Log::e("����������������롣");
			}
		}
		else if (subpage == "create")
		{
			int check = checkFileName(command);
			if (check == 1)
			{
				Log::e("�ļ�������Ϊ��");
			}
			else if (check == 2)
			{
				Log::e("�ļ���̫������Ӧ�ó���40���ַ�");
			}
			else if (check == 3)
			{
				Log::e("�ļ�����Ӧ�ú���[/\\:*\"<>|?]��Щ�Ƿ��ַ�");
			}
			else
			{

				bool r = getContext().group.loadFile(command);
				if (r)
				{
					Log::w("�Ѵ��ļ�" + command);
				}
				else
				{
					Log::w("�Ѵ����ļ�" + command);
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
				Log::e("����������������롣");
			}
		}
		else if (subpage == "create")
		{
			//verbose :: any !!
			if (command == "")
			{
				Log::e("��������Ϊ��");
			}
			else if (command.size() > 20)
			{
				Log::e("����̫����Ӧ������20���ַ�");
			}
			else
			{
				getContext().group.select(command);

				getContext().subpage = "";
				getContext().setPage("contact");
			}


		}
		//ѡ�����
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
				Log::e("���벢���Ϸ�");
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
					Log::e("������±겻�ں���ķ�Χ��");
				}
			}

			getContext().group.clearSearch();
		}
		//������Ա������
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
				Log::e("�������");
			}
			else
			{
				if (cmd == 0)
				{
					Log::w("���˳�����");
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
					Log::w("���������");
				}
				else
				{
					Log::w("����ϵ�ˣ��޷��������");
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
				cout << consoleforecolor::yellow << "��ǰ����Ϊ " << current->name << endl << consoleforecolor::normal;
				subpage = "name";
			}
			else if (cmd == 3)
			{
				cout << consoleforecolor::yellow << "��ǰ�Ա�Ϊ " << current->Fsex() << endl << consoleforecolor::normal;
				subpage = "sex";
			}
			else if (cmd == 4)
			{
				cout << consoleforecolor::yellow << "��ǰ�绰Ϊ " << current->phone << endl << consoleforecolor::normal;
				subpage = "phone";
			}
			else if (cmd == 5)
			{
				cout << consoleforecolor::yellow << "��ǰ��ַΪ " << current->address << endl << consoleforecolor::normal;
				subpage = "address";
			}
			else if (cmd == 6)
			{
				cout << consoleforecolor::yellow << "��ǰ��������Ϊ " << current->postCode << endl << consoleforecolor::normal;
				subpage = "postCode";
			}
			else if (cmd == 7)
			{
				cout << consoleforecolor::yellow << "��ǰ����Ϊ " << current->email << endl << consoleforecolor::normal;
				subpage = "email";
			}
			else if (cmd == 8)
			{
				cout << consoleforecolor::yellow << "��ǰQQΪ " << current->qq << endl << consoleforecolor::normal;
				subpage = "qq";
			}
			else if (cmd == 9)
			{
				cout << consoleforecolor::yellow << "��ǰ����Ϊ " << current->Fgroup() << endl << consoleforecolor::normal;
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
					Log::e("��ǰ��ϵ��ȱ�ٱ�Ҫ���ֶΣ��Ա�͵绰�������ѡ��ɾ����ϵ�˻��߽���Щ��Ϣ����������");
				}
			}
			else
			{
				Log::e("����������������롣");
			}
		}
		else if (subpage == "name")
		{
			if (command == "")
			{
				Log::e("�����ֶβ���Ϊ��");
			}
			else if (command.size() > 20)
			{
				Log::e("�����ֶγ���Ӧ������20���ַ�");
			}
			else
			{
				if (getContext().group.hasName(command))
				{
					Log::w("����ϵ�������и��ˣ������޷��޸�����Ϊ��ǰֵ");
				}
				else
				{
					getContext().group.currentContact->name = command;
					getContext().group.notify();
					Log::w("�޸������ֶγɹ�");
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
				Log::w("�޸��Ա��ֶγɹ�");
				subpage = "";
				//getContext().saveFile();
				getContext().group.notify();
			}
			else if (command == "")
			{
				Log::e("�Ա��ֶβ���Ϊ��");
			}
			else
			{
				Log::e("�Ƿ�������");
			}
		}
		else if (subpage == "phone")
		{
			if (command == "")
			{
				Log::e("�绰����Ϊ��");
			}
			else
			{
				if (Contact::isPhoneValid(command))
				{
					getContext().group.currentContact->phone = command;
					Log::w("�޸ĵ绰�ֶγɹ�");
					subpage = "";
					getContext().group.notify();
				}
				else
				{
					Log::e("�绰��ʽ������");
				}
			}
			//getContext().group.currentContact->phone = command;

		}
		else if (subpage == "address")
		{
			getContext().group.currentContact->address = command;
			Log::w("�޸ĵ�ַ�ֶγɹ�");
			subpage = "";
			getContext().group.notify();
		}
		else if (subpage == "postCode")
		{
			if (Contact::isPostCodeValid(command))
			{
				getContext().group.currentContact->postCode = command;
				Log::w("�޸����������ֶγɹ�");
				getContext().group.notify();
				subpage = "";
			}
			else
			{
				Log::w("�޸����������ֶ�ʧ�ܣ���ȷ����ӦΪ�ջ���6λ����");
			}



		}
		else if (subpage == "email")
		{
			getContext().group.currentContact->email = command;
			Log::w("�޸������ֶγɹ�");
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
				Log::w("��ɾ����ϵ��");
			}
			else if (command == "N")
			{
				subpage = "";
			}
			else
			{
				Log::e("�������");
			}

		}
		else if (subpage == "group")
		{
			getContext().group.currentContact->type = command;
			Log::w("�޸ķ�����Ϣ�ɹ�");
			subpage = "";
			getContext().group.notify();
		}
		else if (subpage == "qq")
		{
			if (Contact::isQQValid(command))
			{
				getContext().group.currentContact->qq = command;
				Log::w("�޸�QQ��Ϣ�ɹ�");
				getContext().group.notify();
				subpage = "";
			}
			else
			{
				Log::w("�޸�QQ��Ϣʧ�ܣ���ȷ����Ӧ��Ϊ�ջ���5-12λ����");
			}


		}
	}
	return true;
}
