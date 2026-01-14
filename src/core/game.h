#ifndef GAME_H
#define GAME_H

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/glm.hpp>
class Game
{
private:
    // -- 参数 --
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    MIX_Mixer *_mixer = nullptr;
    glm::vec2 _screen_size = glm::vec2(800, 600); // 屏幕大小

    Uint64 _FPS = 60; // 帧率
    Uint64 _frame_delay = 0; // 帧间隔时间，单位纳秒
    float _dt = 0; // 时间间隔,单位秒

    // -- 游戏状态 --
    bool _is_running = true; // 游戏是否运行

    // -- 单例 --
    Game(){};// 私有构造函数
    // 禁止拷贝构造函数与赋值操作符
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    // -- 参数 --

    // -- 获取单例实例 --
     static Game& GetInstance()
    {
        static Game instance;
        return instance;
    }
    // -- 游戏主循环 --
    void run();                                          // 运行游戏主循环
    void init(std::string title, int width, int height); // 初始化
    void handleEvents(SDL_Event *event);                                 // 处理事件
    void update();                                       // 更新游戏状态
    void render();                                       // 渲染游戏
    void clean();                                        // 清理游戏资源
};
#endif // GAME_H