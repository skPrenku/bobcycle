
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
struct Client {

	Client();

	std::string computerName ;
	std::string userName;
	std::string ip;
	std::string disks;
	std::string computerOS;
};
