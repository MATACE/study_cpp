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
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/asio/steady_timer.hpp>
#include <glog/logging.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <thread>

#include "lock_lazy_singleton.h"
#include "data_queue.h"

using namespace std;

#define MAX_EVENTS 10
#define MAX_BUF_SIZE 1024
#define EPOLL_LISTEN_TIME 100
#define MAX_RETRY_TIME 3

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

    void StartSendPackage();
    void HandleSendPackage();
    void SendPackage(int& send_num, string send_line);

    void StartSendheartbeat();
    void HandSendHeartbeat(const boost::system::error_code &ec, boost::asio::steady_timer* pt);
    void SendHeartbeat(int& send_num, string send_line);

    void ParsePackage(string line);

    bool RegexWholePackage(string input_buffer, std::size_t& n);

private:
    int socket_client_fd_;
    struct sockaddr_in server_addr_;
    int nfds_;
    int epoll_fd_;
    struct epoll_event epoll_event_;
    struct epoll_event events[MAX_EVENTS];

    char recv_buf[MAX_BUF_SIZE];
    std::string input_buffer_;

    typedef std::map<std::string, pthread_t> ThreadMap;
    ThreadMap tm_;

    bool stop_;
    bool retry_connect_successful_;
    long long timeout_cout_;
    long long timeout_cout_max_;

};

#endif // CLIENT_H