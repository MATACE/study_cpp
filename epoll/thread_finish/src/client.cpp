#include "client.h"

Client::Client()
{   
    retry_connect_ = false;
    Start();
}

Client::~Client()
{

}

void Client::Start()
{
    StartConnect();
}

void Client::Stop()
{

}

void Client::StartConnect()
{
    LOG(INFO) << "StartConnect()";
    // Create the socket to connect the server and set socket is unblocked.
    socket_client_fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (socket_client_fd_ < 0) {
        LOG(ERROR) << "Connect to server failed.";
        return;
    }

    // Get the 212 config param.
    LockLazySingleton* config_param = config_param->GetInstance();

    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(config_param->port_);
    server_addr_.sin_addr.s_addr = inet_addr(config_param->host_.c_str());

    // Start connect.
    HandleConnect(config_param->port_, config_param->host_);
    LOG(INFO) << "Log in " << config_param->host_ << ":" << config_param->port_ << "...";


    // NOTE: Epoll in the while(1), So do anything before epoll.
    // Create a thread to start Send.
    std::thread thread_send(&Client::StartSend, this);
    // Get thread native handle.
    tm_["StartSend"] = thread_send.native_handle();
    thread_send.detach();

    LOG(INFO) << "The keep alive status." << config_param->heartbeat_;
    if (config_param->heartbeat_) {
        // TODO: Create the heartbeat thread.
    }

    // NOTE: The epoll of while(1) must in the last of logic. 
    // Start Read.
    StartRead();
}

void Client::HandleConnect(int port, string host)
{
    // Trying to connect the server.
    int ret;
    LOG(INFO) << "Trying to connect " << host << ":" << port << "...";
    ret = connect(socket_client_fd_, (struct sockaddr *)&server_addr_, sizeof(server_addr_));
    if (ret < 0) {
        LOG(ERROR) << "Connet to server failed.";
        sleep(5);
        // Connect the server retry.
        HandleConnect(port, host);
    }
    return;
}

void Client::RetryConnect()
{
    LOG(INFO) << "RetryConnect()";
    // Create the socket to connect the server and set socket is unblocked.
    socket_client_fd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (socket_client_fd_ < 0) {
        LOG(ERROR) << "Retrying Connect to server failed.";
        // If create failed then reset the retry connect status.
        return;
    }

    // Get the 212 config param.
    LockLazySingleton *config_param = config_param->GetInstance();

    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(config_param->port_);
    server_addr_.sin_addr.s_addr = inet_addr(config_param->host_.c_str());

    // Create a thread to retry connect the server.
    std::thread thread_retry_connect(&Client::HandleRetryConnect, this);
    // Get thread native handle.
    tm_["RetryConnect"] = thread_retry_connect.native_handle();
    thread_retry_connect.detach();
}

void Client::HandleRetryConnect()
{
    // Get the 212 config param.
    LockLazySingleton *config_param = config_param->GetInstance();
    int ret;

    while (1) {
        // Trying to connect the server.
        LOG(INFO) << "Retrying to connect " << config_param->host_ << ":" << config_param->port_ << "...";
        ret = connect(socket_client_fd_, (struct sockaddr *)&server_addr_, sizeof(server_addr_));
        if (ret < 0) {
            LOG(ERROR) << "Retry Connet to server failed.";
            sleep(5);
        } else {
            LOG(INFO) << "Log in " << config_param->host_ << ":" << config_param->port_ << "...";
            // Add new socket fd to epoll.
            epoll_event_.data.fd = socket_client_fd_;
            // Add socket fd.
            epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, socket_client_fd_, &epoll_event_);
            break;
        }
    }
}

void Client::StartRead()
{
    // Init epoll.
    int n;
    epoll_fd_ = epoll_create1(0);
    if (epoll_fd_ == -1) {
        LOG(INFO) << "Epoll Create1";
        return;
    }
    // Set epoll param.
    epoll_event_.events = EPOLLIN | EPOLLET;

    epoll_event_.data.fd = socket_client_fd_;
    // Add socket fd.
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, socket_client_fd_, &epoll_event_);

    while (1) {
        nfds_ = epoll_wait(epoll_fd_, events, MAX_EVENTS, 100);
        if (nfds_ == -1) {
            LOG(INFO) << "Epoll Wait failed.";
            return;
        }

        // Wait to listen the fd.
        for (n = 0; n < nfds_; ++n) {
            if (events[n].data.fd == socket_client_fd_) {
                HandleRead();
            } 
        }
    }
}

void Client::HandleRead()
{
    int nread;
    // Clear the buf.
    memset(buf, 0, MAX_BUF_SIZE);
    nread = recv(socket_client_fd_, buf, MAX_BUF_SIZE, MSG_DONTWAIT); // MSG_DONTWAIT meaning unblocked receiver.
    if (nread < 0) {
        // This socket is closed.
        LOG(ERROR) << "Server close.";
        // Close socket.
        close(socket_client_fd_);
        // Remove the socket fd from epoll.
        epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
        return;
    } else if (nread == 0) {
        // This socket is closed.
        LOG(ERROR) << "Server close.";
        // Close socket.
        close(socket_client_fd_);
        // Remove the socket fd from epoll.
        epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
        return;
    }
    input_buffer_.clear();
    input_buffer_ = buf;
    LOG(INFO) << input_buffer_;
}

void Client::StartSend()
{
    while (1)
    {
        sleep(3);
        LOG(INFO) << "Send";
    }
}

void Client::HandleSend()
{

}
