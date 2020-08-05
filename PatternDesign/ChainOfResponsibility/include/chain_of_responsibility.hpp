#ifndef CHAIN_OF_RESPONSIBILITY_HPP
#define CHAIN_OF_RESPONSIBILITY_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace chain_of_responsibility {

class Account {
public:
    Account() = default;
    Account(float balance)
        : balance_(balance) {}
    virtual ~Account() = default;
    
    virtual string GetName() = 0;
    void SetNext(Account* accout) {
        accout_ = accout;
    }
    bool CanPay(float amount_to_pay) {
        return amount_to_pay <= balance_ ? true : false;
    }
    void Pay(float amount_to_pay) {
        if (CanPay(amount_to_pay)) {
            std::cout << this->GetName() << "Can Pay" << std::endl;
        } else if (accout_ != nullptr) {
            accout_->Pay(amount_to_pay);
        } else {
            std::cout << this->GetName() << "Failed" << std::endl;
        }
    }

private:
    Account* accout_ = nullptr;
    float balance_;
};

class Bank : public Account {
public:
    Bank() = default;
    Bank(float balance)
        : Account(balance) {} 
    virtual ~Bank() = default;
    string GetName() {
        return "Bank";
    }
};

class PayPal : public Account {
public:
    PayPal() = default;
    PayPal(float balance)
        : Account(balance) {} 
    virtual ~PayPal() = default;
    string GetName() {
        return "PayPal";
    }
};

class BitCoin : public Account {
public:
    BitCoin() = default;
    BitCoin(float balance)
        : Account(balance) {} 
    virtual ~BitCoin() = default;
    string GetName() {
        return "BitCoin";
    }
};

}

#endif // CHAIN_OF_RESPONSIBILITY_HPP