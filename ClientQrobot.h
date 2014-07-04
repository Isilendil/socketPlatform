//ClientQrobot.h
//class ClientQrobot

#ifndef _CLIENTQROBOT_H_
#define _CLIENTQROBOT_H_

#include "Client.h"
#include "ServerQrobotMessage.h"

class ClientQrobot : public Client
{
public:
	ClientQrobot();
	~ClientQrobot();

	void run();

protected:
  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
  OutputServerQrobotMessage *myInput;
	InputServerQrobotMessage *myOutput;

};

#endif
