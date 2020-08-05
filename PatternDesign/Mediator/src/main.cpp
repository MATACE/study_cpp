#include <iostream>

#include "mediator.hpp"

using namespace std;
using namespace mediator;

int main(int argc, char const *argv[])
{ 
    shared_ptr<HumanLanguage> human = make_shared<HumanLanguage>();
    shared_ptr<IntelligentLanguage> intel = make_shared<IntelligentLanguage>();

    Interpreter inter(human, intel);
    
    inter.HumanLanguageToIntelligent("Hello World");
    inter.IntelligentLanguageToHuman("Bye Bye");

    return 0;
}
