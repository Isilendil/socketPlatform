//Master.cpp

#include "Master.h"

using namespace std;

int Master::count = 1;

Master::Master()
{
	name = "Master";


  //inputMemory = new InputMasterMessage;
	inputMemoryKey = ftok("Master.h", 0);
	//inputMemoryId = shmget(inputMemoryKey, sizeof(InputMasterMessage), 0666|IPC_CREAT);
	inputMemoryId = shmget(987, sizeof(InputMasterMessage), 0666|IPC_CREAT);
	inputMemory = (InputMasterMessage*)shmat(inputMemoryId, 0, 0);
	inputMemory->clean = true;

	outputMemoryKey = ftok("Master.cpp", 0);
	outputMemoryId = shmget(987, sizeof(OutputMasterMessage), 0666|IPC_CREAT);
	//outputMemoryId = shmget(outputMemoryKey, sizeof(OutputMasterMessage), 0666|IPC_CREAT);
	outputMemory = (OutputMasterMessage*)shmat(outputMemoryId, 0, 0);
	outputMemory->clean = true;
}

Master::~Master()
{
}

size_t Master::getInputMessageSize()
{
	return sizeof(InputMasterMessage);
}

size_t Master::getOutputMessageSize()
{
	return sizeof(OutputMasterMessage);
}

void Master::serverRegister(string className)
{
	if(outputMemory->clean)
	{
		key_t temp1 = inputMemoryKey + count;
		key_t temp2 = outputMemoryKey + count;
		count ++;
		serverInformation.push_back(ServerRecord(className, temp1, temp2));
		outputMemory->inputMemoryKey = temp1;
		outputMemory->outputMemoryKey = temp2;
		outputMemory->clean = false;
		cout << outputMemory->inputMemoryKey << endl;
		cout << outputMemory->outputMemoryKey << endl;

		cout << "!!" << endl;
	}
}

void Master::serverLookup(string className)
{
	if(outputMemory->clean)
	{
		for(vector<ServerRecord>::iterator iter = serverInformation.begin();
		  iter != serverInformation.end(); ++iter)
		{
			if(iter->className == className)
		  {
		    outputMemory->inputMemoryKey = iter->inputMemoryKey;
		    outputMemory->outputMemoryKey = iter->outputMemoryKey;
		    outputMemory->clean = false;
			  return;
		  }
		}
		outputMemory->inputMemoryKey = -1;
		outputMemory->outputMemoryKey = -1;
		return;
	}
}

void Master::run()
{
	while(true)
	{
	  if(!inputMemory->clean)
	  {
			char temp[20];
			strcmp(temp, inputMemory->className);
			cout << "!" << endl;
		  if(inputMemory->senderType == SERVER)
		  {
				
        serverRegister(string(temp));
		  }
		  else if(inputMemory->senderType = CLIENT)
		  {
        serverLookup(string(temp));
		  }
		  inputMemory->clean = true;
	  }
	}
}
