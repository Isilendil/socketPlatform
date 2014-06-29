//ClientQrobot.h
//class ClientQrobot

#include "Client.h"
#include "ServerQrobotMessage.h"

#ifndef _CLIENTQROBOT_H_
#define _CLIENTQROBOT_H_

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
