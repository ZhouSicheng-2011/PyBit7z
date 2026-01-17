// example.cpp - 使用pyos库的示例
// 在包含pyos.hpp之前先包含导出头文件
#ifdef _WIN32
    #ifdef _DEBUG
        #define PYOS_DEBUG
    #endif
#endif

#include "pyos_export.h"
#include "pyos.hpp"
#include <iostream>

int main() {
    std::cout << "=== pyos 库使用示例 ===" << std::endl;
    
    // 1. os.path 相关功能
    std::cout << "\n1. 路径操作测试:" << std::endl;
    
    std::string joined_path = os::path::join({"dir1", "dir2", "file.txt"});
    std::cout << "os::path::join: " << joined_path << std::endl;
    
    // 使用模板版本
    std::string joined_path2 = os::path::join("dir1", "dir2", "file.txt");
    std::cout << "os::path::join (模板): " << joined_path2 << std::endl;
    
    std::string abs_path = os::path::abspath("example.cpp");
    std::cout << "os::path::abspath: " << abs_path << std::endl;
    
    std::string base_name = os::path::basename("/home/user/file.txt");
    std::cout << "os::path::basename: " << base_name << std::endl;
    
    bool file_exists = os::path::exists("example.cpp");
    std::cout << "os::path::exists('example.cpp'): " << (file_exists ? "true" : "false") << std::endl;
    
    // 2. os 相关功能
    std::cout << "\n2. 系统操作测试:" << std::endl;
    
    std::string cwd = os::getcwd();
    std::cout << "当前目录: " << cwd << std::endl;
    
    // 创建测试目录
    std::string test_dir = "test_dir";
    if (os::mkdir(test_dir)) {
        std::cout << "创建目录成功: " << test_dir << std::endl;
        
        // 创建测试文件
        std::vector<std::string> parts = {test_dir, "test.txt"};
        std::string test_file = os::path::join(parts);
        
        if (os::write_file(test_file, "Hello, World!")) {
            std::cout << "创建文件成功: " << test_file << std::endl;
            
            // 获取文件大小
            auto file_size = os::path::getsize(test_file);
            std::cout << "文件大小: " << file_size << " bytes" << std::endl;
            
            // 读取文件
            std::string content = os::read_file(test_file);
            std::cout << "文件内容: " << content << std::endl;
        }
        
        // 清理测试目录
        os::removedirs(test_dir);
        std::cout << "清理测试目录" << std::endl;
    }
    
    // 3. 环境变量操作
    std::cout << "\n3. 环境变量测试:" << std::endl;
    
    std::string home = os::getenv("HOME");
    if (home.empty()) home = os::getenv("USERPROFILE");
    std::cout << "家目录环境变量: " << home << std::endl;
    
    // 4. 系统信息
    std::cout << "\n4. 系统信息:" << std::endl;
    
    std::string temp_dir = os::gettempdir();
    std::cout << "临时目录: " << temp_dir << std::endl;
    
    std::cout << "路径分隔符: " << os::sep << std::endl;
    std::cout << "路径列表分隔符: " << os::pathsep << std::endl;
    std::cout << "行结束符: " << os::linesep();
    
    return 0;
}