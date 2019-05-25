#pragma once
#include"Context.h"
#include"Log.h"
#include<iostream>
using namespace std;

class AppBase
{
public:
	void run()
	{
		onLoad();
		handleInput();
	}
	AppBase(Context* context):context(context)
	{
	}

protected:


	virtual string onTip() = 0;

	virtual void onLoad() = 0;

	virtual bool onHandleInput(string command) = 0;
	
	Context& getContext()
	{
		return *context;
	}

private:
	void handleInput() 
	{
		while (true)
		{
			auto tip = onTip();
			cout << consoleforecolor::seablue << "> " << tip << ":" <<  consoleforecolor::normal;
			string cmd;
			getline(cin, cmd);
			if (!onHandleInput(cmd))
			{
				break;
			}
		}
	}

	Context* context;


};