cmake_minimum_required(VERSION 3.10)
project(pyos)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 默认构建类型为Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 构建选项
option(BUILD_SHARED_LIBS "构建动态库" OFF)
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

# 创建库目标
if(BUILD_SHARED_LIBS)
    message(STATUS "构建动态库")
    add_library(pyos SHARED pyos.cpp)
else()
    message(STATUS "构建静态库")
    add_library(pyos STATIC pyos.cpp)
endif()

# 设置目标属性
set_target_properties(pyos PROPERTIES
    OUTPUT_NAME "pyos"
)

# 创建示例程序
if(BUILD_EXAMPLES)
    add_executable(example example.cpp)
    target_link_libraries(example pyos)
endif()

# 安装配置
install(TARGETS pyos
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES pyos.hpp
    DESTINATION include
)

if(BUILD_EXAMPLES)
    install(TARGETS example
        DESTINATION bin
    )
endif()