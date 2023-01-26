#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#define CMD_BUFFERHDR 4



namespace Packet {
	enum class Type : std::uint16_t {

		clip_data,
		hw_data,
		snd_data,
		img_data,
		vid_data,
		mouse_data,
		ft_data
	};


	/*
	sendPacket() return codes
	-successful  returns 0
	-empty buffer returns -1
	else returns an error code from WSAGetlastError()
	*/
	int  sendPacket(const std::string& packetBody, Packet::Type packetType, SOCKET srvSocket);

	//recives the command from the server and handels it.
	std::uint16_t recvPacket(SOCKET srvSocket);
}



	
