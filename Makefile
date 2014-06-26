all : MasterMain ServerTester1Main ClientTester1Main

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

clean : 
	rm Server.o Client.o \
	   MasterMain MasterMain.o Master.o \
	   ServerTester1Main ServerTester1Main.o ServerTester1.o \
		 ClientTester1Main ClientTester1Main.o ClientTester1.o
