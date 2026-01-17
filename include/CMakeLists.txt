cmake_minimum_required(VERSION 3.10)
project(pyos VERSION 1.0.0 LANGUAGES CXX)

# 设置默认构建类型为Release
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "构建类型" FORCE)
    message(STATUS "未指定构建类型，默认使用: ${CMAKE_BUILD_TYPE}")
endif()

# 构建选项
option(BUILD_SHARED_LIBS "构建动态库而不是静态库" OFF)
option(BUILD_EXAMPLES "构建示例程序" ON)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 生成导出头文件
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pyos_export.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/pyos_export.h"
)

# 输出目录组织
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Windows/MSVC特定设置
if(MSVC)
    # 编码设置
    add_compile_options(/utf-8)
    
    # 禁用安全警告和编码警告
    add_compile_options(/wd4996 /wd4819 /wd4251)
    
    # 安全宏定义
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    
    # 优化设置
    string(TOUPPER "${CMAKE_BUILD_TYPE}" UPPER_BUILD_TYPE)
    if(UPPER_BUILD_TYPE STREQUAL "RELEASE")
        add_compile_options(/O2 /Ob2 /DNDEBUG)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
    elseif(UPPER_BUILD_TYPE STREQUAL "DEBUG")
        add_compile_options(/Zi /Od /RTC1)
    endif()
    
    # Windows动态库设置
    if(BUILD_SHARED_LIBS)
        # 自动导出所有符号（简化方式）
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        # 添加导出宏定义
        add_definitions(-DPYOS_EXPORTS)
    endif()
else()
    # GCC/Clang设置
    add_compile_options(-Wall -Wextra -Wpedantic)
    
    # 位置无关代码（支持动态库）
    if(BUILD_SHARED_LIBS)
        add_compile_options(-fPIC)
        add_definitions(-DPYOS_EXPORTS)
    endif()
    
    # 优化设置
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-O0 -g -DDEBUG)
    endif()
endif()

# 设置源文件
set(SOURCES pyos.cpp)

# 添加包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 添加库目标（根据BUILD_SHARED_LIBS决定构建静态库还是动态库）
add_library(pyos ${SOURCES})

# 设置目标属性
set_target_properties(pyos PROPERTIES
    OUTPUT_NAME "pyos"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Windows下为动态库设置导入库名称
if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(pyos PROPERTIES
        IMPORT_SUFFIX ".lib"
        IMPORT_PREFIX ""
    )
endif()

# 安装配置
install(TARGETS pyos
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# 安装头文件
install(FILES pyos.hpp
    DESTINATION include
)

# 安装导出头文件
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pyos_export.h
    DESTINATION include
)

# 构建示例程序
if(BUILD_EXAMPLES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/example.cpp")
    add_executable(pyos_example example.cpp)
    
    # 为示例程序添加导出头文件目录
    target_include_directories(pyos_example PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    
    # 链接库
    target_link_libraries(pyos_example pyos)
    
    # 安装示例程序
    install(TARGETS pyos_example
        DESTINATION bin
    )
endif()

# 创建别名目标，方便使用
add_library(pyos::pyos ALIAS pyos)

# 输出总结信息
message(STATUS "")
message(STATUS "=========================================")
message(STATUS "pyos 库构建配置")
message(STATUS "=========================================")
message(STATUS "项目版本: ${PROJECT_VERSION}")
message(STATUS "构建类型: ${CMAKE_BUILD_TYPE}")
if(BUILD_SHARED_LIBS)
    message(STATUS "库类型: 动态库")
else()
    message(STATUS "库类型: 静态库")
endif()
message(STATUS "C++标准: ${CMAKE_CXX_STANDARD}")
message(STATUS "构建示例程序: ${BUILD_EXAMPLES}")
message(STATUS "安装前缀: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "=========================================")