#export LD_LIBRARY_PATH="lib":$$LD_LIBRARY_PATH
all : MasterMain ServerTester1Main ClientTester1Main \
                 ServerQrobotMain ClientQrobotMain

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

ServerQrobotMain.o : ServerQrobotMain.cpp ServerQrobot.o Server.o
	g++ -c ServerQrobotMain.cpp

ServerQrobot.o : ServerQrobot.cpp ServerQrobot.h Server.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ServerQrobot.cpp

ClientQrobotMain : ClientQrobotMain.o ClientQrobot.o Client.o
	g++ -o ClientQrobotMain ClientQrobotMain.o ClientQrobot.o Client.o

ClientQrobotMain.o : ClientQrobotMain.cpp ClientQrobot.h Client.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ClientQrobotMain.cpp

ClientQrobot.o : ClientQrobot.cpp ClientQrobot.h Client.h ServerQrobotMessage.h MasterMessage.h
	g++ -c ClientQrobot.cpp

clean : 
	rm Server.o Client.o \
	   MasterMain MasterMain.o Master.o \
	   ServerTester1Main ServerTester1Main.o ServerTester1.o \
		 ClientTester1Main ClientTester1Main.o ClientTester1.o \
		 ServerQrobotMain ServerQrobotMain.o ServerQrobot.o  \
		 ClientQrobotMain ClientQrobotMain.o ClientQrobot.o  
