#include<iostream>
#include<vector>
#include<string>
#include"Context.h"
#include"App.h"

using namespace std;

int main() 
{
	Context context;
	App app(&context);
	app.run();
}