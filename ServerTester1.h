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

	void run();

protected:
  size_t getInputMessageSize();
  size_t getOutputMessageSize();

private:

};



#endif
