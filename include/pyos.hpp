// pyos.hpp - Python风格的OS操作C++库接口
// 兼容C++11及以上版本

#ifndef PYOS_HPP
#define PYOS_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>
#include <utility>

namespace os {

// ===================== os.path 命名空间 =====================
namespace path {

std::string join(const std::vector<std::string>& parts);

template<typename... Args>
inline std::string join(const Args&... args) {
    std::vector<std::string> parts = {args...};
    return join(parts);
}

std::string normpath(const std::string& p);
std::string abspath(const std::string& p);
std::string basename(const std::string& p);
std::string dirname(const std::string& p);
bool exists(const std::string& p);
bool isfile(const std::string& p);
bool isdir(const std::string& p);
bool islink(const std::string& p);
uint64_t getsize(const std::string& p);
std::string splitext(const std::string& p);
std::pair<std::string, std::string> splitext_pair(const std::string& p);
time_t getmtime(const std::string& p);
std::string relpath(const std::string& path, const std::string& start = ".");
bool isabs(const std::string& p);

} // namespace path

// ===================== os 主命名空间 =====================

std::string getcwd();
bool chdir(const std::string& path);
std::vector<std::string> listdir(const std::string& path = ".");
bool mkdir(const std::string& path, int mode = 0777);
bool makedirs(const std::string& path, int mode = 0777);
bool remove(const std::string& path);
bool rmdir(const std::string& path);
uint64_t removedirs(const std::string& path);
bool rename(const std::string& oldpath, const std::string& newpath);
bool copyfile(const std::string& src, const std::string& dst);
std::string getenv(const std::string& key);
bool putenv(const std::string& key, const std::string& value);
std::string expanduser();
std::string expanduser(const std::string& path);
int getmode(const std::string& path);
bool chmod(const std::string& path, int mode);
std::string gettempdir();
std::string urandom(size_t length);
std::vector<std::string> walk(const std::string& root);

/**
 * 行结束符（类似os.linesep）
 */
inline std::string linesep() {
#ifdef _WIN32
    return "\r\n";
#else
    return "\n";
#endif
}

/**
 * 路径分隔符（类似os.sep）
 */
inline char sep() {
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

/**
 * 路径列表分隔符（类似os.pathsep）
 */
inline char pathsep() {
#ifdef _WIN32
    return ';';
#else
    return ':';
#endif
}

// ===================== 实用工具函数 =====================

std::string read_file(const std::string& filename);
bool write_file(const std::string& filename, const std::string& content);
bool append_file(const std::string& filename, const std::string& content);

} // namespace os

#endif // PYOS_HPP