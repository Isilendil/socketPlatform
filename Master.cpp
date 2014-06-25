//Master.cpp

#include "Master.h"

using namespace std;

int Master::count = 1;

Master::Master()
{
	name = "Master";


	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(4444);

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
	int portTemp = 4444 + count;
	count ++;
	serverInformation.push_back(ServerRecord(className, portTemp));
	cout << outputMemory->inputMemoryKey << endl;
	cout << outputMemory->outputMemoryKey << endl;
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

void* Master::work(void *inputMessage)
{
	inputMasterMessage = (InputMasterMessage*)inputMessage;
	string temp = inputMasterMessage->className;
	int portTemp;
	if( (InputMasterMessage*)(inputMessage)->type == REGISTER )
	{
		portTemp = serverRegister(temp);
	}
	else if( (InputMasterMessage*)(inputMessage)->type == LOOKUP )
	{
		portTemp = clientLookup(temp);
	}
	outputMasterMessage->port = portTemp;
	return outputMasterMessage;
	/*
	while(true)
	{
	  if(!inputMemory->clean)
	  {
			char temp[20];
			strcmp(temp, inputMemory->className);
			cout << "!" << endl;
		  if(inputMemory->senderType == SERVER)
		  {
				
        serverRegister(string(temp));
		  }
		  else if(inputMemory->senderType = CLIENT)
		  {
        serverLookup(string(temp));
		  }
		  inputMemory->clean = true;
	  }
	}
	*/
}
