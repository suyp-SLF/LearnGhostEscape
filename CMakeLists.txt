# 标题
cmake_minimum_required(VERSION 3.10.0)
project(LearnGhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# --- 关键：强制只查找你自定义的路径 ---
set(MY_SDL_BASE "/Users/suyp/C++/Library/build")
set(CMAKE_PREFIX_PATH "${MY_SDL_BASE}")
# 告诉 CMake 不要去系统默认路径（如 Homebrew）乱找
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm CONFIG REQUIRED)

# 添加可执行文件
add_executable(
    ${TARGET} 
    src/main.cpp
    src/core/game.cpp
    )

# 这样编译器才能进入 /Users/suyp/C++/Library/build/include 找到 SDL3_mixer 文件夹
target_include_directories(${TARGET} PRIVATE "${MY_SDL_BASE}/include")

# 链接库
target_link_libraries(
    ${TARGET}
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
    )