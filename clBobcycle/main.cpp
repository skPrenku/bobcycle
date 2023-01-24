#define _CRT_SECURE_NO_WARNINGS
#include "Client.h"
#include "packet.h"
#include "usb.h"
#include "audio.h"
#include "network.h"
using namespace std;



int main()
{
	//displayDisks();

	//audio::liveStream();

	//Packet test =
	
	//makePacket("sdf",Packet::Type::clip_data);

	//cout << test.buffer;

	//wsaWrapper wsa;
	std::cout << "started client\n";
	network::_connect("localhost", 27015);

	//Client cl;
	




	return 0;
}
