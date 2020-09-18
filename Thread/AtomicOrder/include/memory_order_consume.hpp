#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

using namespace std;

struct X {
    int i;
    std::string s;
};

class OrderConsume {
public:
    OrderConsume() = default;
    virtual ~OrderConsume() = default;
    void CreateX() {
        X* x = new X;
        x->i = 42;
        x->s = "hello";
        a.store(99, std::memory_order_relaxed);
        p.store(x, std::memory_order_release);
    }

    void UseX() {
        X* x;
        while (!(x = p.load(std::memory_order_consume))) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep 2s.
        }
        assert(x->i == 42);
        assert(x->s == "hello");
        assert(a.load(std::memory_order_relaxed) == 99);
    }

    void Run() {
        std::thread create_x_work(&OrderConsume::CreateX, this);
        std::thread use_x_work(&OrderConsume::UseX, this);
        
        create_x_work.join();
        use_x_work.join();

        std::cout << "No Errnor Work." << std::endl;
    }

private:
    std::atomic<X*> p;
    std::atomic<int> a;
};