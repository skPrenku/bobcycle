#pragma once
#include <iostream>
#include <WinSock2.h>
#include <list>

//client container



struct Client {

	Client(SOCKET clSck, std::string hwSpecs);
	SOCKET clSocket = INVALID_SOCKET;	
	std::string clientSpecs; //stores complete Client PC's information in a single string
};

static  std::list<struct Client> clientList;