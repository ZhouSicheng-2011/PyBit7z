cmake_minimum_required(VERSION 3.10)
project(pyos)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 构建选项
option(BUILD_SHARED_LIBS "构建动态库而不是静态库" ON)
option(BUILD_EXAMPLES "构建示例程序" ON)

# Windows设置
if(MSVC)
    add_compile_options(/utf-8 /wd4996 /wd4819)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 创建库
add_library(pyos pyos.cpp)

# 设置库属性
set_target_properties(pyos PROPERTIES
    OUTPUT_NAME "pyos"
)

# 创建示例程序
if(BUILD_EXAMPLES)
    add_executable(pyos_example example.cpp)
    target_link_libraries(pyos_example pyos)
endif()

# 安装
install(TARGETS pyos
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES pyos.hpp
    DESTINATION include
)