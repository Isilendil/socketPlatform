//ClientQrobot.cpp

#include "ClientQrobot.h"

using namespace std;

ClientQrobot::ClientQrobot()
{
	myInput = new OutputServerQrobotMessage;
	myOutput = new InputServerQrobotMessage;

	inputMessage = myInput;
	outputMessage = myOutput;
}

ClientQrobot::~ClientQrobot()
{
	delete myInput;
	delete myOutput;
}

size_t ClientQrobot::getInputMessageSize()
{
	return sizeof(OutputServerQrobotMessage);
}

size_t ClientQrobot::getOutputMessageSize()
{
	return sizeof(InputServerQrobotMessage);
}

void ClientQrobot::run()
{
	myLookup("ServerQrobot");
	myOutput->commandName = Heart;
	myOutput->parameters[0] = 0;
	myOutput->parameters[1] = 0;
	myOutput->parameters[2] = 255;
	request();
	cout << myInput->returnValues[0] << '\t' << myInput->returnValues[1] << endl;
}
