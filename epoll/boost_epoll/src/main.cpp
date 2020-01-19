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
#include "dylibapi.h"

using namespace std;

void tcp_run()
{
    Client client;
    while (1) 
    {
        client.Start();
    }
}

int main()
{
    // Init Gloglog.
    MyGlogLog mygloglog("Client", "INFO", "./log");
    // Add boost regex.
    LoadDLL((char *)"libboost_regex.so.1.68.0");
	LoadDLL((char *)"libboost_system.so.1.68.0");
	LoadDLL((char *)"libboost_regex.so.1.68.0");

    // Add the socket param.
    LockLazySingleton* config_param = config_param->GetInstance();
    config_param->host_ = "192.168.101.114";
    config_param->port_ = 5075;
    config_param->heartbeat_ = true;
    config_param->heartbeat_timer_ = 5;
    config_param->heartbeat_package_ = "AA112233BB";

    std::thread tcp(tcp_run);
    tcp.detach();

    while (1) 
    {
        sleep(1);
    }

    return 0;
}