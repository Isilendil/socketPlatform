//ServerCamera.h
//class ServerCamera

#ifndef _SERVERQROBOT_H_
#define _SERVERQROBOT_H_

#include "Server.h"
#include "ServerCameraMessage.h"
#include "stdio.h"
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "opencv2/imgproc/imgproc.hpp" 
#include <iostream> 
#include <cstdio>   


class ServerCamera : public Server
{
public:
  ServerCamera();
	~ServerCamera();

	static bool flag;

protected:
	void work();
        bool get_camera();
  	bool get_picture();
  	bool cut_image(char* image);
  	bool move_detect();
        size_t getInputMessageSize();
	size_t getOutputMessageSize();

  //void waiting();

private:
	InputServerCameraMessage *myInput;
	OutputServerCameraMessage *myOutput;


  
  //qrobot::QrobotController &controller;
};

#endif
