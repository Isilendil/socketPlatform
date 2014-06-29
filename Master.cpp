//Master.cpp

#include "Master.h"

using namespace std;

int Master::count = 1;

Master::Master()
{
	name = "Master";

  myInput = new InputMasterMessage;
	myOutput = new OutputMasterMessage;

	inputMessage = myInput;
	outputMessage = myOutput;


	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(4444);
	port = 4444;

	if((listenSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(bind(listenSocket, (struct sockaddr*)&myAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
	}


}

Master::~Master()
{
	delete myInput;
	delete myOutput;
}

size_t Master::getInputMessageSize()
{
	return sizeof(InputMasterMessage);
}

size_t Master::getOutputMessageSize()
{
	return sizeof(OutputMasterMessage);
}

int Master::serverRegister(string className)
{
	for(vector<ServerRecord>::iterator iter = serverInformation.begin();
		 iter != serverInformation.end(); ++iter)
	{
		if(iter->className == className)
		{
			return iter->port;
	  }
	}

	int portTemp = 4444 + count;
	count ++;
	serverInformation.push_back(ServerRecord(className, portTemp));
	cout << "!!" << endl;

	return portTemp;
}

int Master::clientLookup(string className)
{
	for(vector<ServerRecord>::iterator iter = serverInformation.begin();
		 iter != serverInformation.end(); ++iter)
	{
		if(iter->className == className)
		{
			return iter->port;
	  }
	}
	return -1;
}

void Master::work()
{
	//myInput = (InputMasterMessage*)inputMessage;
	string temp = myInput->className;
	int portTemp;
	if( myInput->type == REGISTER )
	{
		portTemp = serverRegister(temp);
	}
	else if( myInput->type == LOOKUP )
	{
		portTemp = clientLookup(temp);
	}
	myOutput->port = portTemp;

	cout << myInput->type << '\t' << string(myInput->className) << endl;
	cout << myOutput->port << endl;
	return;
}
