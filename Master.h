//Master.h
//class Master

#ifndef _MASTER_H_
#define _MASTER_H_

#include "Server.h"
#include "MasterMessage.h"

#include <vector>

class ServerRecord
{
public:
  ServerRecord(std::string p1, key_t p2, key_t p3) 
	  : className(p1), inputMemoryKey(p2), outputMemoryKey(p3) {}
  std::string className;
	key_t inputMemoryKey;
	key_t outputMemoryKey;
};


class Master : public Server
{
public:
  Master();
  ~Master();
	
	void serverRegister(std::string className);
	void serverLookup(std::string className);
  
  void run();

protected:
  std::vector<ServerRecord> serverInformation;

private:
  InputMasterMessage* inputMemory;
	OutputMasterMessage* outputMemory;

	static int count;

	size_t getInputMessageSize();
	size_t getOutputMessageSize();

};

#endif
