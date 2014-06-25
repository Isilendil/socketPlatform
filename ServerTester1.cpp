//ServerTester1.cpp

#include "ServerTester1.h"

ServerTester1::ServerTester1()
{
	name = "ServerTester1";
	myRegister();
}

ServerTester1::~ServerTester1()
{
}

size_t ServerTester1::getInputMessageSize()
{
	return sizeof(InputServerTester1Message);
}

size_t ServerTester1::getOutputMessageSize()
{
	return sizeof(OutputServerTester1Message);
}

void ServerTester1::run()
{
	while(true)
	{
	}
}
