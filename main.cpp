#include <iostream>
#include "tabulate/color.hpp"
#include "Logger.h"
#include "thread"

/*
void thread_test(int n){
    Logger::Trace("thread word test");
} */
int main() {
    Logger::setPriority(traceP);
    std::string a = "joy";
    auto b = "6";
    Logger::Trace(" hello world ",a,a);
    Logger::Debug("Debug text ", a, " is working");
    Logger::setPriority(infoP);
    Logger::Info("Getting Info on ", a, " current progress", b);

    Logger::Warn("Warning ", a, " there is a data breech");

/*
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(thread_test,i);
    }

    for (int j = 0; j < 10; ++j) {
        threads[j].join();
    }
    */
    std::cin.get();
    return 0;
}
