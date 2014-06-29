//ServerQrobotMessage.h
//class InputServerQrobotMessage
//class OutputServerQrobotMessage

#ifndef _SERVERQROBOTMESSAGE_H_
#define _SERVERQROBOTMESSAGE_H_

enum CommandType
{
	Reset = 0,
	LeftWingUp = 1,
	LeftWingDown = 2,
	LeftWingOrg = 3,
	RightWingUp = 4,
	RightWingDown = 5,
	RightWingOrg = 6,
	HorizontalHead = 7,
	HorizontalHeadOrg = 8,
	VerticalHead = 9,
	VerticalHeadOrg = 10,
	Heart = 11,
	Eye = 12,
	SetPowerState = 13,
	Query = 14,
	GetHeadPosition = 15
};

struct InputServerQrobotMessage
{
	CommandType commandName;
	int parameters[3];
};

struct OutputServerQrobotMessage
{
	int returnValues[2];
};

#endif
