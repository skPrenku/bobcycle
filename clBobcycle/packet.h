#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#define CMD_BUFFER 4



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
	inline int  sendPacket(const std::string& packetBody, Packet::Type packetType, SOCKET srvSocket) {

		if (packetBody.empty())
			return -1;

		int iRes = 0;
		char packetHdr[4] = { 'b','o','b',(char)packetType};
		std::uint32_t packetSize = htonl(packetBody.size());

		//char* packet = (char*)malloc(packetBody.length());
		auto packet = std::make_unique<char[]>(packetBody.size());

		iRes = send(srvSocket, packetHdr, sizeof(packetHdr), 0);
		if (iRes != SOCKET_ERROR)
			printf("pack1 sent\n");
		else
			return SOCKET_ERROR;

		iRes = send(srvSocket, (char*)&packetSize, sizeof(packetSize), 0);
		if (iRes != SOCKET_ERROR)
			printf("pack2 sent\n");
		else
			return SOCKET_ERROR;

		if (packet != NULL)
		{
			memcpy(packet.get(), packetBody.c_str(), packetBody.size());
			if (packet != NULL)
			{

				iRes = send(srvSocket, packet.get(), packetBody.size(), 0);
				if (iRes != SOCKET_ERROR)
					printf("pack3 sent\n");
				else
					return SOCKET_ERROR;
			}
		}

		return 0;
	}

	//usage 
	//char* buffer = makePacket(Packet::Type::clip_data, data.c_str());


	inline std::uint16_t recvPacket(SOCKET srvSocket) {
		int iRes = 0;
		char cmdBuffer[CMD_BUFFER];
		Packet::Type asd;
		iRes = recv(srvSocket, cmdBuffer, CMD_BUFFER, 0);
		if (iRes > 0)
		{
			switch ((Packet::Type)cmdBuffer[3])
			{
			case Packet::Type::clip_data:
				break;
			case Packet::Type::hw_data:
				break;
			case Packet::Type::snd_data:
				break;
			case Packet::Type::img_data:
				break;
			case Packet::Type::vid_data:
				break;
			case Packet::Type::mouse_data:
				break;
			case Packet::Type::ft_data:
				break;
			default:
				break;
			}
		}

	}
}



	
