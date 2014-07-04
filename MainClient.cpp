//MainClient.cpp

MainClient::MainClient()
{
}

MainClient::~MainClient()
{
}

void MainClient::run()
{
	//开启摄像头
	//接收语音输入
	//查询书籍
	//获得结果
	//播放结果
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
			return sizeof(InpueServerCameraMessage);
		  break;
		case SERVERQROBOT:
			return sizeof(InpueServerQrobotMessage);
		  break;
		case SERVERTESTER1:
			return sizeof(InpueServerTester1Message);
		  break;
		default:
			return 0;
		  break;
		
	}
}



