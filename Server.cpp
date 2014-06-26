//Server.cpp

#include "Server.h"
#include "MasterMessage.h"

using namespace std;

Server::Server()
{
  inputMessage = 0;
  outputMessage = 0;

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

  cout << "start register" << endl;
	int masterSocket;
	struct sockaddr_in masterAddress;
	masterAddress.sin_family = AF_INET;
	masterAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	masterAddress.sin_port = htons(4444);

	if((masterSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

  cout << "before connect" << endl;

	if(connect(masterSocket, (struct sockaddr*)&masterAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
		cout << "connect error" << endl;
	}

  cout << "after connect" << endl;


	int length;
	InputMasterMessage *inputMaster = new InputMasterMessage;
	OutputMasterMessage *outputMaster = new OutputMasterMessage;
	inputMaster->type = REGISTER;

  cout << "before cpy" << endl;
	strcpy(inputMaster->className, name.c_str());
  cout << "after cpy" << endl;
  cout << "before send" << endl;
	length = send(masterSocket, inputMaster, sizeof(InputMasterMessage), 0);
  cout << "before recv" << endl;
	length = recv(masterSocket, outputMaster, sizeof(OutputMasterMessage), 0);

	cout << inputMaster->type << '\t' << string(inputMaster->className) << '\n';
	cout << outputMaster->port << endl;

	close(masterSocket);

	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = INADDR_ANY;
	myAddress.sin_port = htons(outputMaster->port);
	port = myAddress.sin_port;

	if((listenSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		//handle
	}

	if(bind(listenSocket, (struct sockaddr*)&myAddress, sizeof(struct sockaddr)) < 0)
	{
		//handle
	}

  
  delete inputMaster;
	delete outputMaster;

}

void Server::serve()
{
  init();

	socklen_t sinSize;
	int length;
  cout << "start serve" << endl;
	while(true)
	{
    cout << "serve loop" << endl;

		if((clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddress, &sinSize)) < 0)
		{
			cout << "accept error" << endl;
		  //handle
		}
    cout << "after accept" << endl;
    cout << inputMessage << endl;
	  length = recv(clientSocket, inputMessage, getInputMessageSize(), 0);
    cout << "after recv" << endl;
    cout << inputMessage << endl;
		//cout << ((InputMasterMessage*)inputMessage)->type << string(((InputMasterMessage*)inputMessage)->className) << endl;
	  work();
		//cout << ((OutputMasterMessage*)outputMessage)->port << endl;
    cout << "after work" << endl;
		if(outputMessage)
		{
		  if(send(clientSocket, outputMessage, getOutputMessageSize(), 0) < 0)
		  {
			  cout << "send error" << endl;
			//handle
			}
      cout << "after send" << endl;
		}
		close(clientSocket);
	}
}



