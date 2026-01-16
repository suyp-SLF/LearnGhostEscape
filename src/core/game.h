#ifndef GAME_H
#define GAME_H

#include "asset_store.h"

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/glm.hpp>

class Scene;
class Game
{
private:
    // -- 游戏资源 --
    AssetStore *_asset_store = nullptr; // 资源存储
    // -- 参数 --
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    MIX_Mixer *_mixer = nullptr;
    Scene* _current_scene = nullptr; // 当前场景
    TTF_Font *_font = nullptr; // 字体
    TTF_TextEngine *_textEngine = nullptr; // 文字引擎
    TTF_Text *_text = nullptr; // 文字
    
    glm::vec2 _screen_size = glm::vec2(0); // 屏幕大小
    Uint64 _FPS = 144; // 帧率
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
    void handleEvents();                                 // 处理事件
    void update(float dt);                                 // 更新游戏状态
    void render();                                       // 渲染游戏
    void clean();                                        // 清理游戏资源

    // getter and setter
    glm::vec2 getScreenSize() const { return _screen_size; } // 获取屏幕大小
    Scene* getCurrentScene() const { return _current_scene; }   // 获取当前场景
    AssetStore* getAssetStore() const { return _asset_store; } // 获取资源存储

    // 工具类,用于绘制网格,offset_x和offset_y为网格的偏移量
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float cell_size, const glm::vec2 offset, const SDL_FColor color); // 绘制网格
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const SDL_FColor color); // 绘制边界
    void drawFPS(const glm::vec2 &position, const SDL_FColor color); // 绘制FPS
};
#endif // GAME_H