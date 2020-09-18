// #ifndef THREAD_MANAGER_H
// #define THREAD_MANAGER_H

// #include <iostream>
// #include <thread>

// using namespace std;

// // A thread class 
// class background_task
// {
// public:
//     void do_something() const {

//     }

//     void do_something_else() const {

//     }
//     void operator()() const
//     {
//         do_something();
//         do_something_else();
//     }
// };

// // ############################################################

// // A thread struct 
// struct func
// {
//     int& i;
//     func(int& i_) : i(i_) {}
//     void operator() ()
//     {
//         for (unsigned j = 0; j < 1000000; ++j)
//         {
//             do_something(i); // 1. 潜在访问隐患：悬空引用
//         }
//     }

//     void do_something(int& i) {

//     }
// };


// void oops()
// {
//     int some_local_state = 0;
//     func my_func(some_local_state);
//     std::thread my_thread(my_func);
//     // 2. 不等待线程结束
//     my_thread.detach(); 
//     // 3. 新线程可能还在运行
//     // do some other things 
// }                      

// // ############################################################

// void do_something_in_current_thread() {
//     // do anythings 
// }

// void f()
// {
//     int some_local_state=0;
//     func my_func(some_local_state);
//     std::thread t(my_func);
//     try
//     {
//         do_something_in_current_thread();
//     } catch(...) {
//         // Do join in error 
//         t.join(); // 1
//         throw;
//     }
//     // Do join in right
//     t.join(); // 2
// }

// // ############################################################

// class thread_guard
// {
//     std::thread& t;
// public:
//     explicit thread_guard(std::thread& t_) :
//         t(t_) {}
//     virtual ~thread_guard() {
//         if(t.joinable()) { // 1 
//             t.join(); // 2
//         }
//     }

//     thread_guard(thread_guard const&)=delete; // 3
//     thread_guard& operator=(thread_guard const&)=delete;
// };

// void f()
// {
//     int some_local_state=0;
//     func my_func(some_local_state);
//     std::thread t(my_func);
//     thread_guard g(t);
//     do_something_in_current_thread();
// } // 4

// // ############################################################

// void f(int i,std::string const& s);
// void not_oops(int some_param)
// {
//     char buffer[1024];
//     sprintf(buffer, "%i", some_param);
//     std::thread t(f, 3, std::string(buffer)); // 使用std::string，避免悬垂指针
//     t.detach();
// }

// // ############################################################

// void update_data_for_widget(widget_id w,widget_data& data); // 1
// void oops_again(widget_id w)
// {
//     widget_data data;
//     std::thread t(update_data_for_widget, w, std::ref(data)); // 2
//     display_status();
//     t.join();
//     process_widget_data(data); // 3
// }

// // ############################################################

// class X
// {
// public:
//     void do_lengthy_work();
// };

// X my_x;
// std::thread t(&X::do_lengthy_work,&my_x); // 1

// // ############################################################

// class X
// {
// public:
//     void do_lengthy_work(int);
// };

// X my_x;
// int num(0);
// std::thread t(&X::do_lengthy_work, &my_x, num);

// // ############################################################

// void process_big_object(std::unique_ptr<big_object>);
// std::unique_ptr<big_object> p(new big_object);
// p->prepare_data(42);
// std::thread t(process_big_object, std::move(p));

// // ############################################################

// // std::move in thread 

// void some_function();
// void some_other_function();
// std::thread t1(some_function); // 1
// std::thread t2 = std::move(t1); // 2
// t1 = std::thread(some_other_function); // 3
// std::thread t3; // 4
// t3 = std::move(t2); // 5
// t1 = std::move(t3); // Error

// #endif // THREAD_MANAGER_H