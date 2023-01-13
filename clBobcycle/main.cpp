#define _CRT_SECURE_NO_WARNINGS

#include "packet.h"

#include "audio.h"

using namespace std;



int main()
{
	//displayDisks();

	//audio::liveStream();

	Packet test =
	
	makePacket("sdf",Packet::Type::clip_data);

	cout << test.buffer;








	return 0;
}
