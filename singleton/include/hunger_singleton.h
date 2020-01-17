#ifndef HUNGER_SINGLETON_H
#define HUNGER_SINGLETON_H

#include <iostream>

using namespace std;

class HungerSingleton
{
public:
    static HungerSingleton* GetInstace();

    string name_;
    int age_;

private:
    // Private constructor and destructor.
    HungerSingleton();
    virtual ~HungerSingleton();

    // Private copy constructor and assignment operator.
    HungerSingleton(const HungerSingleton&);
    HungerSingleton& operator=(const HungerSingleton&);
    
    // Static point myself.
    static HungerSingleton *m_instanceSingleton;
};

#endif // HUNGER_SINGLETON_H