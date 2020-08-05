#ifndef INTERPTRTER_HPP
#define INTERPTRTER_HPP

#include <iostream>

using namespace std;

namespace interpreter_api {

class Context
{
public:
    Context() = default;
    virtual ~Context() = default;
};

class AbstractExpression
{
public:
    AbstractExpression() = default;
    virtual ~AbstractExpression() = default;
    virtual void Interpret(Context& c) = 0;
    
};

class TerminalExpression : public AbstractExpression
{
public:
    TerminalExpression() = default;
    TerminalExpression(string statement) {
        _statement = statement;
    }
    virtual ~TerminalExpression() = default;
    void Interpret(Context& c) {
        std::cout << this->_statement << "TerminalExpression" << std::endl;
    }

    string _statement;
};

class NonterminalExpression : public AbstractExpression
{
public:
    NonterminalExpression() = default;
    NonterminalExpression(AbstractExpression* expression, int times) {
        this->_expression = expression;
        this->_times = times;
    }
    virtual ~NonterminalExpression() = default;
    void Interpret(Context& c) override {
        for (int i = 0; i < _times ; i++) {
            this->_expression->Interpret(c);
        }
    }
    AbstractExpression* _expression;
    int _times;
};

}

#endif // INTERPTRTER_HPP