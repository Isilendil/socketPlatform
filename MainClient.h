//MainClient.h
//class MainClient

#ifndef _MAIN_CLIENT_H
#define _MAIN_CLIENT_H_

#include "Client.h"

#include "ServerTester1Message.h"
#include "ServerCameraMessage.h"
#include "ServerQrobotMessage.h"
//#include "ServerQrobotMessage.h"
#include "TextToSpeechMessage.h"
#include "ServerlibraryMessage.h"

/*
 * struct InputServerTester1Message
 * {
 *   int a;
 *   char b[10];
 * };
 *
 * struct OutputServerTester1Message
 * {
 *   int c;
 *   char d[10];
 * };
 *
 * struct InputServerQrobotMessage
 * {
 *   CommandType commandName;
 *   int parameters[3];
 * };
 *
 * struct OutputServerQrobotMessage
 * {
 *   int returnValues[2];
 * };
 *
 * struct InputServerCameraMessage
 * {
 *   CommandType commandName;
 *   char parameters[20];
 * };
 *
 * struct OutputServerCameraMessage
 * {
 *   int returnValues[2];
 * };
 *
 * struct InputTextToSpeechMessage
 * {
 *   char str[20];
 * };
 *
 * struct OutputTextToSpeechMessage
 * {
 *   bool ret;
 * };
 */

enum ServerType
{
	SERVERCAMERA,
	SERVERQROBOT,
	SERVERTESTER1,
	TEXTTOSPEECH,
	SERVERLIBRARY
};

class MainClient : public Client
{
public:
  MainClient();
	~MainClient();

	void run();

protected:
  size_t getInputMessageSize();
	size_t getOutputMessageSize();

private:
  ServerType type;


};

#endif
