//MasterMessage.h
//class InputMasterMessage
//class OutputMasterMessage

#ifndef _MASTERMESSAGE_H_
#define _MASTERMESSAGE_H_

typedef int TYPE;
const TYPE SERVER = 0;
const TYPE CLIENT = 1;

#include <cstring>

struct InputMasterMessage
{
	TYPE senderType;
	char className[20];
	bool clean;
};

struct OutputMasterMessage
{
	key_t inputMemoryKey;
	key_t outputMemoryKey;
	bool clean;
};

#endif
