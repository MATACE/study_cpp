#include <iostream>
#include "lock_lazy_singleton.h"
#include "unlock_lazy_singleton.h"
#include "hunger_singleton.h"

using namespace std;

void ShowLockLazySingleton()
{
    LockLazySingleton *lock_lazy_singleton = LockLazySingleton::GetInstace();
    cout << lock_lazy_singleton->name_ << endl;
    cout << lock_lazy_singleton->age_ << endl;
     
}

void ShowUnLockLazySingleton()
{
    cout << UnlockLazySingleton::GetInstace().name_ << endl;
    cout << UnlockLazySingleton::GetInstace().age_ << endl;
     
}

void ShowHungerSingleton()
{
    HungerSingleton* hunger_singleton = HungerSingleton::GetInstace();
    cout << hunger_singleton->name_ << endl;
    cout << hunger_singleton->age_ << endl;
}

int main()
{
    // Set the Singleton variable.
    LockLazySingleton *lock_lazy_singleton = LockLazySingleton::GetInstace();
    lock_lazy_singleton->name_ = "xiao ming";
    lock_lazy_singleton->age_ = 24;

    UnlockLazySingleton::GetInstace().name_ = "xiao hong";
    UnlockLazySingleton::GetInstace().age_  = 22; 

    HungerSingleton* hunger_singleton = HungerSingleton::GetInstace();
    hunger_singleton->name_ = "xiao gang";
    hunger_singleton->age_ = 23;

    ShowLockLazySingleton();
    ShowUnLockLazySingleton();
    ShowHungerSingleton();

    hunger_singleton->name_ = "xiao hua";
    hunger_singleton->age_ = 25;

    ShowHungerSingleton();

    return 0;
}