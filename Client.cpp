//Client.cpp

#include "Client.h"

using namespace std;

Client::Client()
{
	inputMessage = 0;
	outputMessage = 0;
}

Client::~Client()
{
}

void Client::init()
{
}

void Client::myLookup(string serverClassName)
{
	cout << "start lookup" << endl;
  int masterSocket;
	struct sockaddr_in masterAddress;
	masterAddress.sin_family = AF_INET;
	masterAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	masterAddress.sin_port = htons(4444);

	if((masterSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(connect(masterSocket , (struct sockaddr*)&masterAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
		cout << "connect error" << endl;
	}

  int length;
	InputMasterMessage *inputMaster = new InputMasterMessage;
	OutputMasterMessage *outputMaster = new OutputMasterMessage;
	inputMaster->type = LOOKUP;

	strcpy(inputMaster->className, serverClassName.c_str());
	length = send(masterSocket, inputMaster, sizeof(InputMasterMessage), 0);
	length = recv(masterSocket, outputMaster, sizeof(OutputMasterMessage), 0);
	
	close(masterSocket);

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(outputMaster->port);
	
	if((serverSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
	}

	delete inputMaster;
	delete outputMaster;

}

void Client::request()
{
  if(connect(serverSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
		cout << "connect error" << endl;
	}
  
	int length;
	socklen_t sinSize;

	if(send(serverSocket, outputMessage, getOutputMessageSize(), 0) < 0)
	{
		//handle
		cout << "send error" << endl;
	}
	length = recv(serverSocket, inputMessage, getInputMessageSize(), 0);

  close(serverSocket);

} 

