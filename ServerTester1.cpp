//ServerTester1.cpp

#include "ServerTester1.h"

using namespace std;

ServerTester1::ServerTester1()
{
	name = "ServerTester1";

  myInput = new InputServerTester1Message;
	myOutput = new OutputServerTester1Message;

	inputMessage = myInput;
	outputMessage = myOutput;

	myRegister();
}

ServerTester1::~ServerTester1()
{
	delete myInput;
	delete myOutput;
}

size_t ServerTester1::getInputMessageSize()
{
	return sizeof(InputServerTester1Message);
}

size_t ServerTester1::getOutputMessageSize()
{
	return sizeof(OutputServerTester1Message);
}

void ServerTester1::work()
{
	//myInput = (InputServerTester1Message*)input;
	cout << myInput->a << '\t' << string(myInput->b) << '\n';
	myOutput->c = -myInput->a;
	strcpy(myOutput->d, "hello");
	cout << myOutput->c << '\t' << string(myOutput->d) << '\n';
	//cout << myOutput->n << '\n';
	return;
}
