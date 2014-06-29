//ServerQrobot.h
//class ServerQrobot

#ifndef _SERVERQROBOT_H_
#define _SERVERQROBOT_H_

#include "Server.h"
#include "ServerQrobotMessage.h"

#include "include/QrobotController.h"

class ServerQrobot : public Server
{
public:
  ServerQrobot();
	~ServerQrobot();

	void work();

protected:
  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
	InputServerQrobotMessage *myInput;
	OutputServerQrobotMessage *myOutput;

  //qrobot::QrobotController &controller;
};

#endif
