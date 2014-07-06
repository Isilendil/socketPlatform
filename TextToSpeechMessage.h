//TextToSpeech.h
//class InputTextToSpeechMessage
//class OutputTextToSpeechMessage

#ifndef _TEXTTOSPEECHMESSAGE_H_
#define _TEXTTOSPEECHMESSAGE_H_

struct InputTextToSpeechMessage
{
	char str[1024*4];
};

struct OutputTextToSpeechMessage
{
	bool ret;
};

#endif
