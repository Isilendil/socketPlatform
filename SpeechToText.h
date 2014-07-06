//SpeechToText.h


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/qisr.h"
#include "./include/msp_cmn.h"
#include "./include/msp_errors.h"

#include "Server.h"
#include "SpeechToTextMessage.h"

//record
#include <malloc.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <ctype.h>  
#include <errno.h>  
#include <limits.h>  
#include <time.h>  
#include <locale.h>  
#include <sys/unistd.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <alsa/asoundlib.h>  
#include <assert.h>  
#include "wav_parser.h"  
#include "sndwav_common.h"  
  
#define DEFAULT_CHANNELS         (2)  
#define DEFAULT_SAMPLE_RATE      (8000)  
#define DEFAULT_SAMPLE_LENGTH    (16)  
#define DEFAULT_DURATION_TIME    (10)  

typedef int SR_DWORD;
typedef short int SR_WORD ;




class SpeechToText : public Server
{
public:
  SpeechToText();
	~SpeechToText();


protected:
	void work();

  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
	InputSpeechToTextMessage *myInput;
	OutputSpeechToTextMessage *myOutput;

  //qrobot::QrobotController &controller;
};

