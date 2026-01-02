cmake_minimum_required(VERSION 3.10)
project(pyos VERSION 1.0.0 LANGUAGES CXX)

# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 源文件
set(SOURCES pyos.cpp)

# 头文件
set(HEADERS pyos.hpp)

# 创建静态库
add_library(pyos_static STATIC ${SOURCES})
set_target_properties(pyos_static PROPERTIES
    OUTPUT_NAME pyos
    PUBLIC_HEADER "${HEADERS}"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# 创建动态库
add_library(pyos_shared SHARED ${SOURCES})
set_target_properties(pyos_shared PROPERTIES
    OUTPUT_NAME pyos
    PUBLIC_HEADER "${HEADERS}"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# 安装配置
install(TARGETS pyos_static pyos_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# 创建别名目标，方便使用
add_library(pyos::static ALIAS pyos_static)
add_library(pyos::shared ALIAS pyos_shared)

# 示例程序（可选）
if(BUILD_EXAMPLES)
    add_executable(example examples/example.cpp)
    target_link_libraries(example pyos_static)
    install(TARGETS example DESTINATION bin)
endif()

# 测试程序（可选）
if(BUILD_TESTS)
    enable_testing()
    add_executable(test_pyos tests/test_pyos.cpp)
    target_link_libraries(test_pyos pyos_static)
    add_test(NAME pyos_test COMMAND test_pyos)
endif()