//ClientTester1.cpp

#include "ClientTester1.h"

using namespace std;

ClientTester1::ClientTester1()
{
  myInput = new OutputServerTester1Message;
	myOutput = new InputServerTester1Message;

	inputMessage = myInput;
	outputMessage = myOutput;
}

ClientTester1::~ClientTester1()
{
	delete myInput;
	delete myOutput;
}

size_t ClientTester1::getInputMessageSize()
{
	return sizeof(OutputServerTester1Message);
}

size_t ClientTester1::getOutputMessageSize()
{
	return sizeof(InputServerTester1Message);
}

void ClientTester1::run()
{
	myLookup("ServerTester1");
	myOutput->a = 1024;
	strcpy(myOutput->b, "world");
	cout << myOutput->a << '\t' << string(myOutput->b) << endl;
	request();
	cout << myInput->c << '\t' << string(myInput->d) << endl;
}
