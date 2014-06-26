//Server.h
//class Server

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <cstring>
#include <string>
#include <iostream>

#include "MasterMessage.h"

class Server
{
public:
  Server();
	~Server();

  void myRegister();


	void init();
	void serve();
	virtual void work() = 0;

protected:
  std::string name;

  int listenSocket;
	int clientSocket;

	struct sockaddr_in myAddress;
	struct sockaddr_in clientAddress;

  int port;
 
	virtual size_t getInputMessageSize() = 0;
	virtual size_t getOutputMessageSize() = 0;

  void *inputMessage;
	void *outputMessage;

private:

};

#endif
