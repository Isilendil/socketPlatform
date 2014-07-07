#export LD_LIBRARY_PATH="lib":$$LD_LIBRARY_PATH
all : MasterMain ServerTester1Main ClientTester1Main \
                 ServerQrobotMain ClientQrobotMain \
								 ServerCameraMain ClientCameraMain \
								 TextToSpeechMain SpeechToTextMain\
                 main

MasterMain : MasterMain.o Master.o Server.o 
	g++ -o MasterMain MasterMain.o Master.o Server.o 

MasterMain.o : MasterMain.cpp Master.h Server.h MasterMessage.h
	g++ -c MasterMain.cpp

Master.o : Master.cpp Master.h Server.h MasterMessage.h
	g++ -c Master.cpp

Server.o : Server.cpp Server.h MasterMessage.h
	g++ -c Server.cpp


ServerTester1Main : ServerTester1Main.o ServerTester1.o Server.o
	g++ -o ServerTester1Main ServerTester1Main.o ServerTester1.o Server.o

ServerTester1Main.o : ServerTester1Main.cpp ServerTester1.h Server.h ServerTester1Message.h MasterMessage.h
	g++ -c ServerTester1Main.cpp

ServerTester1.o : ServerTester1.cpp ServerTester1.h Server.h ServerTester1Message.h MasterMessage.h 
	g++ -c ServerTester1.cpp

Client.o : Client.cpp Client.h MasterMessage.h
	g++ -c Client.cpp

ClientTester1Main : ClientTester1Main.o ClientTester1.o Client.o
	g++ -o ClientTester1Main ClientTester1Main.o ClientTester1.o Client.o

ClientTester1Main.o : ClientTester1Main.cpp ClientTester1.h Client.h ServerTester1Message.h MasterMessage.h
	g++ -c ClientTester1Main.cpp

ClientTester1.o : ClientTester1.cpp ClientTester1.h Client.h ServerTester1Message.h MasterMessage.h
	g++ -c ClientTester1.cpp

ServerQrobotMain : ServerQrobotMain.o ServerQrobot.o Server.o
	g++ -o ServerQrobotMain ServerQrobotMain.o ServerQrobot.o Server.o \
	    -L"lib" -lqcontroller

ServerQrobotMain.o : ServerQrobotMain.cpp ServerQrobot.h Server.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ServerQrobotMain.cpp

ServerQrobot.o : ServerQrobot.cpp ServerQrobot.h Server.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ServerQrobot.cpp

ClientQrobotMain : ClientQrobotMain.o ClientQrobot.o Client.o
	g++ -o ClientQrobotMain ClientQrobotMain.o ClientQrobot.o Client.o

ClientQrobotMain.o : ClientQrobotMain.cpp ClientQrobot.h Client.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ClientQrobotMain.cpp

ClientQrobot.o : ClientQrobot.cpp ClientQrobot.h Client.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ClientQrobot.cpp

ServerCameraMain : ServerCameraMain.o ServerCamera.o Server.o
	g++ -o ServerCameraMain ServerCameraMain.o ServerCamera.o Server.o `pkg-config --libs opencv` 

ServerCameraMain.o : ServerCameraMain.cpp ServerCamera.h Server.h ServerCameraMessage.h MasterMessage.h
	g++ -c ServerCameraMain.cpp `pkg-config --cflags opencv`

ServerCamera.o : ServerCamera.cpp ServerCamera.h Server.h ServerCameraMessage.h MasterMessage.h
	g++ -c ServerCamera.cpp `pkg-config --cflags opencv` -std=c++11

ClientCameraMain : ClientCameraMain.o ClientCamera.o Client.o
	g++ -o ClientCameraMain ClientCameraMain.o ClientCamera.o Client.o

ClientCameraMain.o : ClientCameraMain.cpp ClientCamera.h Client.h ServerCameraMessage.h MasterMessage.h
	g++ -c ClientCameraMain.cpp

ClientCamera.o : ClientCamera.cpp ClientCamera.h Client.h ServerCameraMessage.h MasterMessage.h
	g++ -c ClientCamera.cpp

main : main.o MainClient.o Client.o
	g++ -o main main.o MainClient.o Client.o

main.o : main.cpp MainClient.h Client.h ServerCameraMessage.h ServerTester1Message.h MasterMessage.h TextToSpeechMessage.h SpeechToTextMessage.h ServerlibraryMessage.h
	g++ -c main.cpp

MainClient.o : MainClient.cpp MainClient.h Client.h ServerCameraMessage.h ServerTester1Message.h MasterMessage.h TextToSpeechMessage.h SpeechToTextMessage.h ServerQrobotMessage.h
	g++ -c MainClient.cpp

TextToSpeechMain : TextToSpeech.o Server.o sndwav_common.o wav_parser.o
	g++ -o TextToSpeechMain TextToSpeech.o Server.o sndwav_common.o wav_parser.o -L"lib" -lmsc -ldl -lrt -lasound

TextToSpeech.o : TextToSpeech.cpp TextToSpeech.h Server.h TextToSpeechMessage.h MasterMessage.h
	g++ -c TextToSpeech.cpp -Wno-write-strings

SpeechToTextMain : SpeechToText.o Server.o sndwav_common.o wav_parser.o
	g++ -o SpeechToTextMain SpeechToText.o Server.o sndwav_common.o wav_parser.o -L"lib" -lmsc -ldl -lrt -lasound

SpeechToText.o : SpeechToText.cpp SpeechToText.h Server.h SpeechToTextMessage.h MasterMessage.h
	g++ -c SpeechToText.cpp -Wno-write-strings

sndwav_common.o : sndwav_common.cpp sndwav_common.h wav_parser.h
	g++ -c sndwav_common.cpp -Wno-write-strings

wav_parser.o : wav_parser.cpp wav_parser.h
	g++ -c wav_parser.cpp -Wno-write-strings

clean : 
	rm Server.o Client.o \
	   MasterMain MasterMain.o Master.o \
	   ServerTester1Main ServerTester1Main.o ServerTester1.o \
		 ClientTester1Main ClientTester1Main.o ClientTester1.o \
		 ServerQrobotMain ServerQrobotMain.o ServerQrobot.o \
		 ClientQrobotMain ClientQrobotMain.o ClientQrobot.o \
		 ServerCameraMain ServerCameraMain.o ServerCamera.o \
		 ClientCameraMain ClientCameraMain.o ClientCamera.o \
		 TextToSpeechMain TextToSpeech.o \
		 SpeechToTextMain SpeechToText.o \
		 sndwav_common.o wav_parser.o \
		 main main.o MainClient.o
