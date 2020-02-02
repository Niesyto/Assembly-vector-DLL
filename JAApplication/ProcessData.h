#pragma once
#include "stdafx.h";
#include <string>

class ProcessData
{
public:
	ProcessData();
	~ProcessData();
	void run(int, string, bool);
private:
	typedef void(WINAPI *MyProc1)(float*, float*, float*, int);
	typedef void(*JACpp)(float*, float*, float*, int);

	
};

