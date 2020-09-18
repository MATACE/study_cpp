#include <iostream>
#include <future>
#include <functional>

using namespace std;

class Task {
public:
    Task() = default;
    virtual ~Task() = default;

    int Add(int a, int b) {
        return a + b;
    }

    int Del(int a, int b) {
        return a - b;
    }

    int Mul(int a, int b) {
        return a * b;
    }

};