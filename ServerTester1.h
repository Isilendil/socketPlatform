//ServerTester.h
//class ServerTester1

#ifndef _SERVERTESTER1_H_
#define _SERVERTESTER1_H_

#include "Server.h"

#include "ServerTester1Message.h"

class ServerTester1 : public Server
{
public:
  ServerTester1();
	~ServerTester1();


protected:
	void work();

  size_t getInputMessageSize();
  size_t getOutputMessageSize();

private:
  InputServerTester1Message *myInput;
	OutputServerTester1Message *myOutput;

};



#endif
