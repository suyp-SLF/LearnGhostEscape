#ifndef GAME_H
#define GAME_H

#define DEBUG_MDOE

#include "asset_store.h"
#include "data_struct.h"

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
#include <glm/glm.hpp>
#include <random>

struct Texture;
class Scene;
class Game
{
private:
    // -- 游戏资源 --
    AssetStore *_asset_store = nullptr; // 资源存储
    // -- 音乐 --
    // 背景音乐专用
    MIX_Track *_bgm_track = nullptr;
    std::string _current_music_path = ""; // 记录当前播放的音乐路径，防止重复加载播放
    // 音轨池：固定 8 条音轨用于音效
    static const int TRACK_POOL_SIZE = 8;
    std::vector<MIX_Track *> _effect_tracks;
    int _next_track_index = 0; // 轮询计数器
    // -- 参数 --
    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    MIX_Mixer *_mixer = nullptr;
    Scene *_current_scene = nullptr;       // 当前场景
    Scene *_next_scene = nullptr;             // 下一个场景
    TTF_Font *_font = nullptr;             // 字体
    TTF_TextEngine *_textEngine = nullptr; // 文字引擎
    TTF_Text *_text = nullptr;             // 文字

    TTF_Text *_textVe = nullptr; // 文字

    glm::vec2 _mouse_position = glm::vec2(0);     // 鼠标位置
    SDL_MouseButtonFlags _mouse_button_state = 0; // 鼠标按键状态

    glm::vec2 _screen_size = glm::vec2(0); // 屏幕大小
    Uint64 _FPS = 144;                     // 帧率
    Uint64 _frame_delay = 0;               // 帧间隔时间，单位纳秒
    float _dt = 0;                         // 时间间隔,单位秒

    int _high_score = 0;
    // -- 游戏状态 --
    bool _is_running = true; // 游戏是否运行

    // -- 随机数 --
    std::mt19937 _random_generator = std::mt19937(std::random_device{}()); // 随机数生成器

    // -- 单例 --
    Game() {}; // 私有构造函数
    // 禁止拷贝构造函数与赋值操作符
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

public:
    // -- 参数 --

    // -- 获取单例实例 --
    static Game &GetInstance()
    {
        static Game instance;
        return instance;
    }
    // -- 游戏主循环 --
    void run();                                          // 运行游戏主循环
    void init(std::string title, int width, int height); // 初始化
    bool handleEvents();                                 // 处理事件
    void update(float dt);                               // 更新游戏状态
    void render();                                       // 渲染游戏
    void clean();                                        // 清理游戏资源

    void quit() {_is_running = false;} // 退出游戏
    void changeScene(Scene *scene); // 切换场景
    void safeChangeScene(Scene *scene) {_next_scene = scene; } // 安全切换场景

    // getter and setter
    glm::vec2 getScreenSize() const { return _screen_size; }   // 获取屏幕大小
    Scene *getCurrentScene() const { return _current_scene; }  // 获取当前场景
    AssetStore *getAssetStore() const { return _asset_store; } // 获取资源存储
    glm::vec2 getMousePosition() const { return _mouse_position; }
    SDL_MouseButtonFlags getMouseButtonState() const { return _mouse_button_state; }
    TTF_Text *getTextVe() const { return _textVe; }
    void setHighScore(int score) { _high_score = score; }
    int getHighScore() const { return _high_score; }

    // 随机数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(_random_generator); }          // 生成一个[min, max)之间的随机浮点数
    float randowInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(_random_generator); }                   // 生成一个[min, max)之间的随机整数
    glm::vec2 randomVec2(glm::vec2 min, glm::vec2 max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }  // 生成一个[min, max)之间的随机二维浮点数向量
    glm::ivec2 randomIvec2(glm::ivec2 min, glm::ivec2 max) { return glm::ivec2(randowInt(min.x, max.x), randowInt(min.y, max.y)); } // 生成一个[min, max)之间的随机二维整数向量
    // 音乐
    void playMusic(const std::string &music_path, int loops = -1); // 播放音乐
    void stopMusic();                                              // 停止音乐
    void pauseMusic();                                             // 暂停音乐
    void resumeMusic();                                            // 恢复音乐
    // 音效
    void playSoundEffect(const std::string &sound_path); // 播放音效
    void pauseAllSoundEffects();                             // 停止所有音效
    void resumeAllSoundEffects();                            // 恢复所有音效
    // 渲染图片
    void drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask, float alpha, glm::vec3 color);
    void drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask = glm::vec2(1.f), float alpha = 1.f); // 绘制图片
    // 文字
    TTF_Text *createTTFText(const std::string &content, const std::string &font_path, int font_size = 12);
    // 工具类
    // 用于绘制网格,offset_x和offset_y为网格的偏移量
    void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float cell_size, const glm::vec2 offset, const SDL_FColor color); // 绘制网格
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const glm::vec4 color);                    // 绘制边界
    void drawRect(const RectData &data);                                                                                                      // 绘制矩形
    void drawFPS(const glm::vec2 &position, const SDL_FColor color);                                                                          // 绘制FPS
    void drawText(const std::string &content, glm::vec2 position, glm::vec4 color = glm::vec4(1.0f));
    void drawHBar(const glm::vec2 &position, const glm::vec2 &size, float value, const glm::vec4 color); // 绘制水平进度条
    void drawPoint(const std::vector<glm::vec2> &points, const glm::vec2 render_pos, glm::vec4 color); // 绘制点
    // 碰撞检测
    bool isMouseInRect(const RectData &data);
    // 读取文件
    std::string loadTextFile(const std::string &path);
private:
    void updateMouse();
};
#endif // GAME_H