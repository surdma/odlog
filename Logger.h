#pragma once

#include <iostream>
#include "tabulate/table.hpp"
#include "tabulate/markdown_exporter.hpp"
#include <mutex>
#include <fstream>
#include <ctime>

enum LogPriority {
    traceP, debugP, infoP, warnP, errorP, fatalP
};

class Logger {
public:

    static void setPriority(LogPriority new_priority) {
        priority = new_priority;
        std::string test = priorlog(priority);

        tabulate::Table tune;

        tune.add_row({"Priority Set to: ", test});
        tune.column(0).format().font_color(tabulate::Color::red).font_style({tabulate::FontStyle::bold});
        //colors[0][1].format().font_color(tabulate::Color::blue).font_style({tabulate::FontStyle::bold});
        std::cout << tune << std::endl;
    }

    template<typename... Args>
    static void Trace(std::string message, Args... args) {

        auto color = tabulate::Color::blue;
        log_result("Trace", traceP, message,color, args...);
    }

    template<typename... Args>
    static void Debug(std::string message, Args... args) {
        auto color = tabulate::Color::yellow;
        log_result("Debug", debugP, message,color, args...);
    }

    template<typename... Args>
    static void Info(std::string message, Args... args) {
        auto color = tabulate::Color::green;
        log_result("Info", infoP, message,color, args...);
    }

    template<typename... Args>
    static void Warn(std::string message, Args... args) {
        auto color = tabulate::Color::red;
        log_result("Warn", warnP, message,color, args...);
    }


private:
    static LogPriority priority;
    static std::mutex log_mutex;


    static std::string priorlog(LogPriority prior);

    template<typename... Args>
    static void log_result(std::string title, LogPriority new_priority, std::string message,auto flag_color, Args... args) {
        if (priority <= new_priority) {

            std::time_t current_time = std::time(0);
            std::tm* timestamp = std::localtime(&current_time);
            char buffer[80];
            strftime(buffer,80,"%c", timestamp);

            std::scoped_lock lock(log_mutex);

            tabulate::Table log;


            std::string file_name = "dump_logs.odl";
            std::ofstream fout(file_name, std::ios_base::app);

            log.add_row({title,buffer ,message, args...});

            log.format().font_color(flag_color).font_style({tabulate::FontStyle::bold});


            fout << log << std::endl;
            fout.close();
            std::cout << log << std::endl;



        }
    }

};

LogPriority Logger::priority = infoP;
std::mutex Logger::log_mutex;

std::string Logger::priorlog(LogPriority prior) {
    switch (prior) {
        case traceP:
            return "Tracing";
        case debugP:
            return "Debugging";
        case infoP:
            return "Notice";
        case warnP:
            return "Warning";
        case errorP:
            return "Reporting Error";
        case fatalP:
            return "Critical Error";
        default:
            return "invalid priority";
    }
}
