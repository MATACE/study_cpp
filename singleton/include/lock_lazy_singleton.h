#ifndef LOCK_LAZY_SINGLETON_H
#define LOCK_LAZY_SINGLETON_H

#include <iostream>
#include <mutex>

using namespace std;

class LockLazySingleton
{
public:
    // Static Get myself instace point api.
    static LockLazySingleton* GetInstace();

    // The singleton variable.
    string name_;
    int age_;

private:
    // Private constructor and destructor.
    LockLazySingleton();
    virtual ~LockLazySingleton();

    // Private copy constructor and assignment operator.
    LockLazySingleton(const LockLazySingleton&);
    LockLazySingleton& operator=(const LockLazySingleton&);

    // Static myself instance point.
    static LockLazySingleton *m_instanceSingleton;
    // Static lock to protect the object.
    static std::mutex mtx;

};

#endif // LAZY_SINGLETON_H