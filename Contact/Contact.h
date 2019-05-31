#pragma once
#include<string>
#include<iostream>
#include<iomanip>
#include<ctype.h>

using namespace std;

//data class
class Contact
{
public:
	Contact()
	{
	}
	Contact(string name) :name(name)
	{
	}

	string name;
	string sex;
	string phone;
	string address;
	string postCode;
	string email;
	string qq;
	string type;

	string Fsex() const
	{
		if (sex == "")
		{
			return "(��)";
		}
		else if (sex == "M")
		{
			return "��";
		}
		else
		{
			return "Ů";
		}
	}
	string Fgroup() const
	{
		if (type == "")
		{
			return "(��)";
		}
		else
		{
			return type;
		}
	}

	friend ostream& operator << (ostream& out, const Contact& obj)
	{
		out << setw(10) << "����:" << obj.name << endl
			<< setw(10) << "�Ա�:" << obj.Fsex() << endl
			<< setw(10) << "�绰:" << obj.phone << endl
			<< setw(10) << "��ַ:" << obj.address << endl
			<< setw(10) << "��������:" << obj.postCode << endl
			<< setw(10) << "����:" << obj.email << endl
			<< setw(10) << "QQ��:" << obj.qq << endl
			<< setw(10) << "����:" << obj.Fgroup() << endl;

		return out;
	}

	void showSimple()
	{
		cout << setw(12) << name << setw(20) << phone << setw(6) << ( type == ""?"(��)":type) << endl;
	}

	static bool isSexValid(string sex) 
	{
		if (sex == "M" || sex == "W")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static bool isNameValid(string name)
	{
		if (name == "" || name.size()>20)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	static bool isPhoneValid(string phone)
	{
		if (phone.length() != 11)
		{
			return false;
		}
		for (int i = 0; i < phone.length(); i++)
		{
			if (!isdigit(phone[i]))
			{
				return false;
			}
		}


		return true;
	}

	bool isValid()
	{
		if (sex == "M" || sex == "W")
		{
		}
		else
		{
			return false;
		}

		if (phone == "")
		{
			return false;
		}
		return true;
	}
};