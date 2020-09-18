#include <iostream>
#include <future>

using namespace std;

struct AsyncTask
{
    void Add(int a, int b, int& ret) {
        std::cout << "This Add async thread id: " << std::this_thread::get_id() << std::endl;
        ret = a + b;
    }
    void Del(int a, int b, int& ret) {
        std::cout << "This Del async thread id: " << std::this_thread::get_id() << std::endl;
        ret = b - a;
    }
    void operator() (int a, int b, int& c) {
        std::cout << "This operator() async thread id: " << std::this_thread::get_id() << std::endl;
        c = a * b;
    }
};


