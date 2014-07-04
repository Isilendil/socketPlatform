//MainClient.cpp
#include "MainClient.h"

struct InputServerQrobotMessage
{
	CommandType commandName;
	int parameters[3];
};

struct OutputServerQrobotMessage
{
	int returnValues[2];
};


using namespace std;

MainClient::MainClient()
{
}

MainClient::~MainClient()
{
}

void MainClient::run()
{
	//开启摄像头
	//接收语音输入
	//查询书籍
	//获得结果
	//播放结果
	myLookup("TextToSpeech");
	type = TEXTTOSPEECH;
	outputMessage = new InputTextToSpeechMessage;
	inputMessage = new OutputTextToSpeechMessage;
	strcpy(((InputTextToSpeechMessage*)outputMessage)->str, "Miss Tan");
	request();
	cout << ((OutputTextToSpeechMessage*)inputMessage)->ret << endl;
	delete (InputTextToSpeechMessage*)outputMessage;
	delete (OutputTextToSpeechMessage*)inputMessage;

}

size_t MainClient::getInputMessageSize()
{
	switch(type)
	{
		case SERVERCAMERA:
			return sizeof(OutputServerCameraMessage);
		  break;
		case SERVERQROBOT:
			return sizeof(OutputServerQrobotMessage);
		  break;
		case SERVERTESTER1:
			return sizeof(OutputServerTester1Message);
		  break;
		case TEXTTOSPEECH:
		  return sizeof(OutputTextToSpeechMessage);
			break;
		default:
			return 0;
		  break;
		
	}
}

size_t MainClient::getOutputMessageSize()
{
	switch(type)
	{
		case SERVERCAMERA:
			return sizeof(InputServerCameraMessage);
		  break;
		case SERVERQROBOT:
			return sizeof(InputServerQrobotMessage);
		  break;
		case SERVERTESTER1:
			return sizeof(InputServerTester1Message);
		  break;
		case TEXTTOSPEECH:
		  return sizeof(InputTextToSpeechMessage);
			break;
		default:
			return 0;
		  break;
		
	}
}



