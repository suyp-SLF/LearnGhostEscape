#include "game.h"
#include "../scene_main.h"

#include "actor.h"
#include "../player.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

void Game::run()
{
    // 游戏主循环
    while (_is_running)
    {

        auto start = SDL_GetTicksNS(); // 获取当前时间
        handleEvents();                // 必须处理事件，否则窗口无法关闭且会转圈圈
        update(_dt);
        render();

        auto end = SDL_GetTicksNS();
        auto elapsed = end - start;
        if (elapsed < _frame_delay)
        {
            SDL_DelayNS(_frame_delay - elapsed); // 简单限帧，防止 CPU 100%
            _dt = _frame_delay / 1.0e9;
        }
        else
        {
            _dt = elapsed / 1.0e9;
        }
    }
}
void Game::init(std::string title, int width, int height)
{
    _screen_size = glm::vec2(width, height);
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
    // SDL3创建窗口与渲染器
    // --- Window ---
    SDL_PropertiesID window_props = SDL_CreateProperties();

    SDL_SetStringProperty(window_props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, title.c_str());
    SDL_SetNumberProperty(window_props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty(window_props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
    SDL_SetNumberProperty(window_props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
    SDL_SetNumberProperty(window_props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);

    // 重要：macOS 开启 Retina 高分屏支持
    SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);
    SDL_SetBooleanProperty(window_props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);

    _window = SDL_CreateWindowWithProperties(window_props);
    SDL_DestroyProperties(window_props); // 立即释放

    if (!_window)
    {
        SDL_Log("窗口创建失败: %s", SDL_GetError());
        _is_running = false;
        return;
    }

    // --- Renderer ---
    SDL_PropertiesID render_props = SDL_CreateProperties();
    SDL_SetPointerProperty(render_props, SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, _window);

    // 如果你想尝试显式指定 Metal 驱动（macOS 性能更好）
    // SDL_SetStringProperty(render_props, SDL_PROP_RENDERER_CREATE_NAME_STRING, "metal");

    _renderer = SDL_CreateRendererWithProperties(render_props);
    SDL_DestroyProperties(render_props); // 立即释放

    if (!_renderer)
    {
        SDL_Log("渲染器创建失败: %s", SDL_GetError());
        _is_running = false;
        return;
    }

    // --- 后续关键设置 ---

    // 1. 设置垂直同步 (VSync) - 解决线条断开/撕裂的核心
    // 这里的 1 表示开启。这是 SDL3 最稳定的设置方式。
    if (!SDL_SetRenderVSync(_renderer, 1))
    {
        SDL_Log("警告: 无法设置 VSync: %s", SDL_GetError());
    }

    // 2. 设置缩放质量为线性采样（会让移动中的线条边缘更平滑一些）
    // 在 SDL2 中是 "0" 或 "nearest"，在 SDL3 中最稳妥的写法是：
    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "0");

    // 3. 开启逻辑与物理像素的自动缩放 (HighDPI 适配)
    // 这确保了在 Retina 屏上，虽然像素变多了，但你的坐标系依然是你设定的 width/height
    SDL_SetRenderLogicalPresentation(_renderer, width, height,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);
    // SDL3 TTF初始化
    if (!TTF_Init())
    {
        SDL_Log("SDL_TTF初始化失败 : %s\n", SDL_GetError());
        _is_running = false;
        return;
    }
    // 新文本绘制
    _textEngine = TTF_CreateRendererTextEngine(_renderer);
    // 加载字体
    _font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);
    if (!_font)
    {
        // 关键：打印出具体错误原因，比如 "No such file or directory"
        SDL_Log("字体加载失败！错误原因: %s\n", SDL_GetError());
        SDL_Log("当前工作目录路径，请确认 assets 文件夹是否在此目录下。");
    }
    _text = TTF_CreateText(_textEngine, _font, "FPS: 60", 0);

    // --创建资源管理器
    _asset_store = new AssetStore(_renderer, _mixer);

    _frame_delay = 1.0e9 / _FPS; // 60帧每秒

    _current_scene = new SceneMain();
    _current_scene->init();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            _is_running = false;
            break;
        default:
            _current_scene->handleEvents(event);
        }
    }
}

void Game::update(float dt)
{
    if (_text)
    {
        char buffer[64];
        // dt * 1000 得到毫秒数
        float ms = dt * 1000.0f;
        float fps = (dt > 0) ? (1.0f / dt) : 0;

        SDL_snprintf(buffer, sizeof(buffer), "FPS: %.1f  Time: %.2f ms", fps, ms);

        // 更新 SDL3_ttf 文本内容
        TTF_SetTextString(_text, buffer, 0);
    }
    _current_scene->update(dt);
}

void Game::render()
{
    SDL_SetRenderDrawColor(_renderer, 100, 100, 100, 255);
    SDL_RenderClear(_renderer);
    _current_scene->render();
    SDL_RenderPresent(_renderer);
}

void Game::clean()
{
    // 清理当前场景
    if (_current_scene)
    {
        _current_scene->clean();
        delete _current_scene;
        _current_scene = nullptr;
    }
    //清理资源管理器
    if (_asset_store)
    {
        _asset_store->clean();
        delete _asset_store;
    }
    // 清理文本引擎TTF_TextEngine
    if (_textEngine)
    {
        TTF_DestroyRendererTextEngine(_textEngine);
    }
    if (_text)
    {
        TTF_DestroyText(_text);
    }
    //  qSDL3销毁窗口与渲染器
    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window)
    {
        SDL_DestroyWindow(_window);
    }
    // SDL3销毁TTF
    TTF_Quit();
    // SDL3销毁Mixer
    MIX_DestroyMixer(_mixer);
    MIX_Quit();
    // SDL3销毁SDL
    SDL_Quit();
}
void Game::drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float cell_size, const glm::vec2 offset, const SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(_renderer, color.r, color.g, color.b, color.a);
    // 划线
    for (float x = top_left.x; x <= bottom_right.x; x += cell_size)
    {
        SDL_RenderLine(_renderer, x + offset.x, top_left.y + offset.y, x + offset.x, bottom_right.y + offset.y);
    }
    for (float y = top_left.y; y <= bottom_right.y; y += cell_size)
    {
        SDL_RenderLine(_renderer, top_left.x + offset.x, y + offset.y, bottom_right.x + offset.x, y + offset.y);
    }
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}

void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(_renderer, color.r, color.g, color.b, color.a);
    for (size_t i = 0; i < grid_width; i++)
    {
        SDL_FRect rect = {
            top_left.x - i,
            top_left.y - i,
            bottom_right.x - top_left.x + 2 * i,
            bottom_right.y - top_left.y + 2 * i};
        SDL_RenderRect(_renderer, &rect);
    }
    SDL_SetRenderDrawColorFloat(_renderer, 0, 0, 0, 1);
}
void Game::drawFPS(const glm::vec2 &position, const SDL_FColor color)
{
    if (!_text)
        return;

    // 1. 【重中之重】将渲染颜色设为纯白
    // 几何渲染会把这个颜色和文字纹理相乘。如果是黑色，字就消失了。
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    // 2. 显式开启混合模式
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    // 3. 设置文字内部颜色（转化为 0-255）
    TTF_SetTextColor(_text,
                     (Uint8)(color.r * 255),
                     (Uint8)(color.g * 255),
                     (Uint8)(color.b * 255),
                     (Uint8)(color.a * 255));

    // 4. 执行绘制
    if (!TTF_DrawRendererText(_text, position.x, position.y))
    {
        SDL_Log("TTF_DrawRendererText 失败: %s", SDL_GetError());
    }

    // 5. 绘制完后把颜色改回黑色（为了不影响你的 drawGrid 逻辑）
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}