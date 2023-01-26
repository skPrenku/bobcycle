#include "network.h"
#include "packet.h"


wsaWrapper::wsaWrapper() {

    res = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (res == 0) {
        printf("WSAStartup GOOD");
    }
    else {
        printf("Error initializing wsa: %d\n",WSAGetLastError());
    }
}

wsaWrapper::~wsaWrapper()
{
       WSACleanup();
}

using namespace network;

int network::_start_Server( short PORT) {


        wsaWrapper wsa;


    srvSOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (srvSOCKET == INVALID_SOCKET)
    {
        printf("Error creating socket %d\n", WSAGetLastError());

    }
    else {
        printf("Socket created successfully.\n");
    }

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_port = htons(PORT);
    srvAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    result = bind(srvSOCKET, (sockaddr*)&srvAddr, sizeof(srvAddr));
    if (result == SOCKET_ERROR)
    {
        printf("Error binding.. %d\n", WSAGetLastError());
    }
    else {
        printf("Binding socket, successful\n");
    }
    
    result = listen(srvSOCKET, 5);
    if (result == SOCKET_ERROR)
    {
        printf("Error listening ...%d\n", WSAGetLastError());
    }
    else {
        printf("Server started listening on port %d\n", PORT);
    }

    //test socket to send/recv data
   
    int recBytes = 0;
    int clAddrSize = sizeof(clAddr);
   


    std::cout << "waiting\n";
    while (true) {
       
       /*
       Loop accept clients and add them to the clientList
       manage multiple clients/sockets via select()
       sendPacket()
       recvPacket()
       */

    }
    //accepting loop
    return 0;
}


int network::_rcvClipbord() {

    return 0;
}
int network::_captureMic() {

    return 0;
}
int network::_rcvScrShot() {

    return 0;
}
int network::_rcvHWSpecs() {

    return 0;
}