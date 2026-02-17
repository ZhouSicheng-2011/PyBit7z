// pyos.hpp - Python风格的OS操作C++库接口
// 兼容C++11及以上版本

#ifndef PYOS_HPP
#define PYOS_HPP

// 添加导出/导入宏
#ifdef _WIN32
  #ifdef pyos_EXPORTS
    // 构建 DLL 时定义导出
    #define PYOS_API __declspec(dllexport)
  #else
    // 使用 DLL 时定义导入
    #define PYOS_API __declspec(dllimport)
  #endif
#else
  // 非 Windows 平台无需特殊处理
  #define PYOS_API
#endif

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>
#include <utility>

namespace os {

// ===================== os.path 命名空间 =====================
namespace path {
PYOS_API std::string join(const std::vector<std::string>& parts);

template<typename... Args>
inline std::string join(const Args&... args) {
    std::vector<std::string> parts = {args...};
    return join(parts);
}

PYOS_API std::string normpath(const std::string& p);
PYOS_API std::string abspath(const std::string& p);
PYOS_API std::string basename(const std::string& p);
PYOS_API std::string dirname(const std::string& p);
PYOS_API bool exists(const std::string& p);
PYOS_API bool isfile(const std::string& p);
PYOS_API bool isdir(const std::string& p);
PYOS_API bool islink(const std::string& p);
PYOS_API uint64_t getsize(const std::string& p);
PYOS_API std::string splitext(const std::string& p);
PYOS_API std::pair<std::string, std::string> splitext_pair(const std::string& p);
PYOS_API time_t getmtime(const std::string& p);
PYOS_API std::string relpath(const std::string& path, const std::string& start = ".");
PYOS_API bool isabs(const std::string& p);
} // namespace path

// ===================== os 主命名空间 =====================
PYOS_API std::string getcwd();
PYOS_API bool chdir(const std::string& path);
PYOS_API std::vector<std::string> listdir(const std::string& path = ".");
PYOS_API bool mkdir(const std::string& path, int mode = 0777);
PYOS_API bool makedirs(const std::string& path, int mode = 0777);
PYOS_API bool remove(const std::string& path);
PYOS_API bool rmdir(const std::string& path);
PYOS_API uint64_t removedirs(const std::string& path);
PYOS_API bool rename(const std::string& oldpath, const std::string& newpath);
PYOS_API bool copyfile(const std::string& src, const std::string& dst);
PYOS_API std::string getenv(const std::string& key);
PYOS_API bool putenv(const std::string& key, const std::string& value);
PYOS_API std::string expanduser();
PYOS_API std::string expanduser(const std::string& path);
PYOS_API int getmode(const std::string& path);
PYOS_API bool chmod(const std::string& path, int mode);
PYOS_API std::string gettempdir();
PYOS_API std::string urandom(size_t length);
PYOS_API std::vector<std::string> walk(const std::string& root);

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

PYOS_API std::string read_file(const std::string& filename);
PYOS_API bool write_file(const std::string& filename, const std::string& content);
PYOS_API bool append_file(const std::string& filename, const std::string& content);

} // namespace os

#endif // PYOS_HPP