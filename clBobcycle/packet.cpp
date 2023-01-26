#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "packet.h"
#include "network.h"
#include <WinSock2.h>
#include <iostream>
#define CMD_BUFFERHDR 4






	 int  Packet::sendPacket(const std::string& packetBody, Packet::Type packetType, SOCKET srvSocket) {

		if (packetBody.empty())
			return -1;

		int iRes = 0;
		char packetHdr[CMD_BUFFERHDR] = { 'b','o','b',(char)packetType };
		std::uint32_t packetSize = static_cast<std::uint32_t>(htonl(packetBody.size()));

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



	 

 std::uint16_t Packet::recvPacket(SOCKET srvSocket) {
		int iRes = 0;
		std::uint16_t cmdBuffer;
		iRes = recv(srvSocket, (char*)&cmdBuffer, sizeof(cmdBuffer), 0);
		if (iRes > 0)
		{
			switch ((Packet::Type)ntohs(cmdBuffer))
			{
			case Packet::Type::clip_data:
				network::_sendClipbord(); //sends clipb to srv
				break;
			case Packet::Type::hw_data:
				network::_sendHWSpecs(); //sends hw/specs to srv
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

			return 0;
		}

		return WSAGetLastError();
	}





