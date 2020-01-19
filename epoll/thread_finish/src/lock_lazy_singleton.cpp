#include "lock_lazy_singleton.h"

// LazySingleton* LazySingleton::m_instanceSingleton = 0;
LockLazySingleton* LockLazySingleton::m_instanceSingleton = nullptr;
std::mutex LockLazySingleton::mtx;

LockLazySingleton::LockLazySingleton()
{
    std::cout << "Create LockLazySingleton" << std::endl;
}

LockLazySingleton::~LockLazySingleton()
{

}

LockLazySingleton* LockLazySingleton::GetInstance()
{
    if (m_instanceSingleton == NULL) {
            mtx.lock();
            // If the Singleton not null, then less mutex lock time. 
            if (m_instanceSingleton == NULL) {
                m_instanceSingleton = new LockLazySingleton;
            }
            mtx.unlock();
        }
        return m_instanceSingleton;
}