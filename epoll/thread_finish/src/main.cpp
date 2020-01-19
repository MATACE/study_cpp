#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <thread>

#include "lock_lazy_singleton.h"
#include "client.h"
#include "gloglog.h"

using namespace std;

void tcp_run()
{
    Client client;
    while (1) 
    {
        Sleep(5);
        LOG(INFO) << "Sleep 5s.";
    }
}

int main()
{
    // Init Gloglog.
    MyGlogLog mygloglog("Client", "INFO", "./log");

    // Add the socket param.
    LockLazySingleton* config_param = config_param->GetInstance();
    config_param->host_ = "192.168.101.114";
    config_param->port_ = 5075;
    config_param->heartbeat_ = true;

    std::thread tcp(tcp_run);
    tcp.detach();

    sleep(10);
    

    return 0;
}