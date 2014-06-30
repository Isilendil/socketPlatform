//Client.h
//class Client

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>
#include <cstring>
#include <iostream>

#include "MasterMessage.h"

class Client
{
public:
  Client();
	~Client();

	void myLookup(std::string serverClassName);

	void init();

	virtual void run() = 0;

protected:
	std::string serverClassName;
  int serverSocket;

	struct sockaddr_in myAddress;
	struct sockaddr_in serverAddress;

	virtual size_t getInputMessageSize() = 0;
	virtual size_t getOutputMessageSize() = 0;

	void *inputMessage;
	void *outputMessage;

	void request();

private:

};

#endif

