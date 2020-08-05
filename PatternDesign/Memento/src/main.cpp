#include <iostream>

#include "memento.hpp"

using namespace std;
using namespace memento;

int main(int argc, char const *argv[])
{
    Editor editor_;
    editor_.Write("Hello World");
    
    std::cout << "1321" << std::endl;
    std::cout << editor_.GetContent() << std::endl;
    
    auto save = editor_.Save();
    
    editor_.Write("Bye Bye");
    
    std::cout << editor_.GetContent() << std::endl;
    
    editor_.ResState(save);
    
    std::cout << editor_.GetContent() << std::endl;

    return 0;
}
