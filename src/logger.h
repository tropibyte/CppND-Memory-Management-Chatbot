#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger
{
public:
    static Logger &getInstance()
    {
        static Logger instance;
        return instance;
    }

    void log(const std::string &message)
    {
        std::string timestamped = getTimestamp() + " " + message;
        std::cout << timestamped << std::endl;
        if (_fileStream.is_open())
        {
            _fileStream << timestamped << std::endl;
        }
    }

private:
    std::ofstream _fileStream;

    Logger()
    {
        _fileStream.open("chatbot.log", std::ios::out | std::ios::app);
    }

    ~Logger()
    {
        if (_fileStream.is_open())
        {
            _fileStream.close();
        }
    }

    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::string getTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                       now.time_since_epoch()) %
                   1000;

        std::stringstream ss;
        std::tm tm_buf;
#ifdef _WIN32
        localtime_s(&tm_buf, &time);
#else
        localtime_r(&time, &tm_buf);
#endif
        ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S")
           << "." << std::setfill('0') << std::setw(3) << ms.count();
        return "[" + ss.str() + "]";
    }
};

#endif /* LOGGER_H_ */
