#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

class TimeProcessor {
private:
    // 计时器相关变量
    std::chrono::high_resolution_clock::time_point start_time_;
    std::chrono::high_resolution_clock::time_point end_time_;
    bool timer_running_;
    double elapsed_time_;

public:
    // 构造函数
    TimeProcessor() : timer_running_(false), elapsed_time_(0.0) {}
    
    // 获取当前时间戳（秒，double类型，包含小数部分）
    double getCurrentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration<double>(duration).count();
    }
    
    // 获取当前时间戳（毫秒）
    long long getCurrentTimestampMs() const {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    
    // 获取当前时间戳（微秒）
    long long getCurrentTimestampUs() const {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }
    
    // 获取格式化时间字符串：年-月-日 时:分:秒
    std::string getFormattedTime() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::tm tm_info;
        #ifdef _WIN32
            localtime_s(&tm_info, &time);  // Windows版本
        #else
            localtime_r(&time, &tm_info);  // Linux/macOS版本
        #endif
        
        std::ostringstream oss;
        oss << std::put_time(&tm_info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    
    // 获取格式化时间字符串（包含毫秒）
    std::string getFormattedTimeWithMs() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        // 获取毫秒部分
        auto since_epoch = now.time_since_epoch();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch) % 1000;
        
        std::tm tm_info;
        #ifdef _WIN32
            localtime_s(&tm_info, &time);
        #else
            localtime_r(&time, &tm_info);
        #endif
        
        std::ostringstream oss;
        oss << std::put_time(&tm_info, "%Y-%m-%d %H:%M:%S");
        oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return oss.str();
    }
    
    // 启动计时器
    void startTimer() {
        if (timer_running_) {
            std::cout << "计时器已经在运行中，重新开始计时。" << std::endl;
        }
        start_time_ = std::chrono::high_resolution_clock::now();
        timer_running_ = true;
        elapsed_time_ = 0.0;
    }
    
    // 停止计时器，返回经过的时间（秒）
    double stopTimer() {
        if (!timer_running_) {
            std::cout << "计时器未启动。" << std::endl;
            return 0.0;
        }
        
        end_time_ = std::chrono::high_resolution_clock::now();
        timer_running_ = false;
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_ - start_time_);
        elapsed_time_ = duration.count() / 1e9;  // 转换为秒
        
        return elapsed_time_;
    }
    
    // 暂停计时器（可选功能）
    void pauseTimer() {
        if (!timer_running_) {
            std::cout << "计时器未启动，无法暂停。" << std::endl;
            return;
        }
        
        end_time_ = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_ - start_time_);
        elapsed_time_ += duration.count() / 1e9;
    }
    
    // 恢复计时器（可选功能）
    void resumeTimer() {
        if (timer_running_) {
            std::cout << "计时器已经在运行中。" << std::endl;
            return;
        }
        start_time_ = std::chrono::high_resolution_clock::now();
        timer_running_ = true;
    }
    
    // 获取当前计时器值（不停止计时器）
    double getCurrentTimerValue() const {
        if (!timer_running_) {
            return elapsed_time_;
        }
        
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - start_time_);
        return elapsed_time_ + duration.count() / 1e9;
    }
    
    // 检查计时器是否在运行
    bool isTimerRunning() const {
        return timer_running_;
    }
    
    // 获取指定时间戳的格式化时间
    static std::string formatTimestamp(double timestamp) {
        auto duration = std::chrono::duration<double>(timestamp);
        auto time_point = std::chrono::system_clock::time_point(
            std::chrono::duration_cast<std::chrono::system_clock::duration>(duration));
        
        auto time = std::chrono::system_clock::to_time_t(time_point);
        std::tm tm_info;
        
        #ifdef _WIN32
            localtime_s(&tm_info, &time);
        #else
            localtime_r(&time, &tm_info);
        #endif
        
        std::ostringstream oss;
        oss << std::put_time(&tm_info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    
    // 获取当前日期（年-月-日）
    std::string getCurrentDate() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::tm tm_info;
        #ifdef _WIN32
            localtime_s(&tm_info, &time);
        #else
            localtime_r(&time, &tm_info);
        #endif
        
        std::ostringstream oss;
        oss << std::put_time(&tm_info, "%Y-%m-%d");
        return oss.str();
    }
    
    // 获取当前时间（时:分:秒）
    std::string getCurrentTime() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::tm tm_info;
        #ifdef _WIN32
            localtime_s(&tm_info, &time);
        #else
            localtime_r(&time, &tm_info);
        #endif
        
        std::ostringstream oss;
        oss << std::put_time(&tm_info, "%H:%M:%S");
        return oss.str();
    }
    
    // 重置计时器
    void resetTimer() {
        timer_running_ = false;
        elapsed_time_ = 0.0;
    }
};

