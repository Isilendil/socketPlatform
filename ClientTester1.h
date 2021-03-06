//ClientTester1.h
//class ClientTester1

#ifndef _CLIENTTEST1_H_
#define _CLIENTTEST1_H_

#include "Client.h"
#include "ServerTester1Message.h"

class ClientTester1 : public Client
{
public:
  ClientTester1();
	~ClientTester1();

  void run();

protected:
  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
  OutputServerTester1Message *myInput;
	InputServerTester1Message *myOutput;

};

#endif
