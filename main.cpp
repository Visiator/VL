


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


#include "NET/NET.h"
#include "GUI/GUIlowlevel.h"
#include "GUI/GUI.h"
#include "ClientManager/ClientManager.h"
#include "Viewer.h"


std::unique_ptr<ClientManager> g_ClientManager;
std::unique_ptr<Viewer> g_Viewer;




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

int g_1 = 0;
#ifdef __linux__

//void *SigCatcher(int n)
//{
//  wait3(NULL,WNOHANG,NULL);
//}



    
    //boost::array<int, 4> arr = {{1,2,3,4}};
    
    //signal(SIGCHLD,SigCatcher);
    
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
    //g_Net = std::make_unique<NET>();
    g_ClientManager = std::make_unique<ClientManager>(gui);
    g_Viewer = std::make_unique<Viewer>(gui);
    
    g_ClientManager->run();
    //clientManager.reset();
    
    g_Viewer->start();
    
    //g_ClientManager->wait();
    //g_Viewer->wait();
    
    //g_ClientManager->stop();
    //g_Viewer->stop();
    
    
    gui->window_list->wait();
    //g_Net->set_need_stop();
    //g_Net->wait_stop();
    printf("stop\n");
    return;
}

