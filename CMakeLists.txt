# 标题
cmake_minimum_required(VERSION 3.10.0)
project(LearnGhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
elseif(APPLE)
    # 告诉编译器注入内存监控代码
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    # 告诉链接器链接内存监控库
    add_link_options(-fsanitize=address)
    message(STATUS "Mac Address Sanitizer (ASan) 已激活")
    add_compile_options(-Wall -Wextra -Wpedantic)
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
    src/core/data_struct.h
    src/core/object.cpp
    src/core/game.cpp
    src/core/object_screen.cpp
    src/core/object_world.cpp
    src/core/object_affiliate.cpp
    src/core/actor.cpp
    src/core/scene.cpp
    src/core/asset_store.cpp

    src/screen/ui_mouse.cpp
    src/screen/hud_stats.cpp
    src/screen/hud_skill.cpp
    src/screen/hud_text.cpp
    src/screen/hud_button.cpp

    src/raw/stats.cpp
    src/raw/weapon.cpp
    src/raw/timer.cpp
    src/raw/bg_star.cpp
    src/raw/move_control.cpp

    src/world/effect.cpp
    src/world/spell.cpp

    src/affiliate/sprite.cpp
    src/affiliate/sprite_anim.cpp
    src/affiliate/collider.cpp
    src/affiliate/affiliate_bar.cpp
    src/affiliate/text_label.cpp
    
    src/main.cpp
    src/player.cpp
    src/enemy.cpp
    src/scene_main.cpp
    src/spawner.cpp
    src/weapon_thunder.cpp
    src/scene_title.cpp
    src/move_control_arrow.cpp
    src/move_control_wasd.cpp
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