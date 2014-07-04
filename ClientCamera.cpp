//ClientCamera.cpp

#include "ClientCamera.h"

using namespace std;

ClientCamera::ClientCamera()
{
	myInput = new OutputServerCameraMessage;
	myOutput = new InputServerCameraMessage;

	inputMessage = myInput;
	outputMessage = myOutput;
}

ClientCamera::~ClientCamera()
{
	delete myInput;
	delete myOutput;
}

size_t ClientCamera::getInputMessageSize()
{
	return sizeof(OutputServerCameraMessage);
}

size_t ClientCamera::getOutputMessageSize()
{
	return sizeof(InputServerCameraMessage);
}

void ClientCamera::run()
{
	myLookup("ServerCamera");
	char temp;
	cin >> temp;
	myOutput->commandName = getcamera;
	
	request();
	cout << myInput->returnValues[0] << '\t' << myInput->returnValues[1] << endl;
}

