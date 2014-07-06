#include "TextToSpeech.h"

int text_to_speech(const char* src_text ,const char* des_path ,const char* params)
{
	struct wave_pcm_hdr pcmwavhdr = default_pcmwavhdr;
	const char* sess_id = NULL;
	int ret = 0;
	unsigned int text_len = 0;
	char* audio_data;
	unsigned int audio_len = 0;
	int synth_status = 1;
	FILE* fp = NULL;

	printf("begin to synth...\n");
	if (NULL == src_text || NULL == des_path)
	{
		printf("params is null!\n");
		return -1;
	}
	text_len = (unsigned int)strlen(src_text);
	fp = fopen(des_path,"wb");
	if (NULL == fp)
	{
		printf("open file %s error\n",des_path);
		return -1;
	}
	sess_id = QTTSSessionBegin(params, &ret);
	if ( ret != MSP_SUCCESS )
	{
		printf("QTTSSessionBegin: qtts begin session failed Error code %d.\n",ret);
		return ret;
	}

	ret = QTTSTextPut(sess_id, src_text, text_len, NULL );
	if ( ret != MSP_SUCCESS )
	{
		printf("QTTSTextPut: qtts put text failed Error code %d.\n",ret);
		QTTSSessionEnd(sess_id, "TextPutError");
		return ret;
	}
	fwrite(&pcmwavhdr, sizeof(pcmwavhdr) ,1, fp);
	while (1) 
	{
		const void *data = QTTSAudioGet(sess_id, &audio_len, &synth_status, &ret);
		if (NULL != data)
		{
		   fwrite(data, audio_len, 1, fp);
		   pcmwavhdr.data_size += audio_len;//修正pcm数据的大小
		}
		if (synth_status == 2 || ret != 0) 
		break;
	}

	//修正pcm文件头数据的大小
	pcmwavhdr.size_8 += pcmwavhdr.data_size + 36;

	//将修正过的数据写回文件头部
	fseek(fp, 4, 0);
	fwrite(&pcmwavhdr.size_8,sizeof(pcmwavhdr.size_8), 1, fp);
	fseek(fp, 40, 0);
	fwrite(&pcmwavhdr.data_size,sizeof(pcmwavhdr.data_size), 1, fp);
	fclose(fp);

	ret = QTTSSessionEnd(sess_id, NULL);
	if ( ret != MSP_SUCCESS )
	{
	printf("QTTSSessionEnd: qtts end failed Error code %d.\n",ret);
	}
	return ret;
}
  
void SNDWAV_Play(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd)  
{  
    int load, ret;  
    off64_t written = 0;  
    off64_t c;  
    off64_t count = LE_INT(wav->chunk.length);  
  
    load = 0;  
    while (written < count) {  
        /* Must read [chunk_bytes] bytes data enough. */  
        do {  
            c = count - written;  
            if (c > sndpcm->chunk_bytes)  
                c = sndpcm->chunk_bytes;  
            c -= load;  
  
            if (c == 0)  
                break;  
            ret = SNDWAV_P_SaveRead(fd, sndpcm->data_buf + load, c);  
            if (ret < 0) {  
                fprintf(stderr, "Error safe_read/n");  
                exit(-1);  
            }  
            if (ret == 0)  
                break;  
            load += ret;  
        } while ((size_t)load < sndpcm->chunk_bytes);  
  
        /* Transfer to size frame */  
        load = load * 8 / sndpcm->bits_per_frame;  
        ret = SNDWAV_WritePcm(sndpcm, load);  
        if (ret != load)  
            break;  
          
        ret = ret * sndpcm->bits_per_frame / 8;  
        written += ret;  
        load = 0;  
    }  
}  
  
void play_wav()
{

    char *filename;  
    char *devicename = "default";  
    int fd;  
    WAVContainer_t wav;  
    SNDPCMContainer_t playback;  
        
    memset(&playback, 0x0, sizeof(playback));  
  
    filename = "test.wav";  
    fd = open(filename, O_RDONLY);  
    if (fd < 0) {  
        fprintf(stderr, "Error open [%s]/n", filename);  
    }  
      
    if (WAV_ReadHeader(fd, &wav) < 0) {  
        fprintf(stderr, "Error WAV_Parse [%s]/n", filename);  
        goto Err;  
    }  
  
    if (snd_output_stdio_attach(&playback.log, stderr, 0) < 0) {  
        fprintf(stderr, "Error snd_output_stdio_attach/n");  
        goto Err;  
    }  
  
    if (snd_pcm_open(&playback.handle, devicename, SND_PCM_STREAM_PLAYBACK, 0) < 0) {  
        fprintf(stderr, "Error snd_pcm_open [ %s]/n", devicename);  
        goto Err;  
    }  
  
    if (SNDWAV_SetParams(&playback, &wav) < 0) {  
        fprintf(stderr, "Error set_snd_pcm_params/n");  
        goto Err;  
    }  
    snd_pcm_dump(playback.handle, playback.log);  
  
    SNDWAV_Play(&playback, &wav, fd);  
  
    snd_pcm_drain(playback.handle);  
  
    close(fd);  
    free(playback.data_buf);  
    snd_output_close(playback.log);  
    snd_pcm_close(playback.handle);  
	  
		return;
   
          
Err:  
		close(fd);  
    if (playback.data_buf) free(playback.data_buf);  
    if (playback.log) snd_output_close(playback.log);  
    if (playback.handle) snd_pcm_close(playback.handle);  

}

TextToSpeech ::TextToSpeech()
{
	name = "TextToSpeech";

  myInput = new InputTextToSpeechMessage;
	myOutput = new OutputTextToSpeechMessage;

	inputMessage = myInput;
	outputMessage = myOutput;

	//myRegister();

	//APPID请勿随意改动
	const char* login_configs = " appid = 53acdd53, work_dir =   .  ";
	int ret = 0;
	
	//用户登录
	ret = MSPLogin(NULL, NULL, login_configs);
	if ( ret != MSP_SUCCESS )
	{
		printf("MSPLogin failed , Error code %d.\n",ret);
	}

	myRegister();
}

TextToSpeech :: ~TextToSpeech()
{
	delete myInput;
	delete myOutput;
	
	//退出登录
  MSPLogout();
}

void TextToSpeech :: work()
{

  const char* text  = "科大讯飞作为中国最大的智能语音技术提供商，在智能语音技术领域有着长期的研究积累，并在中文语音合成、语音识别、口语评测等多项技术上拥有国际领先的成果。";
	//const char*  filename = "text_to_speech_test.pcm";
	const char* filename = "test.wav";
	const char* param = "aue = speex-wb;3, vcn=xiaoyan,  spd = 50, vol = 50, tte = utf8";
	int ret = 0;
	char key = 0;

	//音频合成
	printf("\n\n\n%s\n\n\n\n", myInput->str);
	ret = text_to_speech(myInput->str,filename,param);
	//ret = text_to_speech(text,filename,param);
	if ( ret != MSP_SUCCESS )
	{
		printf("text_to_speech: failed , Error code %d.\n",ret);
	}
	
	play_wav();
}


size_t TextToSpeech :: getInputMessageSize()
{
	return sizeof(InputTextToSpeechMessage);
}

size_t TextToSpeech :: getOutputMessageSize()
{
	return sizeof(OutputTextToSpeechMessage);
}



int main(int argc, char* argv[])
{
	TextToSpeech exp;
	exp.serve();
	return 0;
}



