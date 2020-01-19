#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>
#include <sys/epoll.h> 

#include <boost/regex.hpp>
#include <glog/logging.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <thread>

#include "lock_lazy_singleton.h"

using namespace std;

#define MAX_EVENTS 10
#define MAX_BUF_SIZE 1024

class Client
{
public:
    Client();
    virtual ~Client();

    void Start();
    void Stop();

    void StartConnect();
    void HandleConnect(int port, string host);

    void RetryConnect();
    void HandleRetryConnect();

    void StartRead();
    void HandleRead();

    void StartSend();
    void HandleSend();

private:
    int socket_client_fd_;
    struct sockaddr_in server_addr_;
    int nfds_;
    int epoll_fd_;
    struct epoll_event epoll_event_;
    struct epoll_event events[MAX_EVENTS];

    char buf[MAX_BUF_SIZE];
    std::string input_buffer_;

    typedef std::map<std::string, pthread_t> ThreadMap;
    ThreadMap tm_;

    bool retry_connect_;

};

#endif // CLIENT_H