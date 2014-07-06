//TextToSpeech.h
//class InputTextToSpeechMessage
//class OutputTextToSpeechMessage

#ifndef _SPEECHTOTEXTMESSAGE_H_
#define _SPEECHTOTEXTMESSAGE_H_

struct InputSpeechToTextMessage
{
	bool input;
};

struct OutputSpeechToTextMessage
{
	char result[100];
};

#endif
