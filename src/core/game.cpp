#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

void Game::run()
{
    // 游戏主循环
    while (_is_running)
    {
        SDL_Event event;
        auto start = SDL_GetTicksNS(); // 获取当前时间
        // 1. 处理消息：告诉 Mac “我还活着”
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) _is_running = false;
        }
        handleEvents(&event); // 必须处理事件，否则窗口无法关闭且会转圈圈
        update();
        render();
        
        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < _frame_delay)
        {
            SDL_DelayNS(_frame_delay - elapsed); // 简单限帧，防止 CPU 100%
            _dt = _frame_delay / 1.0e9;
        }else{
            _dt = elapsed / 1.0e9;
        }
    }
}
void Game::init(std::string title, int width, int height)
{
    // 初始化SDL3，如果失败则退出
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL初始化失败: %s\n", SDL_GetError());
        _is_running = false;
        return;
    }
    // 不需要SDL_image初始化
    // 初始化SDL_Mixer
    // 必须先调用 MIX_Init (SDL3_mixer 需要它来加载底层驱动)
    if (!MIX_Init())
    {
        SDL_Log("MIX_Init 失败: %s", SDL_GetError());
        _is_running = false;
        return;
    }
    // 定义音频规格
    SDL_AudioSpec spec;
    SDL_zero(spec);              // 清零
    spec.format = SDL_AUDIO_S16; // 常用格式：16位发声
    spec.channels = 2;           // 立体声
    spec.freq = 44100;           // 采样率
    // 创建音频设备
    _mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);

    if (!_mixer)
    {
        SDL_Log("创建 Mixer 失败: %s\n", SDL_GetError());
        _is_running = false;
        return;
    }

    // SDL3 TTF初始化
    if (!TTF_Init())
    {
        SDL_Log("SDL_TTF初始化失败 : %s\n", SDL_GetError());
        _is_running = false;
        return;
    }

    // SDL3创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &_window, &_renderer);

    _frame_delay = 1.0e9 / 60; // 60帧每秒
}

void Game::handleEvents(SDL_Event *event)
{
}

void Game::update()
{
}

void Game::render()
{
}

void Game::clean()
{
    //  qSDL3销毁窗口与渲染器
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    // SDL3销毁TTF
    TTF_Quit();
    // SDL3销毁Mixer
    MIX_DestroyMixer(_mixer);
    MIX_Quit();
    // SDL3销毁SDL
    SDL_Quit();
}
