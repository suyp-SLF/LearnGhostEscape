
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int, char **)
{
    std::cout << "Hello, World!" << std::endl;
    // SDL初始化
    // 1. 必须先初始化 SDL 核心音频
    if (!SDL_Init(SDL_INIT_AUDIO))
    {
        SDL_Log("SDL_Init 失败: %s", SDL_GetError());
        return -1;
    }
    // 创建窗口
    SDL_Window *window = SDL_CreateWindow("Hello World!", 800, 600, 0);
    // 创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    // SDL3_Image不需要手动初始化

    // 加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/sprite/ghost-idle.png");

    // 2. 初始化 Mixer 库
    // 参数 0 表示默认初始化。如果你需要特定格式，可以使用如 MIX_INIT_OGG
    if (!MIX_Init())
    {
        SDL_Log("MIX_Init 失败: %s", SDL_GetError());
        return -1;
    }
    // 1. 定义音频规格
    SDL_AudioSpec spec;
    SDL_zero(spec);              // 清零
    spec.format = SDL_AUDIO_S16; // 常用格式：16位发声
    spec.channels = 2;           // 立体声
    spec.freq = 44100;           // 采样率

    // 2. 调用函数 (传入 2 个参数)
    // 参数 1: SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK (通常是 0)
    // 参数 2: spec 的地址
    MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);

    if (!mixer)
    {
        SDL_Log("创建 Mixer 失败: %s", SDL_GetError());
        return -1;
    }



    // 读取音乐
    MIX_Audio *music = MIX_LoadAudio(mixer, "assets/bgm/OhMyGhost.ogg", false); // 播放音乐
    // --- 播放阶段 ---
    MIX_Track *track = MIX_CreateTrack(mixer); // 创建一条音轨
    // 或者设置音轨的音量
    MIX_SetTrackAudio(track, music);           // 将音频装载进音轨
    MIX_PlayTrack(track, 0);                   // 开始播放
    // SDL_TTF初始化
    if (!TTF_Init())
    {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    // 加载字体
    TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);

    // 创建文本纹理
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, SDL! 中文也可以", 0, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    //新文本绘制
    TTF_TextEngine *textEngine = TTF_CreateRendererTextEngine(renderer);
    TTF_Text *text = TTF_CreateText(textEngine, font, "Hello, SDL! 中文也可以111", 0);

    // 渲染循环
    while (true)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                break;
            }
        }

       // 1. 清屏 (所有绘制之前)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 建议设个黑色背景，方便观察白色文字
        SDL_RenderClear(renderer);

        // 2. 开始绘制各种对象
        // [绘制长方形]
        SDL_FRect rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        // [绘制图片]
        SDL_FRect dstrect = {200, 200, 200, 200};
        SDL_RenderTexture(renderer, texture, NULL, &dstrect);

        // [旧文本方式绘制]
        SDL_FRect textRect = {300, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

        // --- 【关键修改点】 ---
        // 必须在 Present 之前调用！
        // 建议换个坐标（如 50, 50），避免和上面的旧文本重叠导致看不清
        TTF_DrawRendererText(text, 50, 50); 

        // 3. 提交渲染 (交卷)
        SDL_RenderPresent(renderer);
    }

    // 清理图片资源
    SDL_DestroyTexture(texture);

    // 清理音乐资源
    MIX_DestroyAudio(music);
    MIX_DestroyMixer(mixer); // 对应以前的 Mix_CloseAudio(music);
    MIX_Quit();

    // 清理字体资源
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    //清理文本引擎TTF_TextEngine
    TTF_DestroyRendererTextEngine(textEngine);
    TTF_DestroyText(text);

    // 清理并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}