#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace mediator {

class Interpreter;

class Language {
public:
    Language() = default;
    virtual ~Language() = default;
    virtual void ShowMsg(string msg) = 0;
};

class HumanLanguage : public Language {
public:
    HumanLanguage() = default;
    virtual ~HumanLanguage() = default;

    void ShowMsg(string msg) override {
        std::cout << "This is Human Language: " << msg << std::endl;
    }
};

class IntelligentLanguage : public Language {
public:
    IntelligentLanguage() = default;
    virtual ~IntelligentLanguage() = default;
    
    void ShowMsg(string msg) override {
        std::cout << "This is Intelligent Language: " << msg << std::endl;
    }
};

class Interpreter {
public:
    Interpreter() = delete;
    Interpreter(shared_ptr<HumanLanguage> human_lague, shared_ptr<IntelligentLanguage> inter_lague)
        : human_lague_(human_lague), inter_lague_(inter_lague) {}
    virtual ~Interpreter() = default;

    shared_ptr<HumanLanguage> human_lague_;
    shared_ptr<IntelligentLanguage> inter_lague_;

    void HumanLanguageToIntelligent(string msg) {
        inter_lague_->ShowMsg(msg);
    }
    
    void IntelligentLanguageToHuman(string msg) {
        human_lague_->ShowMsg(msg);
    }
};

}

#endif // MEDIATOR_HPP