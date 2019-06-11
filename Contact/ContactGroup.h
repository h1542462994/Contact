#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<vcruntime.h>
#include<algorithm>
#include"Log.h"
#include"Contact.h"
#include"Tool.h"

#define L_ID 6
#define L_NAME 12
#define L_SEX 6
#define L_PHONE 20
#define L_ADDRESS 20
#define L_GROUP 12

using namespace std;

bool contactComparerByGroup(Contact* p1, Contact* p2)
{
	return p1->type < p2->type;
}
bool contactComparerByName(Contact* p1, Contact* p2)
{
	return p1->name < p2->name;
}
bool contactComparerByPhone(Contact* p1, Contact* p2)
{
	return p1->phone < p2->phone;
}
bool contactComparerByAddress(Contact* p1, Contact* p2)
{
	return p1->address < p2->address;
}


enum class FileState 
{
	Closed,
	Changed,
	NoChange,
};

class ContactGroup 
{
public:
	~ContactGroup() 
	{
		clearData();
	}

	FileState getFileState()
	{
		return fileState;
	}
	Contact& Current() 
	{
		return *currentContact;
	}
	bool empty()
	{
		return data.empty();
	}
	//�����ļ����������ڸ��ļ������½��ļ�
	bool loadFile(string fileName) 
	{
		if (fileState == FileState::Closed)
		{
			fileState = FileState::NoChange;
			this->fileName = fileName;
			fstream _file;
			_file.open(fileName, ios::in);

			clearData();

			if (!_file)
			{
				return true;
			}
			else
			{
				int index = 0;
				int ti = 0;
				string line;
				Contact* contact = NULL;
				while (getline(_file, line) && !_file.eof())
				{
					if (ti == 0)
					{
						contact = new Contact();
						contact->name = line.substr(1);
					}
					else if (ti == 1)
					{
						contact->sex = line;
					}
					else if (ti == 2)
					{
						contact->phone = line;
					}
					else if (ti == 3)
					{
						contact->address = line;
					}
					else if (ti == 4)
					{
						contact->postCode = line;
					}
					else if (ti == 5)
					{
						contact->email = line;
					}
					else if (ti == 6)
					{
						contact->qq = line;
					}
					else if (ti == 7)
					{
						contact->type = line;
					}
					ti++;
					if (ti == 8)
					{
						ti = 0;
						data.push_back(contact);
					}
				}
				_file.close();
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	void saveFile()
	{
		if (fileState == FileState::Changed)
		{
			fstream _file;
			_file.open(fileName, ios::out | ios::trunc);
			for (int i = 0; i < data.size(); i++)
			{
				Contact* c = data[i];
				_file << "#" << c->name << endl
					<< c->sex << endl
					<< c->phone << endl
					<< c->address << endl
					<< c->postCode << endl
					<< c->email << endl
					<< c->qq << endl
					<< c->type << endl;
			}
			_file.close();
			fileState = FileState::NoChange;
		}
	}
	void exitFile() 
	{
		clearSearch();
		clearData();
		fileName = "";
		fileState = FileState::Closed;
	}
	string getFileName() 
	{
		return fileName;
	}

	//ѡ����ϵ�ˣ��������ڴ�����
	//����ֵ���Ƿ�ǰ���и���ϵ��
	bool select(string name) 
	{
		//bool flag = false;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i]->name == name)
			{
				currentContact = data[i];
				return true;
			}
		}

		Contact* contact = new Contact(name);
		data.push_back(contact);
		currentContact = contact;
		fileState = FileState::Changed;

		return false;
	}
	bool select(int index)
	{
		if (searchdata != NULL)
		{
			if (index >= 0 && index < searchdata->size())
			{
				currentContact = searchdata->at(index);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (index >= 0 && index < data.size())
			{
				currentContact = data[index];
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	bool deleteContact()
	{
		if (currentContact!=NULL)
		{
			for (int i = 0; i < data.size(); i++)
			{
				if (data[i] == currentContact)
				{
					vector<Contact*>::iterator iter = data.begin() + i;
					data.erase(iter);
				}
			}

			delete currentContact;
			currentContact = NULL;
			fileState = FileState::Changed;
			return true;
		}
		else
		{
			return false;
		}
	}
	void notify() 
	{
		fileState = FileState::Changed;
	}

	void clearSearch()
	{
		if (searchdata!=NULL)
		{
			delete searchdata;
			searchdata = NULL;
		}
	}
	bool search(string mode,string key)
	{
		clearSearch();
		searchMode = mode;
		searchKey = key;
		auto re = new vector<Contact*>();
		for (int i = 0; i < data.size(); i++)
		{
			if (mode == "name")
			{
				if (hasSubString(data[i]->name,key))
				{
					re->push_back(data[i]);
				}
			}
			else if (mode == "phone")
			{
				if (hasSubString(data[i]->phone,key))
				{
					re->push_back(data[i]);
				}
			}
			else if (mode == "address")
			{
				if (hasSubString(data[i]->address,key))
				{
					re->push_back(data[i]);
				}
			}
			else if (mode == "group")
			{
				if (hasSubString(data[i]->type,key))
				{
					re->push_back(data[i]);
				}
			}
		}

		//if (mode == "name")
		//{
		//	sort(re->begin(), re->end(), contactComparerByName);
		//}
		//else if (mode == "phone")
		//{
		//	sort(re->begin(), re->end(), contactComparerByPhone);
		//}
		//else if (mode == "address")
		//{
		//	sort(re->begin(), re->end(), contactComparerByAddress);
		//}
		//else
		//{
		//	sort(re->begin(), re->end(), contactComparerByGroup);
		//}

		sort(re->begin(), re->end(), contactComparerByName);

		searchdata = re;

		return re->size() != 0;
	}
	bool display()
	{
		if (searchdata == NULL)
		{
			return  displayAll();
		}
		else 
		{
			return  displaySearch();
		}

	}
	//չʾһ����ϵ�˵ķ������
	void displayGroup()
	{
		if (data.size() == 0)
		{
			Log::w("��ϵ��Ϊ��");
		}
		else
		{
			auto ccopy = new vector<Contact*>();
			for (int i = 0; i < data.size(); i++)
			{
				ccopy->push_back(data[i]);
			}

			sort(ccopy->begin(), ccopy->end(), contactComparerByGroup);

			cout << "  " << consoleforecolor::cyan 
				<< setw(L_ID) << std::left << "���"
				<< setw(L_NAME) << "����"
				<< setw(L_SEX) << "�Ա�"
				<< setw(L_PHONE) << "�绰"
				<< setw(L_ADDRESS) << "��ַ" << consoleforecolor::normal << endl;
			string type = ccopy->at(0)->type;
			cout << consoleforecolor::ochre << (type == "" ? "��" : type) << consoleforecolor::normal << endl;


			for (int i = 0; i < ccopy->size(); i++)
			{
				if (ccopy->at(i)->type != type)
				{
					type = ccopy->at(i)->type;
					cout << consoleforecolor::ochre << (type == "" ? "��" : type) << consoleforecolor::normal << endl;
				}
				cout << "  ";
				Contact* c = ccopy->at(i);
				cout << consoleforecolor::cyan
					<< setw(L_ID) << i 
					<< consoleforecolor::normal;
				//<< setw(12) << c->name
				if (eggvar == 1 && (c->name == "cg"))
				{
					cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
				}
				else
				{
					cout << setw(L_NAME) << c->name;
				}
				cout << setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
					<< setw(L_PHONE) << c->phone
					<< setw(L_ADDRESS) << c->address
					<< consoleforecolor::normal << endl;
			}

			clearSearch();
			searchdata = ccopy;
		}
	}
	//����ģʽ����ϵ�˽�������
	void sortContact(string mode)
	{
		if (mode == "name")
		{
			sort(data.begin(), data.end(), contactComparerByName);
		}
		else if (mode == "phone")
		{
			sort(data.begin(), data.end(), contactComparerByPhone);
		}
		else if (mode == "address")
		{
			sort(data.begin(), data.end(), contactComparerByAddress);
		}
		else if (mode == "group")
		{
			sort(data.begin(), data.end(), contactComparerByGroup);
		}

		fileState = FileState::Changed;
	}
	bool hasName(string name) 
	{
		int len = data.size();
		for (int i = 0; i < len; i++)
		{
			if (data[i] != currentContact && data[i]->name == name)
			{
				return true;
			}
		}
		return false;
	}

	FileState fileState = FileState::Closed;
	//���������
	vector<Contact*> data;
	Contact* currentContact = NULL;
	string fileName;

	//�������й�
	vector<Contact*>* searchdata = NULL;
	string searchMode;
	string searchKey;
	const int eggvar = 0;
private:

	void clearData()
	{
		for (int i = 0; i < data.size(); i++)
		{
			delete data[i];
		}
		data.clear();
	}

	bool displayAll() 
	{
		if (data.size() < 1)
		{
			Log::w("��ǰ��û����ϵ��");
			return false;
		}
		else
		{
			cout << consoleforecolor::cyan << setw(L_ID) << std::left << "���"
				<< setw(L_NAME) << "����"
				<< setw(L_SEX) << "�Ա�"
				<< setw(L_PHONE) << "�绰"
				<< setw(L_ADDRESS) << "��ַ"
				<< setw(L_GROUP) << "����" << consoleforecolor::normal << endl;

			for (int i = 0; i < data.size(); i++)
			{
				cout << consoleforecolor::cyan << setw(L_ID) << std::left << i  << consoleforecolor::normal;


				Contact* c = data[i];

				if (eggvar == 1 && (c->name == "cg"))
				{
					cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
				}
				else
				{
					cout << setw(L_NAME) << c->name;
				}

				cout
					<< setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
					<< setw(L_PHONE) << c->phone
					<< setw(L_ADDRESS) << c->address
					<< setw(L_GROUP) << (c->type == "" ? "��" : c->type)
					<< consoleforecolor::normal << endl;
			}
			return true;
		}
	}
	bool displaySearch() 
	{
		if (searchdata->size() < 1)
		{
			Log::w("û�в鵽����ϵ��");
			return false;
		}
		else 
		{
			cout << consoleforecolor::cyan
				<< setw(L_ID) << std::left << "���";
			if (searchMode == "address")
			{
				cout << setw(L_ADDRESS) << "��ַ"
					<< setw(L_NAME) << "����"
					<< setw(L_SEX) << "�Ա�"
					<< setw(L_PHONE) << "�绰"
					<< setw(L_GROUP) << "����" << consoleforecolor::normal << endl;
			}
			else if (searchMode == "name")
			{
				cout
					<< setw(L_NAME) << "����"
					<< setw(L_SEX) << "�Ա�"
					<< setw(L_PHONE) << "�绰"
					<< setw(L_ADDRESS) << "��ַ"
					<< setw(L_GROUP) << "����" << consoleforecolor::normal << endl;
			}
			else if (searchMode == "phone")
			{
				cout
					<< setw(L_PHONE) << "�绰"
					<< setw(L_NAME) << "����"
					<< setw(L_SEX) << "�Ա�"
					<< setw(L_ADDRESS) << "��ַ"
					<< setw(L_GROUP) << "����" << consoleforecolor::normal << endl;
			}
			else if (searchMode == "group")
			{
				cout
					<< setw(L_ADDRESS) << "��ַ"
					<< setw(L_NAME) << "����"
					<< setw(L_SEX) << "�Ա�"
					<< setw(L_PHONE) << "�绰"
					<< setw(L_GROUP) << "����" << consoleforecolor::normal << endl;
			}

			for (int i = 0; i < searchdata->size(); i++)
			{
				cout << consoleforecolor::cyan << setw(L_ID) << i  << consoleforecolor::normal;
				Contact* c = searchdata->at(i);

				if (searchMode == "address")
				{
					cout << setw(L_ADDRESS);
					//outputS(c->address,searchKey);

					cout << consoleforecolor::ochre
						<< setw(L_ADDRESS) << c->address
						<< consoleforecolor::normal;
					//<< setw(12) << c->name 
					if (eggvar == 1 && (c->name == "cg"))
					{
						cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
					}
					else
					{
						cout << setw(L_NAME) << c->name;
					}
					cout << setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
						<< setw(L_PHONE) << c->phone
						<< setw(L_GROUP) << (c->type == "" ? "��" : c->type)
						<< consoleforecolor::normal;
				}
				else if (searchMode == "name")
				{
					cout << consoleforecolor::ochre;

					if (eggvar == 1 && (c->name == "cg"))
					{
						cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
					}
					else
					{
						cout << setw(L_NAME) << c->name;
					}

					cout << consoleforecolor::normal
						<< setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
						<< setw(L_PHONE) << c->phone
						<< setw(L_ADDRESS) << c->address
						<< setw(L_GROUP) << (c->type == "" ? "��" : c->type)
						<< consoleforecolor::normal;
				}
				else if (searchMode == "phone")
				{
					cout << consoleforecolor::ochre
						<< setw(20) << c->phone
						<< consoleforecolor::normal;
					//<< setw(12) << c->name
					if (eggvar == 1 && (c->name == "cg"))
					{
						cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
					}
					else
					{
						cout << setw(L_NAME) << c->name;
					}
					cout << setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
						<< setw(L_ADDRESS) << c->address
						<< setw(L_GROUP) << (c->type == "" ? "��" : c->type)
						<< consoleforecolor::normal;
				}
				else if (searchMode == "group")
				{
					cout << consoleforecolor::ochre
						<< setw(L_GROUP) << (c->type == "" ? "��" : c->type)
						<< consoleforecolor::normal;
					//<< setw(12) << c->name
					if (eggvar == 1 && (c->name == "cg"))
					{
						cout << setw(L_NAME) << consoleforecolor::red << ("(*��-��*) " + c->name) << consoleforecolor::normal;
					}
					else
					{
						cout << setw(L_NAME) << c->name;
					}
					cout << setw(L_SEX) << (c->sex == "M" ? "��" : "Ů")
						<< setw(L_PHONE) << c->phone
						<< setw(L_ADDRESS) << c->address
						<< consoleforecolor::normal;
				}
				cout << endl;
			}

			return true;
		}

	}
	

};