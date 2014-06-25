//Server.cpp

#include "Server.h"


using namespace std;

Server::Server()
{
  inputMessage = nullptr;
  outputMessage = nullptr;

}

Server::~Server()
{
}


void Server::init()
{
  listen(listenSocket, 5);
}

void Server::myRegister()
{

	int masterSocket;
	struct sockaddr_in masterAddress;
	masterAddress.sin_family = AF_INET;
	masterAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	masterAddress.sin_port = htons(4444);

	if((masterSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(connect(masterSocket, (struct sockaddr*)&masterAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
	}

	int length;
	InputMasterMessage *inputMaster;
	inputMaster->type = REGISTER;
	strcpy(inputMaster->className, name.c_str());
	OutputMasterMessage *outputMaster;
	length = send(masterSocket, inputMaster, sizeof(InputMasterMessage), 0);
	length = recv(masterSocket, outputMaster, sizeof(OutputMasterMessage), 0);

	cout << inputMaster->type << '\t' << string(inputMaster->className) << '\n';

	close(masterSocket);

	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(outputMaster->port);

	if((listenSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(bind(listenSocket, (struct sockaddr*)&myAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
	}


}

void Server::run()
{
	int sinSize;
	int length;
	while(true)
	{
		if((clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddress, &sinSize)) < 0)
		{
		  //handle
		}
	  length = recv(clientSocket, inputMessage, getInputMessageSize(), 0)
	  outputMessage = work(inputMessage);
		if(!outputMessage)
		{
		  if(send(clientSocket, outputMessage, getOutputMessageSize()) < 0)
		  {
			//handle
			}
		}
		close(clientSocket);
	}
}



