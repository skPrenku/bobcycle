#include "Client.h"
#include "usb.h"
#include "network.h"

Client::Client() {

    const DWORD usrNameSize = 32;
    const DWORD pcNameSize = 32;
    char usrName[usrNameSize];
    char pcName[pcNameSize];

    bool iRes = false;

    iRes = GetComputerNameA((LPSTR)&pcName, (LPDWORD)&pcNameSize);
    if (iRes)
    {
       this->computerName = pcName;
  
    }
        //  printf("Error getting PC name");

    iRes = GetUserNameA((LPSTR)&usrName, (LPDWORD)&usrNameSize);
  
    if (iRes)
    {
        this->userName = usrName;
    }


     disks = displayDisks().c_str();
     ip = getIPv4("").c_str();


}
