#include "client.h"

Client::Client()
{   
    stop_ = false;
    retry_connect_successful_ = false;
    timeout_cout_ = 0;
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
    pthread_cancel(tm_["SendHeartbeat"]);
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
    std::thread thread_send(&Client::StartSendPackage, this);
    // Get thread native handle.
    tm_["StartSendPackage"] = thread_send.native_handle();
    thread_send.detach();

    LOG(INFO) << "The keep alive status : " << config_param->heartbeat_;
    if (config_param->heartbeat_) {
        // Create a thread to retry connect the server.
        std::thread thread_send_heartbeat(&Client::StartSendheartbeat, this);
        // Get thread native handle.
        tm_["SendHeartbeat"] = thread_send_heartbeat.native_handle();
        thread_send_heartbeat.detach();
    }

    // Cout the max of cout time.
    timeout_cout_max_ = (config_param->heartbeat_timer_ + 5) * 1000 / EPOLL_LISTEN_TIME;

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
    // Set socekt stop.
    stop_ = true;
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
            // Reset the socket stop status.
            stop_ = false;
            retry_connect_successful_ = true;
            timeout_cout_ = 0;
            return;
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
        // Epoll listen those fd.
        nfds_ = epoll_wait(epoll_fd_, events, MAX_EVENTS, EPOLL_LISTEN_TIME);
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

        // If Retry connect server then close.
        if (retry_connect_successful_) {
            pthread_cancel(tm_["RetryConnect"]);
            retry_connect_successful_ = false;
        } 

        // Timeout_cout_++ to judge timer out, if not receiver package from server to reset
        // the timeout_cout_, it will be time out to retry connect the server.
        if (++timeout_cout_ == timeout_cout_max_) {
            LOG(INFO) << "Alive time out";
            RetryConnect();
        }
    }
}

void Client::HandleRead()
{
    // FIXME: If in the time out inteval not receiver the package from serve then will retry connect.
    timeout_cout_ = 0;
    int nread;
    // Clear the buf.
    memset(recv_buf, 0, MAX_BUF_SIZE);
    nread = recv(socket_client_fd_, recv_buf, MAX_BUF_SIZE, MSG_DONTWAIT); // MSG_DONTWAIT meaning unblocked receiver.
    if (nread < 0) {
        // This socket is closed.
        LOG(ERROR) << "Server close.";
        // Close socket.
        close(socket_client_fd_);
        // Remove the socket fd from epoll.
        epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
        // Retry to connect the server.
        RetryConnect();
        return;
    } else if (nread == 0) {
        // This socket is closed.
        LOG(ERROR) << "Server close.";
        // Close socket.
        close(socket_client_fd_);
        // Remove the socket fd from epoll.
        epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
        // Retry to connect the server.
        RetryConnect();
        return;
    }

    // Get the whole package by boost regex package head and tail.
    std::size_t n;
    string tmp_buf = recv_buf;
    input_buffer_.append(tmp_buf);
    // The regex package logic reference the boost async socket timeout.
    if (RegexWholePackage(input_buffer_, n)) {
        std::string line(input_buffer_.substr(0, n));
        input_buffer_.erase(0, n);
        if (!line.empty()) {
            LOG(INFO) << "Received: " << line;
            ParsePackage(line);
        }
    } 
}

void Client::StartSendPackage()
{
    while (1)
    {
        sleep(5); // 3s.
        if (!stop_) {
            HandleSendPackage();
        }
    }
}

void Client::HandleSendPackage()
{
    DataQueue* data_queue = data_queue->GetInstace();
    string send_line;
    int send_num = 0;
    send_line.clear();
    if (data_queue->GetFrontQueue(send_line, SEND_PACKAGE)) {
        SendPackage(send_num, send_line);
        // Send 3 time failed, then close socket and retry connect.
        if (send_num > MAX_RETRY_TIME) {
            // This socket is closed.
            LOG(ERROR) << "Server close.";
            // Close socket.
            close(socket_client_fd_);
            // Remove the socket fd from epoll.
            epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
            // Retry to connect the server.
            RetryConnect();
            return;
        }
    } else {
        return;
    }
}

void Client::SendPackage(int& send_num, string send_line)
{
    int nsend;
    ++send_num;
    if (send_num <= MAX_RETRY_TIME && (!stop_)) {
        // If send failed then try 3 time send.
        nsend = send(socket_client_fd_, send_line.c_str(), send_line.size(), MSG_DONTWAIT); // MSG_DONTWAIT meaning unblocked receiver.
        if (nsend < 0) {
            // Retry send.
            SendPackage(send_num, send_line);
        }
        return;
    }
    return;
}

void Client::StartSendheartbeat()
{
    while (1) {
        usleep(100 * 1000); // Sleep 100ms.
        if (!stop_) {
            boost::asio::io_service io;
	        boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
	        // Synchronization to run.
	        t.async_wait(boost::bind(&Client::HandSendHeartbeat, this, boost::asio::placeholders::error, &t));
	        // Wait to timing task finish.
	        io.run();
        }
    }
}

void Client::HandSendHeartbeat(const boost::system::error_code &ec, boost::asio::steady_timer* pt)
{
    LockLazySingleton* config_param = config_param->GetInstance();
    string line = config_param->heartbeat_package_;
    int send_num = 0;
    if (!stop_) {
        SendHeartbeat(send_num, line);
        // Send 3 time failed, then close socket and retry connect.
        if (send_num > MAX_RETRY_TIME) {
            // This socket is closed.
            LOG(ERROR) << "Server close.";
            // Close socket.
            close(socket_client_fd_);
            // Remove the socket fd from epoll.
            epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, socket_client_fd_, &epoll_event_);
            // Retry to connect the server.
            RetryConnect();
            return;
        }
        // TEST: Set the data to send package queue.
        DataQueue* data_queue = data_queue->GetInstace();
        data_queue->SetPushQueue("AA99887766BB", SEND_PACKAGE);

        timeout_cout_ = 0;
        LockLazySingleton* config_param = config_param->GetInstance();
        int timer = config_param->heartbeat_timer_;
	    pt->expires_after(boost::asio::chrono::seconds(timer)) ;
	    pt->async_wait(boost::bind(&Client::HandSendHeartbeat, this, boost::asio::placeholders::error, pt));
    } else {
        // Stop wait to successful retry connet the server.
        return;
    }
}

void Client::SendHeartbeat(int& send_num, string send_line)
{   
    int nsend;
    ++send_num;
    if (send_num <= MAX_RETRY_TIME && (!stop_)) {
        // If send failed then try 3 time send.
        nsend = send(socket_client_fd_, send_line.c_str(), send_line.size(), MSG_DONTWAIT); // MSG_DONTWAIT meaning unblocked receiver.
        if (nsend < 0) {
            // Retry send.
            SendHeartbeat(send_num, send_line);
        }
        return;
    }
    return;
}

void Client::ParsePackage(string line)
{
    if (line == "AA112233BB") {
        LOG(INFO) << "Receiver the heartbeat package.";
        // FIXME: After send heartbeat package, if not receiver heartbeat package back from server, then retry connect.
        // timeout_cout_ = 0;
    } else {
        LOG(INFO) << "Receiver package form server.";
    }
}

bool Client::RegexWholePackage(string input_buffer, std::size_t& n)
{
    boost::regex expression("^AA(.*?)(BB){1}");
    boost::smatch what;

    if (!boost::regex_search(input_buffer, what, expression)) {
        LOG(ERROR) << "Client::RegexWholePackage failed.";
        return false;
    }
    // Get type string.
    if (!what[0].matched) {
        LOG(ERROR) << "RegexWholePackage boost::regex_search type string failed.";
        return false;
    }
    LOG(INFO) << "what[0]: " << what[0];
    input_buffer = what[0];
    n = input_buffer.size();

    return true;
}
