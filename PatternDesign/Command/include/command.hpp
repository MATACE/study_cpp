#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>

using namespace std;

namespace command {

class Bulb {
public:
    Bulb() = default;
    virtual ~Bulb() = default;

    void TurnOn() const {
        std::cout << "The Bulb Turn On" << std::endl;
    }
    
    void TurnOff() const {
        std::cout << "The Bulb Turn Off" << std::endl;
    }
};

class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;
};

class TurnOn : public Command {
public:
    TurnOn() = default;
    explicit TurnOn(Bulb& bulb)
        : bulb_(bulb) {}
    virtual ~TurnOn() = default;
    void Execute() override {
        bulb_.TurnOff();
    }
    void Undo() override {
        bulb_.TurnOn();
    }
    void Redo() override {
        Execute();
    }
private:
    Bulb& bulb_;
};

class TurnOff : public Command {
public:
    TurnOff() = default;
    TurnOff(Bulb& bulb)
        : bulb_(bulb) {}
    virtual ~TurnOff() = default;
    void Execute() override {
        bulb_.TurnOff();
    }
    void Undo() override {
        bulb_.TurnOn();
    }
    void Redo() override {
        Execute();
    }
private:
    Bulb& bulb_;
};

class Receiver {
public:
    Receiver() = default;
    virtual ~Receiver() = default;
    void Execute(Command& cmd) {
        cmd.Execute();
    }
};

}

#endif // COMMAND_HPP