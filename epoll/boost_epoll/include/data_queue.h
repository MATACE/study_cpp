#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include <iostream>
#include <queue>
#include <mutex>

using namespace std;

#define HEART_BEAT   "heartbeat"
#define SEND_PACKAGE "sendpackage"

static std::mutex heartbeat_queue_lock_;
static std::mutex send_package_queue_lock_;

class DataQueue
{
public:
    static DataQueue* GetInstace();

    bool GetFrontQueue(string& data_string, string queue_name);
    bool DelFrontQueue(string& data_string, string queue_name);
    bool SetPushQueue(string data_string, string queue_name);
    bool ClearStringQueue(string queue_name);

    queue<string> heartbeat_queue_;
    queue<string> send_package_queue_;
    string tmp_heartbeat_string_;
    string tmp_send_package_;

private:
    DataQueue();
    virtual ~DataQueue();

    DataQueue(const DataQueue&);
    DataQueue& operator=(const DataQueue&);

    static DataQueue* m_instanceSingleton;

};

#endif // DATA_QUEUE_H