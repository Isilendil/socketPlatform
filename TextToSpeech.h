//TextTospeech.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "./include/qtts.h"
#include "./include/msp_cmn.h"
#include "./include/msp_errors.h"

#include "Server.h"
#include "TextToSpeechMessage.h"

//play headers
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

typedef int SR_DWORD;
typedef short int SR_WORD ;

//音频头部格式
struct wave_pcm_hdr
{
	char            riff[4];                        // = "RIFF"
	SR_DWORD        size_8;                         // = FileSize - 8
	char            wave[4];                        // = "WAVE"
	char            fmt[4];                         // = "fmt "
	SR_DWORD        dwFmtSize;                      // = 下一个结构体的大小 : 16

	SR_WORD         format_tag;              // = PCM : 1
	SR_WORD         channels;                       // = 通道数 : 1
	SR_DWORD        samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	SR_DWORD        avg_bytes_per_sec;      // = 每秒字节数 : dwSamplesPerSec * wBitsPerSample / 8
	SR_WORD         block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	SR_WORD         bits_per_sample;         // = 量化比特数: 8 | 16

	char            data[4];                        // = "data";
	SR_DWORD        data_size;                // = 纯数据长度 : FileSize - 44 
} ;

//默认音频头部数据
struct wave_pcm_hdr default_pcmwavhdr = 
{
	{ 'R', 'I', 'F', 'F' },
	0,
	{'W', 'A', 'V', 'E'},
	{'f', 'm', 't', ' '},
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{'d', 'a', 't', 'a'},
	0  
};

class TextToSpeech : public Server
{
public:
  TextToSpeech();
	~TextToSpeech();


protected:
	void work();

  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
	InputTextToSpeechMessage *myInput;
	OutputTextToSpeechMessage *myOutput;

  //qrobot::QrobotController &controller;
};

//play struct
ssize_t SNDWAV_P_SaveRead(int fd, void *buf, size_t count)  
{  
    ssize_t result = 0, res;  
  
    while (count > 0) {  
        if ((res = read(fd, buf, count)) == 0)  
            break;  
        if (res < 0)  
            return result > 0 ? result : res;  
        count -= res;  
        result += res;  
        buf = (char *)buf + res;  
    }  
    return result;  
}  
  
