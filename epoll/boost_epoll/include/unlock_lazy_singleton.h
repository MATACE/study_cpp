#ifndef UNLOCK_LAZY_SINGLETON_H
#define UNLOCK_LAZY_SINGLETON_H

#include <iostream>
#include <mutex>

// The unlock LazySinglenton just support c++11.

using namespace std;

class UnlockLazySingleton
{
public:
    static UnlockLazySingleton& GetInstace();
    string name_;
    int age_;

private:
    // Private constructor and destructor.
    UnlockLazySingleton();
    virtual ~UnlockLazySingleton();

    // Private copy constructor and assignment operator.
    UnlockLazySingleton(const UnlockLazySingleton&);
    UnlockLazySingleton& operator=(const UnlockLazySingleton&);
};

#endif // UNLOCK_LAZY_SINGLETON_H