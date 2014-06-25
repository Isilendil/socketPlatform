//MasterMessage.h
//class InputMasterMessage
//class OutputMasterMessage

#ifndef _MASTERMESSAGE_H_
#define _MASTERMESSAGE_H_

typedef int TYPE;
const TYPE REGISTER = 0;
const TYPE LOOKUP = 1;

#include <cstring>

struct InputMasterMessage
{
	TYPE type;
	char className[20];
};

struct OutputMasterMessage
{
	int port;
};

#endif
