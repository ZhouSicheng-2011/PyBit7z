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

/**
 * 拼接路径组件（类似os.path.join）
 * @param parts 路径组件列表
 * @return 拼接后的路径
 */
std::string join(const std::vector<std::string>& parts);

/**
 * 拼接路径组件（可变参数版本）
 */
template<typename... Args>
std::string join(const Args&... args);

/**
 * 规范化路径（类似os.path.normpath）
 */
std::string normpath(const std::string& p);

/**
 * 获取绝对路径（类似os.path.abspath）
 */
std::string abspath(const std::string& p);

/**
 * 获取基本文件名（类似os.path.basename）
 */
std::string basename(const std::string& p);

/**
 * 获取目录名（类似os.path.dirname）
 */
std::string dirname(const std::string& p);

/**
 * 判断路径是否存在（类似os.path.exists）
 */
bool exists(const std::string& p);

/**
 * 判断是否为文件（类似os.path.isfile）
 */
bool isfile(const std::string& p);

/**
 * 判断是否为目录（类似os.path.isdir）
 */
bool isdir(const std::string& p);

/**
 * 判断是否为链接（类似os.path.islink）
 */
bool islink(const std::string& p);

/**
 * 获取文件大小（类似os.path.getsize）
 */
uint64_t getsize(const std::string& p);

/**
 * 获取文件扩展名（类似os.path.splitext）
 */
std::string splitext(const std::string& p);

/**
 * 分离文件名和扩展名（类似os.path.splitext）
 */
std::pair<std::string, std::string> splitext_pair(const std::string& p);

/**
 * 获取文件的最后修改时间（类似os.path.getmtime）
 */
time_t getmtime(const std::string& p);

/**
 * 获取相对路径（类似os.path.relpath）
 */
std::string relpath(const std::string& path, const std::string& start = ".");

/**
 * 路径是否为绝对路径（类似os.path.isabs）
 */
bool isabs(const std::string& p);

} // namespace path

// ===================== os 主命名空间 =====================

/**
 * 获取当前工作目录（类似os.getcwd）
 */
std::string getcwd();

/**
 * 改变当前工作目录（类似os.chdir）
 */
bool chdir(const std::string& path);

/**
 * 列出目录内容（类似os.listdir）
 */
std::vector<std::string> listdir(const std::string& path = ".");

/**
 * 创建目录（类似os.mkdir）
 */
bool mkdir(const std::string& path, int mode = 0777);

/**
 * 递归创建目录（类似os.makedirs）
 */
bool makedirs(const std::string& path, int mode = 0777);

/**
 * 删除文件（类似os.remove）
 */
bool remove(const std::string& path);

/**
 * 删除目录（类似os.rmdir）
 */
bool rmdir(const std::string& path);

/**
 * 递归删除目录（类似os.removedirs）
 */
uint64_t removedirs(const std::string& path);

/**
 * 重命名/移动文件或目录（类似os.rename）
 */
bool rename(const std::string& oldpath, const std::string& newpath);

/**
 * 复制文件（类似shutil.copy2的部分功能）
 */
bool copyfile(const std::string& src, const std::string& dst);

/**
 * 获取环境变量（类似os.getenv）
 */
std::string getenv(const std::string& key);

/**
 * 设置环境变量（类似os.putenv）
 */
bool putenv(const std::string& key, const std::string& value);

/**
 * 获取用户主目录（类似os.path.expanduser）
 */
std::string expanduser();

/**
 * 替换路径中的~为用户主目录（类似os.path.expanduser）
 */
std::string expanduser(const std::string& path);

/**
 * 获取文件的权限位（类似os.stat）
 */
int getmode(const std::string& path);

/**
 * 修改文件权限（类似os.chmod）
 */
bool chmod(const std::string& path, int mode);

/**
 * 获取临时目录（类似tempfile.gettempdir）
 */
std::string gettempdir();

/**
 * 生成随机字符串（类似os.urandom的部分用途）
 */
std::string urandom(size_t length);

/**
 * 遍历目录树（类似os.walk的简化版）
 */
std::vector<std::string> walk(const std::string& root);

/**
 * 分隔符（类似os.sep）
 */
extern const char sep;

/**
 * 路径分隔符（类似os.pathsep）
 */
extern const char pathsep;

/**
 * 行结束符（类似os.linesep）
 */
std::string linesep();

// ===================== 实用工具函数 =====================

/**
 * 读取整个文件内容（类似Python的open().read()）
 */
std::string read_file(const std::string& filename);

/**
 * 写入文件（类似Python的open().write()）
 */
bool write_file(const std::string& filename, const std::string& content);

/**
 * 追加到文件（类似Python的open().write()的追加模式）
 */
bool append_file(const std::string& filename, const std::string& content);

// ===================== 模板函数实现（必须在头文件中） =====================

namespace path {

template<typename... Args>
std::string join(const Args&... args) {
    std::vector<std::string> parts = {args...};
    return join(parts);
}

} // namespace path

} // namespace os

#endif // PYOS_HPP