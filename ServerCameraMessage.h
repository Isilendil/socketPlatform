//ServerCameraMessage.h
//class InputServerCameraMessage
//class OutputServerCameraMessage

#ifndef _SERVERQROBOTMESSAGE_H_
#define _SERVERQROBOTMESSAGE_H_

enum CommandType
{
	getcamera=0,
        getpicture=1,
  	cutimage=2,
  	movedetect=3
};

struct InputServerCameraMessage
{
	CommandType commandName;
	char parameters[20];
};

struct OutputServerCameraMessage
{
	int returnValues[2];
};

#endif

