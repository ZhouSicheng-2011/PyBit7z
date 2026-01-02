// pyos.cpp - Python风格的OS操作C++库实现
// 需要C++17或更高版本支持

#include "pyos.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #include <io.h>
    #define getcwd _getcwd
    #define chdir _chdir
    #define stat _stat
    #ifndef S_ISDIR
        #define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
    #endif
    #ifndef S_ISREG
        #define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
    #endif
    #ifndef S_ISLNK
        #define S_ISLNK(mode) (0)  // Windows 无符号链接检查的简单定义
    #endif
#else
    #include <unistd.h>
    #include <dirent.h>
    #include <pwd.h>
#endif

namespace os {

// 命名空间别名，方便使用
namespace fs = std::filesystem;

// ===================== 常量定义 =====================

#ifdef _WIN32
    const char sep = '\\';
    const char pathsep = ';';
#else
    const char sep = '/';
    const char pathsep = ':';
#endif

// ===================== os.path 命名空间实现 =====================

namespace path {

std::string join(const std::vector<std::string>& parts) {
    if (parts.empty()) return "";
    
    fs::path result = parts[0];
    for (size_t i = 1; i < parts.size(); ++i) {
        result /= parts[i];
    }
    return result.string();
}

std::string normpath(const std::string& p) {
    try {
        return fs::weakly_canonical(fs::path(p)).string();
    } catch (...) {
        return fs::path(p).lexically_normal().string();
    }
}

std::string abspath(const std::string& p) {
    if (p.empty()) return fs::current_path().string();
    return fs::absolute(fs::path(p)).string();
}

std::string basename(const std::string& p) {
    return fs::path(p).filename().string();
}

std::string dirname(const std::string& p) {
    return fs::path(p).parent_path().string();
}

bool exists(const std::string& p) {
    return fs::exists(fs::path(p));
}

bool isfile(const std::string& p) {
    return fs::is_regular_file(fs::path(p));
}

bool isdir(const std::string& p) {
    return fs::is_directory(fs::path(p));
}

bool islink(const std::string& p) {
    return fs::is_symlink(fs::path(p));
}

uint64_t getsize(const std::string& p) {
    try {
        return static_cast<uint64_t>(fs::file_size(fs::path(p)));
    } catch (...) {
        return 0;
    }
}

std::string splitext(const std::string& p) {
    return fs::path(p).extension().string();
}

std::pair<std::string, std::string> splitext_pair(const std::string& p) {
    fs::path fp(p);
    return {fp.stem().string(), fp.extension().string()};
}

time_t getmtime(const std::string& p) {
    try {
        auto ftime = fs::last_write_time(fs::path(p));
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
        return std::chrono::system_clock::to_time_t(sctp);
    } catch (...) {
        return 0;
    }
}

std::string relpath(const std::string& path, const std::string& start) {
    try {
        return fs::relative(fs::path(path), fs::path(start)).string();
    } catch (...) {
        return path;
    }
}

bool isabs(const std::string& p) {
    return fs::path(p).is_absolute();
}

} // namespace path

// ===================== os 主命名空间实现 =====================

std::string getcwd() {
    char buffer[4096];
    if (::getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }
    return "";
}

bool chdir(const std::string& path) {
    return ::chdir(path.c_str()) == 0;
}

std::vector<std::string> listdir(const std::string& path) {
    std::vector<std::string> result;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            result.push_back(entry.path().filename().string());
        }
    } catch (...) {
        // 目录不存在或无法访问
    }
    return result;
}

bool mkdir(const std::string& path, int mode) {
    try {
        return fs::create_directory(fs::path(path));
    } catch (...) {
        return false;
    }
}

bool makedirs(const std::string& path, int mode) {
    try {
        return fs::create_directories(fs::path(path));
    } catch (...) {
        return false;
    }
}

bool remove(const std::string& path) {
    try {
        return fs::remove(fs::path(path));
    } catch (...) {
        return false;
    }
}

bool rmdir(const std::string& path) {
    try {
        return fs::remove(fs::path(path));
    } catch (...) {
        return false;
    }
}

uint64_t removedirs(const std::string& path) {
    try {
        return static_cast<uint64_t>(fs::remove_all(fs::path(path)));
    } catch (...) {
        return 0;
    }
}

bool rename(const std::string& oldpath, const std::string& newpath) {
    try {
        fs::rename(fs::path(oldpath), fs::path(newpath));
        return true;
    } catch (...) {
        return false;
    }
}

bool copyfile(const std::string& src, const std::string& dst) {
    try {
        fs::copy_file(fs::path(src), fs::path(dst), fs::copy_options::overwrite_existing);
        return true;
    } catch (...) {
        return false;
    }
}

std::string getenv(const std::string& key) {
    const char* value = std::getenv(key.c_str());
    return value ? std::string(value) : "";
}

bool putenv(const std::string& key, const std::string& value) {
#ifdef _WIN32
    return _putenv_s(key.c_str(), value.c_str()) == 0;
#else
    return setenv(key.c_str(), value.c_str(), 1) == 0;
#endif
}

std::string expanduser() {
#ifdef _WIN32
    const char* home = std::getenv("USERPROFILE");
    if (home) return home;
    
    const char* drive = std::getenv("HOMEDRIVE");
    const char* path = std::getenv("HOMEPATH");
    if (drive && path) return std::string(drive) + path;
    
    return "";
#else
    const char* home = std::getenv("HOME");
    if (home) return home;
    
    // 尝试通过getpwuid获取
    struct passwd* pw = getpwuid(getuid());
    if (pw && pw->pw_dir) {
        return pw->pw_dir;
    }
    
    return "";
#endif
}

std::string expanduser(const std::string& path) {
    if (path.empty() || path[0] != '~') return path;
    
    std::string home = expanduser();
    if (home.empty()) return path;
    
    if (path.size() == 1 || path[1] == '/') {
        return home + path.substr(1);
    }
    
    // 处理 ~user 格式（简化版本，不实现完整功能）
    return path;
}

int getmode(const std::string& path) {
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0) {
        return fileStat.st_mode & 0777;
    }
    return -1;
}

bool chmod(const std::string& path, int mode) {
#ifdef _WIN32
    // Windows下简化处理
    return _chmod(path.c_str(), mode) == 0;
#else
    return ::chmod(path.c_str(), mode) == 0;
#endif
}

std::string gettempdir() {
    return fs::temp_directory_path().string();
}

std::string urandom(size_t length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);
    
    std::string result;
    result.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        result += alphanum[dist(rng)];
    }
    
    return result;
}

std::vector<std::string> walk(const std::string& root) {
    std::vector<std::string> result;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(root)) {
            if (entry.is_regular_file()) {
                result.push_back(entry.path().string());
            }
        }
    } catch (...) {
        // 忽略错误
    }
    return result;
}

std::string linesep() {
#ifdef _WIN32
    return "\r\n";
#else
    return "\n";
#endif
}

// ===================== 实用工具函数实现 =====================

std::string read_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool write_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    return !file.fail();
}

bool append_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::binary | std::ios::app);
    if (!file.is_open()) {
        return false;
    }
    
    file << content;
    return !file.fail();
}

} // namespace os