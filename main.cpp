
#ifdef _WIN32

#define _WINSOCKAPI_ 
#include <windows.h>
#undef _WINSOCKAPI_
#include <winsock2.h>
#include <stdlib.h>
#include <iphlpapi.h>
#include <stdio.h>
#undef _WINSOCKAPI_

#endif

#include <memory>
#include <stdio.h>
#include <cstdlib>

#include "GUI/GUIlowlevel.h"
#include "GUI/GUI.h"
#include "ClientManager/ClientManager.h"

std::unique_ptr<ClientManager> clientManager;


void _start_(
#ifdef _WIN32
    HINSTANCE hInstance
#endif
);

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    _start_(hInstance);
    return 0;
}
#endif


#ifdef __linux__
int main(int argc, char** argv)
{
    _start_();
}
#endif

void _start_(
#ifdef _WIN32
    HINSTANCE hInstance
#endif
)
{
    std::shared_ptr<GUI> gui = std::make_shared<GUI>();
#ifdef _WIN32
    gui->hInstance = hInstance;
#endif    
    clientManager = std::make_unique<ClientManager>(gui);
    
    clientManager->run();
    //clientManager.reset();
    
    clientManager->wait();
    
    clientManager->stop();
    
    //gui.reset();
    
    printf("stop\n");
    return;
}

