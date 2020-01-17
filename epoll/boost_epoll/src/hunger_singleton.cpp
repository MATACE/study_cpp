#include "hunger_singleton.h"

HungerSingleton* HungerSingleton::m_instanceSingleton = new HungerSingleton;

HungerSingleton::HungerSingleton()
{

}

HungerSingleton::~HungerSingleton()
{

}

HungerSingleton* HungerSingleton::GetInstace()
{
    return m_instanceSingleton;
}