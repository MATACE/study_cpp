#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

using namespace std;

class Client
{
public:
    Client();
    virtual ~Client();

    void Strat();
    void Stop();

    void StartConnet();
    void HandleConnet();

    void RetryConnet();
    void HandleRetryConnet();

    void StartRead();
    void HandleRead();

    void StartSend();
    void HandleSend();

private:
    
};

#endif // CLIENT_H