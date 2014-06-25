//Server.h
//class Server

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <string>
#include <iostream>

#include "MasterMessage.h"

class Server
{
public:
  Server();
	virtual ~Server() = 0;

  key_t getInputMemoryKey();
  key_t getOutputMemoryKey();

	void setInputMemoryKey(key_t key);
	void setOutputMemoryKey(key_t key);

  void myRegister();

	virtual void run() = 0;

protected:
  key_t inputMemoryKey;
	key_t outputMemoryKey;

  int inputMemoryId;
	int outputMemoryId;

  void *inputMemory;
	void *outputMemory;

  std::string name;
 
	virtual size_t getInputMessageSize() = 0;
	virtual size_t getOutputMessageSize() = 0;


private:

	void init();
};

#endif
