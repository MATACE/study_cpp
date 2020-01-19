#include "data_queue.h"

DataQueue* DataQueue::m_instanceSingleton = new DataQueue;

DataQueue::DataQueue()
{
    std::cout << "Create DataQueue." << std::endl;
}

DataQueue::~DataQueue()
{

}

DataQueue* DataQueue::GetInstace()
{
    return m_instanceSingleton;
}

bool DataQueue::GetFrontQueue(string& data_string, string queue_name)
{
    if (queue_name == HEART_BEAT) {   // Visit the heartbeat queue.
        // Lock.
        heartbeat_queue_lock_.lock();
        if (heartbeat_queue_.empty()) {
            std::cout << "GetFrontQueue " << queue_name << " is empty." << std::endl;
            // Free lock.
            heartbeat_queue_lock_.unlock();
            return false;
        } else {
            data_string = heartbeat_queue_.front();
            // FIXME: If the server back the package what it receiver the client to server data package.
            // can direct to pop the queue front data.
            // heartbeat_queue_.pop();
            // Free lock.
            heartbeat_queue_lock_.unlock();
            return true;
        }
    } else if (queue_name == SEND_PACKAGE) {   // Visit the sendpackage queue.
         // Lock.
        send_package_queue_lock_.lock();
        if (send_package_queue_.empty()) {
            std::cout << "GetFrontQueue " << queue_name << " is empty." << std::endl;
            // Free lock.
            send_package_queue_lock_.unlock();
            return false;
        } else {
            data_string = send_package_queue_.front();
            // FIXME: If the server back the package what it receiver the client to server data package.
            // can direct to pop the queue front data.
            // send_package_queue_.pop();
            // Free lock.
            send_package_queue_lock_.unlock();
            return true;
        }
    }
    return false;
}

bool DataQueue::DelFrontQueue(string& data_string, string queue_name)
{
    if (queue_name == HEART_BEAT) {   // Visit the heartbeat queue.
        // Lock.
        heartbeat_queue_lock_.lock();
        if (heartbeat_queue_.empty()) {
            std::cout << "DelFrontQueue " << queue_name << " is empty." << std::endl;
            // Free lock.
            heartbeat_queue_lock_.unlock();
            return false;
        } else {
            // Delete the queue front data.
            heartbeat_queue_.pop();
            // Free lock.
            heartbeat_queue_lock_.unlock();
            return true;
        }
    } else if (queue_name == SEND_PACKAGE) {   // Visit the sendpackage queue.
         // Lock.
        send_package_queue_lock_.lock();
        if (send_package_queue_.empty()) {
            std::cout << "DelFrontQueue " << queue_name << " is empty." << std::endl;
            // Free lock.
            send_package_queue_lock_.unlock();
            return false;
        } else {
            data_string = send_package_queue_.front();
            // Delete the queue front data.
            send_package_queue_.pop();
            // Free lock.
            send_package_queue_lock_.unlock();
            return true;
        }
    }
    return false;
}

bool DataQueue::SetPushQueue(string data_string, string queue_name)
{
    if (queue_name == HEART_BEAT) {   // Visit the heartbeat queue.
        // Lock.
        heartbeat_queue_lock_.lock();
        heartbeat_queue_.push(data_string);
        // Free lock.
        heartbeat_queue_lock_.unlock();
        return true;
    } else if (queue_name == SEND_PACKAGE) {   // Visit the sendpackage queue.
        // Lock.
        send_package_queue_lock_.lock();
        send_package_queue_.push(data_string);
        // Free lock.
        send_package_queue_lock_.unlock();
        return true;
    }
    return false;
}

bool DataQueue::ClearStringQueue(string queue_name)
{
    if (queue_name == HEART_BEAT) {   // Visit the heartbeat queue.
        // Lock.
        heartbeat_queue_lock_.lock();
        while (!heartbeat_queue_.empty()) {
            heartbeat_queue_.pop();
        }
        heartbeat_queue_lock_.unlock();
        return true;
    } else if (queue_name == SEND_PACKAGE) {   // Visit the sendpackage queue.
         // Lock.
        send_package_queue_lock_.lock();
        while (!heartbeat_queue_.empty()) {
            heartbeat_queue_.pop();
        }
        send_package_queue_lock_.unlock();
        return true;
    }
    return false;
}