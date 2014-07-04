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
	const char*  filename = "text_to_speech_test.pcm";
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



