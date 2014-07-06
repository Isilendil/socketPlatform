#include "SpeechToText.h"

void run_iat(const char* src_wav_filename ,  const char* param, char *result)
{
	char rec_result[100] = {0};
	const char *sessionID;
	FILE *f_pcm = NULL;
	char *pPCM = NULL;
	int lastAudio = 0 ;
	int audStat = 2 ;
	int epStatus = 0;
	int recStatus = 0 ;
	long pcmCount = 0;
	long pcmSize = 0;
	int ret = 0 ;
	
	sessionID = QISRSessionBegin(NULL, param, &ret);
    if (ret !=0)
	{
	    printf("QISRSessionBegin Failed,ret=%d\n",ret);
	}
	f_pcm = fopen(src_wav_filename, "rb");
	if (NULL != f_pcm) {
		fseek(f_pcm, 0, SEEK_END);
		pcmSize = ftell(f_pcm);
		fseek(f_pcm, 0, SEEK_SET);
		pPCM = (char *)malloc(pcmSize);
		fread((void *)pPCM, pcmSize, 1, f_pcm);
		fclose(f_pcm);
		f_pcm = NULL;
	}
	while (1) {
		unsigned int len = 6400;

		if (pcmSize < 12800) {
			len = pcmSize;
			lastAudio = 1;
		}
		audStat = 2;
		if (pcmCount == 0)
			audStat = 1;
		if (0) {
			if (audStat == 1)
				audStat = 5;
			else
				audStat = 4;
		}
		if (len<=0)
		{
			break;
		}
		printf("csid=%s,count=%d,aus=%d,",sessionID,pcmCount/len,audStat);
		ret = QISRAudioWrite(sessionID, (const void *)&pPCM[pcmCount], len, audStat, &epStatus, &recStatus);
		printf("eps=%d,rss=%d,ret=%d\n",epStatus,recStatus,ret);
		if (ret != 0)
			break;
		pcmCount += (long)len;
		pcmSize -= (long)len;
		if (recStatus == 0) {
			const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &ret);
			if (ret != MSP_SUCCESS)
			{
				printf("QISRGetResult Failed,ret=%d\n",ret);
				break;
			}
			if (NULL != rslt)
				printf("%s\n", rslt);
		}
		if (epStatus == MSP_EP_AFTER_SPEECH)
			break;
		usleep(150000);
	}
	ret=QISRAudioWrite(sessionID, (const void *)NULL, 0, 4, &epStatus, &recStatus);
	if (ret !=0)
	{
		printf("QISRAudioWrite Failed,ret=%d\n",ret);
	}
	free(pPCM);
	pPCM = NULL;
	while (recStatus != 5 && ret == 0) {
		const char *rslt = QISRGetResult(sessionID, &recStatus, 0, &ret);
		if (NULL != rslt)
		{
			strcat(rec_result,rslt);
		}
		usleep(150000);
	}
    ret=QISRSessionEnd(sessionID, NULL);
	if(ret !=MSP_SUCCESS)
	{
		printf("QISRSessionEnd Failed, ret=%d\n",ret);
	}

	printf("=============================================================\n");
	printf("The result is: %s\n",rec_result);
	printf("=============================================================\n");
	strcpy(result, rec_result);
	////////////////////
	FILE *fp = NULL;
 	fp = fopen("iat.txt", "w");
 	if (fp == NULL)
 	{
  	printf("Cann't open the file!");
  	exit(1);
	 }
 	else
 	{
  	fprintf(fp, "%s", rec_result);
  	fclose(fp);
 	}
	
	//////////////////
	usleep(100);
}



int SNDWAV_PrepareWAVParams(WAVContainer_t *wav)  
{  
    assert(wav);  
  
    uint16_t channels = DEFAULT_CHANNELS;  
    uint16_t sample_rate = DEFAULT_SAMPLE_RATE;  
    uint16_t sample_length = DEFAULT_SAMPLE_LENGTH;  
    uint32_t duration_time = DEFAULT_DURATION_TIME;  
  
    /* Const */  
    wav->header.magic = WAV_RIFF;  
    wav->header.type = WAV_WAVE;  
    wav->format.magic = WAV_FMT;  
    wav->format.fmt_size = LE_INT(16);  
    wav->format.format = LE_SHORT(WAV_FMT_PCM);  
    wav->chunk.type = WAV_DATA;  
  
    /* User definition */  
    wav->format.channels = LE_SHORT(channels);  
    wav->format.sample_rate = LE_INT(sample_rate);  
    wav->format.sample_length = LE_SHORT(sample_length);  
  
    /* See format of wav file */  
    wav->format.blocks_align = LE_SHORT(channels * sample_length / 8);  
    wav->format.bytes_p_second = LE_INT((uint16_t)(wav->format.blocks_align) * sample_rate);  
      
    wav->chunk.length = LE_INT(duration_time * (uint32_t)(wav->format.bytes_p_second));  
    wav->header.length = LE_INT((uint32_t)(wav->chunk.length) + sizeof(wav->chunk) + sizeof(wav->format) + sizeof(wav->header) - 8);  
  
    return 0;  
}  
  
void SNDWAV_Record(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd)  
{  
    off64_t rest;  
    size_t c, frame_size;  
      
    if (WAV_WriteHeader(fd, wav) < 0) {  
        exit(-1);  
    }  
  
    rest = wav->chunk.length;  
    while (rest > 0) {  
        c = (rest <= (off64_t)sndpcm->chunk_bytes) ? (size_t)rest : sndpcm->chunk_bytes;  
        frame_size = c * 8 / sndpcm->bits_per_frame;  
        if (SNDWAV_ReadPcm(sndpcm, frame_size) != frame_size)  
            break;  
          
        if (write(fd, sndpcm->data_buf, c) != c) {  
            fprintf(stderr, "Error SNDWAV_Record[write]/n");  
            exit(-1);  
        }  
  
        rest -= c;  
    }  
}  


void record()
{
    char *filename;  
    char *devicename = "default";  
    int fd;  
    WAVContainer_t wav;  
    SNDPCMContainer_t record;  
    
    memset(&record, 0x0, sizeof(record));  
 
    filename = "input";
    remove(filename);  
    if ((fd = open(filename, O_WRONLY | O_CREAT, 0644)) == -1) {  
        fprintf(stderr, "Error open: [%s]/n", filename);  
        return  ;  
    }  
  
    if (snd_output_stdio_attach(&record.log, stderr, 0) < 0) {  
        fprintf(stderr, "Error snd_output_stdio_attach/n");  
        goto Err;  
    }  
  
    if (snd_pcm_open(&record.handle, devicename, SND_PCM_STREAM_CAPTURE, 0) < 0) {  
        fprintf(stderr, "Error snd_pcm_open [ %s]/n", devicename);  
        goto Err;  
    }  
  
    if (SNDWAV_PrepareWAVParams(&wav) < 0) {  
        fprintf(stderr, "Error SNDWAV_PrepareWAVParams/n");  
        goto Err;  
    }  
  
    if (SNDWAV_SetParams(&record, &wav) < 0) {  
        fprintf(stderr, "Error set_snd_pcm_params/n");  
        goto Err;  
    }  
    snd_pcm_dump(record.handle, record.log);  
  
    SNDWAV_Record(&record, &wav, fd);  
  
    snd_pcm_drain(record.handle);  
  
    close(fd);  
    free(record.data_buf);  
    snd_output_close(record.log);  
    snd_pcm_close(record.handle);  
    return ;  
  
Err:  
    close(fd);  
    remove(filename);  
    if (record.data_buf) free(record.data_buf);  
    if (record.log) snd_output_close(record.log);  
    if (record.handle) snd_pcm_close(record.handle);  
    return ; 
}

SpeechToText ::SpeechToText()
{
	name = "SpeechToText";

  myInput = new InputSpeechToTextMessage;
	myOutput = new OutputSpeechToTextMessage;

	inputMessage = myInput;
	outputMessage = myOutput;


	//用户ID请勿更改
	const char* login_configs = "appid = 53acdd53, work_dir =   .  ";
	int ret=0;
	
	//用户登录
	ret = MSPLogin(NULL, NULL, login_configs);
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
	}

	myRegister();
}

SpeechToText :: ~SpeechToText()
{
	delete myInput;
	delete myOutput;
	
	//退出登录
  MSPLogout();
}

size_t SpeechToText :: getInputMessageSize()
{
	return sizeof(InputSpeechToTextMessage);
}

size_t SpeechToText :: getOutputMessageSize()
{
	return sizeof(OutputSpeechToTextMessage);
}

void SpeechToText::work()
{
	record();
	const char* param1 = "sub=iat,ssm=1,auf=audio/L16;rate=16000,aue=speex,ent=sms16k,rst=plain,rse=gb2312";//直接转写，默认编码为gb2312，可以通过rse参数指定为utf8或unicode
	const char* param2 = "sub=iat,ssm=1,auf=audio/L16;rate=16000,aue=speex,ent=sms16k,rst=json,rse=utf8";//转写为json格式，编码只能为utf8
	const char* output_file = "iat_result.txt";
	int ret = 0;
	char key = 0;
	//开始一路转写会话
	//run_iat("input.wav" ,  param1);                                     //iflytek09对应的音频内容“沉舟侧畔千帆过，病树前头万木春。”
	char result[100];
	run_iat("input.wav",  param2, result);                                     //iflytek01对应的音频内容“科大讯飞”
	//退出登录

}


int main(int argc, char* argv[])
{
	SpeechToText exp;
	exp.serve();
	return 0;
}



