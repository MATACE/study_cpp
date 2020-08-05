#include "unlock_lazy_singleton.h"

UnlockLazySingleton::UnlockLazySingleton()
{
    std::cout << "Create UnlockLazySingleton." << std::endl;
}

UnlockLazySingleton::~UnlockLazySingleton()
{
    
}

UnlockLazySingleton& UnlockLazySingleton:: GetInstace()
{
    static UnlockLazySingleton unlock_lazy_singleton;
    return unlock_lazy_singleton;
}