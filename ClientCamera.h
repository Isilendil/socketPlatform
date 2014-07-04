//ClientCamera.h
//class ClientCamera

#include "Client.h"
#include "ServerCameraMessage.h"

#ifndef _CLIENTCAMERA_H_
#define _CLIENTCAMERA_H_

class ClientCamera : public Client
{
public:
	ClientCamera();
	~ClientCamera();

	void run();

protected:
  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
  OutputServerCameraMessage *myInput;
	InputServerCameraMessage *myOutput;

};

#endif

