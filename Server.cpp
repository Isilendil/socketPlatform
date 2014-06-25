//Server.cpp

#include "Server.h"

#include <cstring>
#include <unistd.h>

using namespace std;

Server::Server()
{
	init();
}

Server::~Server()
{
}

key_t Server::getInputMemoryKey()
{
	return inputMemoryKey;
}

key_t Server::getOutputMemoryKey()
{
	return outputMemoryKey;
}

void Server::setInputMemoryKey(key_t key)
{
	inputMemoryKey = key;
}

void Server::setOutputMemoryKey(key_t key)
{
	outputMemoryKey = key;
}

void Server::init()
{
}

void Server::myRegister()
{
	key_t masterInputMemoryKey = ftok("Master.h", 0);
	int masterInputMemoryId = shmget(987, sizeof(InputMasterMessage), 0600);
	//int masterInputMemoryId = shmget(masterInputMemoryKey, sizeof(InputMasterMessage), 0600);
	InputMasterMessage *masterInputMemory = (InputMasterMessage*)shmat(masterInputMemoryId, 0, 0);

	key_t masterOutputMemoryKey = ftok("Master.cpp", 0);
	int masterOutputMemoryId = shmget(987, sizeof(OutputMasterMessage), 0600);
	//int masterOutputMemoryId = shmget(masterOutputMemoryKey, sizeof(OutputMasterMessage), 0600);
	OutputMasterMessage *masterOutputMemory = (OutputMasterMessage*)shmat(masterOutputMemoryId, 0, 0);

  if(masterInputMemory->clean)
	{
		cout << "clean" << endl;
		cout << SERVER << endl;
    masterInputMemory->senderType = SERVER;
		cout << name << endl;
	  strcpy(masterInputMemory->className, name.c_str());
		cout << false << endl;
		masterInputMemory->clean = false;
	}

	sleep(1);

  if(!masterOutputMemory->clean)
	{
    inputMemoryKey = masterOutputMemory->inputMemoryKey;
	  outputMemoryKey = masterOutputMemory->outputMemoryKey;
		masterOutputMemory->clean = true;
	}

	inputMemoryId = shmget(inputMemoryKey, getInputMessageSize(), 0600|IPC_CREAT);
	inputMemory = shmat(inputMemoryId, 0, 0);

	outputMemoryId = shmget(outputMemoryKey, getOutputMessageSize(), 0600|IPC_CREAT);
	outputMemory = shmat(outputMemoryId, 0, 0);



		cout << masterOutputMemory->clean << endl;
	  cout << inputMemoryKey << '\t' << inputMemoryId << endl;
	  cout << outputMemoryKey << '\t' << outputMemoryId << endl;
}



