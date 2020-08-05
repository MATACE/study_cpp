#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace state {

class Size {
public:
    Size() = default;
    virtual ~Size() = default;
    
    virtual void ChangeSize() = 0;
};

class BigSize : public Size {
public:
    BigSize() = default;
    virtual ~BigSize() = default;
    
    void ChangeSize() override {
        std::cout << "Big Size" << std::endl;
    }
};

class SmallSize : public Size {
public:
    SmallSize() = default;
    virtual ~SmallSize() = default;

    void ChangeSize() override {
        std::cout << "Small Size" << std::endl;
    }
};

class Switch {
public:
    Switch() = default;
    explicit Switch(const shared_ptr<Size>& size)
        : size_(size) {}
    virtual ~Switch() = default;

    void SetSize(const shared_ptr<Size>& size) {
        size_ = size;
    }

    void ChangeSize() {
        size_->ChangeSize();
    }

private:
    shared_ptr<Size> size_;
};

}

#endif // STATE_HPP·       