#include "Client.h"

Client::Client(SOCKET clSck, std::string hwSpecs) : clSocket{ clSck } {
	if (!hwSpecs.empty())
	{
		clientSpecs = hwSpecs;
	}
}