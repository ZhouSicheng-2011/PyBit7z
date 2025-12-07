#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#ifdef _WIN32
    #include <windows.h>
    #include <intrin.h>
    #include <psapi.h>
    #include <winternl.h>
    #pragma comment(lib, "psapi.lib")
    #pragma comment(lib, "ntdll.lib")
#elif __linux__
    #include <unistd.h>
    #include <sys/utsname.h>
    #include <sys/sysinfo.h>
    #include <fstream>
    #include <cstring>
#elif __APPLE__
    #include <sys/types.h>
    #include <sys/sysctl.h>
    #include <sys/utsname.h>
    #include <mach/mach.h>
    #include <mach/mach_host.h>
#endif

class SystemInfo {
private:
    std::string osName;
    std::string osVersion;
    std::string architecture;
    size_t totalMemory;    // in MB
    size_t availableMemory; // in MB
    int cpuCores;
    std::string cpuModel;
    std::string hostname;
    
    #ifdef _WIN32
        SYSTEM_INFO sysInfo;
        MEMORYSTATUSEX memoryStatus;
        OSVERSIONINFOEX osVersionInfo;
    #elif __linux__
        struct utsname unameInfo;
        struct sysinfo linuxSysInfo;
    #elif __APPLE__
        struct utsname unameInfo;
    #endif

public:
    SystemInfo() {
        detectOS();
        detectArchitecture();
        detectCPU();
        detectMemory();
        detectHostname();
    }

    // 获取所有系统信息的字符串表示
    std::string getAllInfo() const {
        std::ostringstream oss;
        oss << "========== 系统信息 ==========\n"
            << "操作系统: " << osName << "\n"
            << "系统版本: " << osVersion << "\n"
            << "主机名: " << hostname << "\n"
            << "系统架构: " << architecture << "\n"
            << "CPU型号: " << cpuModel << "\n"
            << "CPU核心数: " << cpuCores << "\n"
            << "总内存: " << formatMemory(totalMemory) << "\n"
            << "可用内存: " << formatMemory(availableMemory) << "\n"
            << "内存使用率: " << calculateMemoryUsage() << "%\n"
            << "==============================";
        return oss.str();
    }

    // 获取JSON格式的信息
    std::string getJsonInfo() const {
        std::ostringstream oss;
        oss << "{\n"
            << "  \"os_name\": \"" << osName << "\",\n"
            << "  \"os_version\": \"" << osVersion << "\",\n"
            << "  \"hostname\": \"" << hostname << "\",\n"
            << "  \"architecture\": \"" << architecture << "\",\n"
            << "  \"cpu_model\": \"" << cpuModel << "\",\n"
            << "  \"cpu_cores\": " << cpuCores << ",\n"
            << "  \"total_memory_mb\": " << totalMemory << ",\n"
            << "  \"available_memory_mb\": " << availableMemory << ",\n"
            << "  \"memory_usage_percent\": " << calculateMemoryUsage() << "\n"
            << "}";
        return oss.str();
    }

    // 各个信息的getter方法
    std::string getOSName() const { return osName; }
    std::string getOSVersion() const { return osVersion; }
    std::string getArchitecture() const { return architecture; }
    std::string getCPUModel() const { return cpuModel; }
    std::string getHostname() const { return hostname; }
    int getCPUCores() const { return cpuCores; }
    size_t getTotalMemory() const { return totalMemory; }
    size_t getAvailableMemory() const { return availableMemory; }
    double getMemoryUsage() const { return calculateMemoryUsage(); }

private:
    // 检测操作系统
    void detectOS() {
        #ifdef _WIN32
            osName = "Windows";
            
            // 检测Windows版本
            ZeroMemory(&osVersionInfo, sizeof(OSVERSIONINFOEX));
            osVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
            
            if (GetVersionEx((OSVERSIONINFO*)&osVersionInfo)) {
                std::ostringstream oss;
                oss << osVersionInfo.dwMajorVersion << "."
                    << osVersionInfo.dwMinorVersion << "."
                    << osVersionInfo.dwBuildNumber;
                
                // 判断Windows具体版本
                if (osVersionInfo.dwMajorVersion == 10) {
                    if (osVersionInfo.dwBuildNumber >= 22000) {
                        osName = "Windows 11";
                    } else {
                        osName = "Windows 10";
                    }
                } else if (osVersionInfo.dwMajorVersion == 6) {
                    if (osVersionInfo.dwMinorVersion == 3) {
                        osName = "Windows 8.1";
                    } else if (osVersionInfo.dwMinorVersion == 2) {
                        osName = "Windows 8";
                    } else if (osVersionInfo.dwMinorVersion == 1) {
                        osName = "Windows 7";
                    } else if (osVersionInfo.dwMinorVersion == 0) {
                        osName = "Windows Vista";
                    }
                }
                
                osVersion = oss.str();
            }
            
        #elif __linux__
            osName = "Linux";
            
            // 尝试读取/etc/os-release文件获取Linux发行版信息
            std::ifstream osRelease("/etc/os-release");
            if (osRelease.is_open()) {
                std::string line;
                while (std::getline(osRelease, line)) {
                    if (line.find("PRETTY_NAME=") != std::string::npos) {
                        size_t start = line.find('"');
                        size_t end = line.rfind('"');
                        if (start != std::string::npos && end != std::string::npos) {
                            osName = line.substr(start + 1, end - start - 1);
                        }
                    } else if (line.find("VERSION_ID=") != std::string::npos) {
                        size_t start = line.find('"');
                        size_t end = line.rfind('"');
                        if (start != std::string::npos && end != std::string::npos) {
                            osVersion = line.substr(start + 1, end - start - 1);
                        }
                    }
                }
                osRelease.close();
            }
            
            // 如果无法从os-release获取，使用uname
            if (osVersion.empty() && uname(&unameInfo) == 0) {
                osVersion = unameInfo.release;
            }
            
        #elif __APPLE__
            osName = "macOS";
            
            char version[256];
            size_t size = sizeof(version);
            if (sysctlbyname("kern.osproductversion", version, &size, NULL, 0) == 0) {
                osVersion = version;
            }
            
            if (uname(&unameInfo) == 0 && osVersion.empty()) {
                osVersion = unameInfo.release;
            }
            
        #else
            osName = "Unknown";
            osVersion = "Unknown";
        #endif
    }

    // 检测系统架构
    void detectArchitecture() {
        #ifdef _WIN32
            GetSystemInfo(&sysInfo);
            switch (sysInfo.wProcessorArchitecture) {
                case PROCESSOR_ARCHITECTURE_AMD64:
                    architecture = "x64";
                    break;
                case PROCESSOR_ARCHITECTURE_ARM:
                    architecture = "ARM";
                    break;
                case PROCESSOR_ARCHITECTURE_ARM64:
                    architecture = "ARM64";
                    break;
                case PROCESSOR_ARCHITECTURE_IA64:
                    architecture = "Itanium";
                    break;
                case PROCESSOR_ARCHITECTURE_INTEL:
                    architecture = "x86";
                    break;
                default:
                    architecture = "Unknown";
            }
        #elif __linux__ || __APPLE__
            if (uname(&unameInfo) == 0) {
                architecture = unameInfo.machine;
                
                // 转换为更易读的格式
                if (architecture == "x86_64") {
                    architecture = "x64";
                } else if (architecture == "i386" || architecture == "i686") {
                    architecture = "x86";
                } else if (architecture.find("arm") != std::string::npos) {
                    if (architecture.find("64") != std::string::npos) {
                        architecture = "ARM64";
                    } else {
                        architecture = "ARM";
                    }
                }
            } else {
                architecture = "Unknown";
            }
        #else
            architecture = "Unknown";
        #endif
    }

    // 检测CPU信息
    void detectCPU() {
        #ifdef _WIN32
            // 获取CPU核心数
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);
            cpuCores = sysInfo.dwNumberOfProcessors;
            
            // 获取CPU品牌字符串
            int CPUInfo[4] = {-1};
            char CPUString[0x40] = {0};
            
            __cpuid(CPUInfo, 0x80000000);
            unsigned int nExIds = CPUInfo[0];
            
            memset(CPUString, 0, sizeof(CPUString));
            
            for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
                __cpuid(CPUInfo, i);
                if (i == 0x80000002)
                    memcpy(CPUString, CPUInfo, sizeof(CPUInfo));
                else if (i == 0x80000003)
                    memcpy(CPUString + 16, CPUInfo, sizeof(CPUInfo));
                else if (i == 0x80000004)
                    memcpy(CPUString + 32, CPUInfo, sizeof(CPUInfo));
            }
            
            cpuModel = CPUString;
            
        #elif __linux__
            // 获取CPU核心数
            cpuCores = sysconf(_SC_NPROCESSORS_ONLN);
            
            // 读取/proc/cpuinfo获取CPU型号
            std::ifstream cpuinfo("/proc/cpuinfo");
            if (cpuinfo.is_open()) {
                std::string line;
                while (std::getline(cpuinfo, line)) {
                    if (line.find("model name") != std::string::npos) {
                        size_t colon = line.find(':');
                        if (colon != std::string::npos) {
                            cpuModel = line.substr(colon + 2);
                            break;
                        }
                    }
                }
                cpuinfo.close();
            }
            
        #elif __APPLE__
            // 获取CPU核心数
            int cores = 0;
            size_t len = sizeof(cores);
            sysctlbyname("hw.ncpu", &cores, &len, NULL, 0);
            cpuCores = cores;
            
            // 获取CPU型号
            char model[256];
            size_t size = sizeof(model);
            if (sysctlbyname("machdep.cpu.brand_string", model, &size, NULL, 0) == 0) {
                cpuModel = model;
            }
            
        #else
            cpuCores = 0;
            cpuModel = "Unknown";
        #endif
        
        // 清理CPU型号字符串中的多余空格
        if (!cpuModel.empty()) {
            std::string cleaned;
            bool lastWasSpace = false;
            for (char c : cpuModel) {
                if (std::isspace(c)) {
                    if (!lastWasSpace) {
                        cleaned += ' ';
                        lastWasSpace = true;
                    }
                } else {
                    cleaned += c;
                    lastWasSpace = false;
                }
            }
            cpuModel = cleaned;
        }
    }

    // 检测内存信息
    void detectMemory() {
        #ifdef _WIN32
            memoryStatus.dwLength = sizeof(memoryStatus);
            if (GlobalMemoryStatusEx(&memoryStatus)) {
                totalMemory = memoryStatus.ullTotalPhys / (1024 * 1024);
                availableMemory = memoryStatus.ullAvailPhys / (1024 * 1024);
            } else {
                totalMemory = 0;
                availableMemory = 0;
            }
            
        #elif __linux__
            if (sysinfo(&linuxSysInfo) == 0) {
                totalMemory = (linuxSysInfo.totalram * linuxSysInfo.mem_unit) / (1024 * 1024);
                availableMemory = (linuxSysInfo.freeram * linuxSysInfo.mem_unit) / (1024 * 1024);
            } else {
                totalMemory = 0;
                availableMemory = 0;
            }
            
        #elif __APPLE__
            int64_t mem = 0;
            size_t len = sizeof(mem);
            
            // 获取总内存
            if (sysctlbyname("hw.memsize", &mem, &len, NULL, 0) == 0) {
                totalMemory = mem / (1024 * 1024);
            }
            
            // 获取可用内存（macOS需要特殊处理）
            vm_size_t page_size;
            mach_port_t mach_port;
            mach_msg_type_number_t count;
            vm_statistics64_data_t vm_stats;
            
            mach_port = mach_host_self();
            count = sizeof(vm_stats) / sizeof(natural_t);
            if (host_page_size(mach_port, &page_size) == KERN_SUCCESS &&
                host_statistics64(mach_port, HOST_VM_INFO, 
                                (host_info64_t)&vm_stats, &count) == KERN_SUCCESS) {
                long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
                availableMemory = free_memory / (1024 * 1024);
            }
            
        #else
            totalMemory = 0;
            availableMemory = 0;
        #endif
    }

    // 检测主机名
    void detectHostname() {
        #ifdef _WIN32
            char buffer[MAX_COMPUTERNAME_LENGTH + 1];
            DWORD size = sizeof(buffer);
            if (GetComputerNameA(buffer, &size)) {
                hostname = buffer;
            } else {
                hostname = "Unknown";
            }
        #elif __linux__ || __APPLE__
            char buffer[256];
            if (gethostname(buffer, sizeof(buffer)) == 0) {
                hostname = buffer;
            } else {
                hostname = "Unknown";
            }
        #else
            hostname = "Unknown";
        #endif
    }

    // 计算内存使用率
    double calculateMemoryUsage() const {
        if (totalMemory == 0) return 0.0;
        return 100.0 * (1.0 - (double)availableMemory / (double)totalMemory);
    }

    // 格式化内存显示（自动转换为合适的单位）
    std::string formatMemory(size_t memoryMB) const {
        std::ostringstream oss;
        if (memoryMB >= 1024) {
            double memoryGB = memoryMB / 1024.0;
            oss.precision(2);
            oss << std::fixed << memoryGB << " GB";
        } else {
            oss << memoryMB << " MB";
        }
        return oss.str();
    }
};

