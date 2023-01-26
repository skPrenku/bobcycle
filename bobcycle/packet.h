#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include "Client.h"

#define CMD_BUFFER 4


#include <list>




namespace Packet {
	enum class Type : std::int16_t {
		clip_data,
		hw_data,
		snd_data,
		img_data,
		vid_data,
		mouse_data,
		ft_data
	};	

};


inline int sendPacket(SOCKET clSocket, Packet::Type cmd) {

	int iRes = 0;
	std::uint16_t packetType = htons(static_cast<std::uint16_t>(cmd));
	iRes = send(clSocket, (char*)&packetType, sizeof(packetType), 0);
	if (iRes == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}

	return 0;
}


inline int recvPacket(SOCKET clSocket) {
	int iRes = 0;
	char bufferHdr[CMD_BUFFER];
	std::uint32_t bufferSize;


	iRes = recv(clSocket, bufferHdr, sizeof(bufferHdr), 0); //recive the header/ if header protocol is = 4bytes -> [b][o][b][packet::type], continue
	if (iRes > 0 || bufferHdr == "bob")
	{
		switch ((Packet::Type)bufferHdr[3])
		{
		case Packet::Type::clip_data:
		{
			iRes = recv(clSocket, (char*)&bufferSize, sizeof(bufferSize), 0); //recive the size for the command to follow , we need the size to dynamically allocate memory
			if (iRes > 0) {
				

				char* bufferPacket = new char[ntohl(bufferSize)];
				iRes = recv(clSocket, bufferPacket, bufferSize, 0); //finally recive the command 
				if (iRes > 0)
				{
					printf("\nClients Clipboard: %s\n", bufferPacket);
				}

				delete[]bufferPacket; //delete the pointer

			}
		}
		break;
		case Packet::Type::hw_data:
		{
			iRes = recv(clSocket, (char*)&bufferSize, sizeof(bufferSize), 0);
			if (iRes > 0) {

				char* bufferPacket = new char[ntohl(bufferSize)];
				std::uint32_t packetSize = ntohl(bufferSize);
				iRes = recv(clSocket, bufferPacket, packetSize, 0);
				if (iRes > 0 && iRes == packetSize)
				{

						printf("Packet Recived, \nType %d\nBytes: %d\nMsg: %s\n", bufferHdr[3], iRes,bufferPacket);
						clientList.push_back(Client(clSocket, bufferPacket));
			
					
				}

				delete[]bufferPacket;

			}

		}

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

	return 0;
}
