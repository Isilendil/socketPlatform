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
	
	myLookup("ServerCamera");
	type = SERVERCAMERA;
	outputMessage = new InputServerCameraMessage;
	inputMessage = new OutputServerCameraMessage;
	((InputServerCameraMessage*)outputMessage)->commandName = getcamera;
	request();
	delete (InputServerCameraMessage*)outputMessage;
	delete (OutputServerCameraMessage*)inputMessage;
	

	

	
	//接收语音输入
	//char bookName[25] = "machine learning";
	myLookup("SpeechToText");
	type = SPEECHTOTEXT;
	outputMessage = new InputSpeechToTextMessage;
	inputMessage = new OutputSpeechToTextMessage;
	((InputSpeechToTextMessage*)outputMessage)->input = true;
	request();
	std::string bookName = string(((OutputSpeechToTextMessage*)inputMessage)->result);
	cout << string(((OutputSpeechToTextMessage*)inputMessage)->result);
	delete (InputSpeechToTextMessage*)outputMessage;
	delete (OutputSpeechToTextMessage*)inputMessage;
	

	

	
	//查询书籍
	//char *bookName = "人工智能";
	char path[100];
	myLookup("Serverlibrary");
	type = SERVERLIBRARY;
	outputMessage = new InputServerlibraryMessage;
	inputMessage = new OutputServerlibraryMessage;
	((InputServerlibraryMessage*)outputMessage)->commandName = searchbookbytitle;
	strcpy(((InputServerlibraryMessage*)outputMessage)->book, bookName.c_str());
	cout << string(((InputServerlibraryMessage*)outputMessage)->book) << endl;
	request();
	strcpy(path, ((OutputServerlibraryMessage*)inputMessage)->path);
	delete (InputServerlibraryMessage*)outputMessage;
	delete (OutputServerlibraryMessage*)inputMessage;

	//获得结果
	cout << string(path) << endl;
	ifstream input(path);
	std::string content;

	/*
	while(input >> content)
	{
		cout << content << endl;
	}
	*/

	//播放结果
  	
	myLookup("TextToSpeech");
	type = TEXTTOSPEECH;
	outputMessage = new InputTextToSpeechMessage;
	inputMessage = new OutputTextToSpeechMessage;

  while(input >> content)
	{
	strcpy(((InputTextToSpeechMessage*)outputMessage)->str, content.c_str());
	request();
	cout << ((OutputTextToSpeechMessage*)inputMessage)->ret << endl;
	}
	delete (InputTextToSpeechMessage*)outputMessage;
	delete (OutputTextToSpeechMessage*)inputMessage;
	
	
	input.close();

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
		case SPEECHTOTEXT:
		  return sizeof(OutputSpeechToTextMessage);
			break;
		case SERVERLIBRARY:
		  return sizeof(OutputServerlibraryMessage);
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
		case SPEECHTOTEXT:
		  return sizeof(InputSpeechToTextMessage);
			break;
		case SERVERLIBRARY:
		  return sizeof(InputServerlibraryMessage);
			break;
		default:
			return 0;
		  break;
		
	}
}



