#include <iostream>

#include "interpreter.hpp"

using namespace std;
using namespace interpreter_api;

int main(int argc, char const *argv[])
{

    Context* c = new Context();
    string str = "hello";
    AbstractExpression* te = new TerminalExpression(str);
    AbstractExpression* nte = new NonterminalExpression(te, 2);
    nte->Interpret(*c);

    return 0;
}

