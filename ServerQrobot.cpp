//ServerQrobot.cpp

#include "ServerQrobot.h"

using namespace std;
using namespace qrobot;

ServerQrobot::ServerQrobot()
{
	name = "ServerQrobot";

	myInput = new InputServerQrobotMessage;
	myOutput = new OutputServerQrobotMessage;

	inputMessage = myInput;
	outputMessage = myOutput;

  //QrobotController::Instance() = QrobotController::Instance();

	myRegister();
}

ServerQrobot::~ServerQrobot()
{
	delete myInput;
	delete myOutput;
}

size_t ServerQrobot::getInputMessageSize()
{
	return sizeof(InputServerQrobotMessage);
}

size_t ServerQrobot::getOutputMessageSize()
{
	return sizeof(OutputServerQrobotMessage);
}

void ServerQrobot::work()
{
  CommandType command = myInput->commandName;
	int p[3];
	p[0] = p[1] = p[2] = -1;
	p[0] = myInput->parameters[0];
	p[1] = myInput->parameters[1];
	p[2] = myInput->parameters[2];
	int *result = new int[2];
	result[0] = result[1] = -1;
	switch(command)
	{
		case Reset:
		  result[0] = QrobotController::Instance().Reset(); 
      break;
		case LeftWingUp:
		  result[0] = QrobotController::Instance().LeftWingUp(p[0], p[1]);
			break;
		case LeftWingDown:
		  result[0] = QrobotController::Instance().LeftWingDown(p[0], p[1]);
			break;
		case LeftWingOrg:
		  result[0] = QrobotController::Instance().LeftWingOrg(p[0]);
			break;
		case RightWingUp:
		  result[0] = QrobotController::Instance().RightWingUp(p[0], p[1]);
			break;
		case RightWingDown:
		  result[0] = QrobotController::Instance().RightWingDown(p[0], p[1]);
			break;
		case RightWingOrg:
		  result[0] = QrobotController::Instance().RightWingOrg(p[0]);
			break;
		case HorizontalHead:
		  result[0] = QrobotController::Instance().HorizontalHead(p[0], p[1]);
			break;
		case HorizontalHeadOrg:
		  result[0] = QrobotController::Instance().HorizontalHeadOrg(p[0]);
			break;
		case VerticalHead:
		  result[0] = QrobotController::Instance().VerticalHead(p[0], p[1]);
			break;
		case VerticalHeadOrg:
		  result[0] = QrobotController::Instance().VerticalHeadOrg(p[0]);
			break;
		case Heart:
		  result[0] = QrobotController::Instance().Heart(p[0], p[1], p[2]);
			break;
    case Eye:
		  result[0] = QrobotController::Instance().Eye(p[0], p[1]);
			break;
		case SetPowerState:
		  QrobotController::Instance().SetPowerState(p[0]);
			break;
    case Query:
		  result[0] = QrobotController::Instance().Query(p[0]);
			break;
		case GetHeadPosition:
		  result = QrobotController::Instance().GetHeadPosition();
			break;
    default:
		  break;
	}
  myOutput->returnValues[0] = result[0];
  myOutput->returnValues[1] = result[1];
	cout << myOutput->returnValues[0] << '\t' << myOutput->returnValues[1] << endl;
	delete result;
}
