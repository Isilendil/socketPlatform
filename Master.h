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
  ServerRecord(std::string className_, int port_) 
	  : className(className_), port(port_) {}
  std::string className;
	int port;
};


class Master : public Server
{
public:
  Master();
  ~Master();
	
	int serverRegister(std::string className);
	int clientLookup(std::string className);
  

protected:
  void work();

	size_t getInputMessageSize();
	size_t getOutputMessageSize();

  std::vector<ServerRecord> serverInformation;

private:
	static int count;

  InputMasterMessage *myInput;
	OutputMasterMessage *myOutput;

};

#endif
