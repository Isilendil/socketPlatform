all : MasterMain ServerTester1Main

MasterMain : MasterMain.o Master.o Server.o SharedMemory.o
	g++ -o MasterMain MasterMain.o Master.o Server.o SharedMemory.o

MasterMain.o : MasterMain.cpp Master.h Server.h MasterMessage.h
	g++ -c MasterMain.cpp

Master.o : Master.cpp Master.h Server.h MasterMessage.h
	g++ -c Master.cpp

Server.o : Server.cpp Server.h MasterMessage.h
	g++ -c Server.cpp

SharedMemory.o : SharedMemory.cpp SharedMemory.h
	g++ -c SharedMemory.cpp

ServerTester1Main : ServerTester1Main.o ServerTester1.o Server.o
	g++ -o ServerTester1Main ServerTester1Main.o ServerTester1.o Server.o

ServerTester1Main.o : ServerTester1Main.cpp ServerTester1.h Server.h ServerTester1Message.h Master.h MasterMessage.h
	g++ -c ServerTester1Main.cpp

ServerTester1.o : ServerTester1.cpp ServerTester1.h Server.h ServerTester1Message.h MasterMessage.h Master.h MasterMessage.h
	g++ -c ServerTester1.cpp

clean : 
	rm MasterMain MasterMain.o Master.o Server.o \
	   ServerTester1Main ServerTester1Main.o ServerTester1.o
