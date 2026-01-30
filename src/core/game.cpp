#include "game.h"
#include "../scene_main.h"
#include "../scene_title.h"

#include "actor.h"
#include "../player.h"
#include "../affiliate/sprite.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <fstream>

void Game::run()
{
    // 游戏主循环
    while (_is_running)
    {
        auto start = SDL_GetTicksNS(); // 获取当前时间
        if (_next_scene)
        {
            changeScene(_next_scene);
            _next_scene = nullptr;
        }
        handleEvents(); // 必须处理事件，否则窗口无法关闭且会转圈圈
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
    // 1. 创建背景音乐专用音轨 (背景音乐线)
    _bgm_track = MIX_CreateTrack(_mixer);

    // 2. 创建音效音轨池 (预留 8 条线)
    for (int i = 0; i < TRACK_POOL_SIZE; ++i)
    {
        MIX_Track *trk = MIX_CreateTrack(_mixer);
        if (trk)
        {
            _effect_tracks.push_back(trk);
        }
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
    _textVe = TTF_CreateText(_textEngine, _font, "FPS: 60", 0);

    // --创建资源管理器
    _asset_store = new AssetStore(_renderer, _mixer);

    _frame_delay = 1.0e9 / _FPS; // 60帧每秒

    _current_scene = new SceneTitle();
    _current_scene->init();
}

bool Game::handleEvents()
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
            if (_current_scene->handleEvents(event))
                return true;
        }
    }
    return false;
}

void Game::update(float dt)
{
    _mouse_button_state = SDL_GetMouseState(&_mouse_position.x, &_mouse_position.y);
    // 更新
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
    drawFPS({100.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
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
    // 销毁背景音乐音轨
    if (_bgm_track)
    {
        MIX_DestroyTrack(_bgm_track);
        _bgm_track = nullptr;
    }
    // ------音乐-------
    // 销毁音轨池
    for (auto trk : _effect_tracks)
    {
        MIX_DestroyTrack(trk);
    }
    _effect_tracks.clear();

    // 销毁资源管理器（它会释放 MIX_Audio）
    if (_asset_store)
    {
        _asset_store->clean();
        delete _asset_store;
    }

    // 销毁 Mixer
    MIX_DestroyMixer(_mixer);
    MIX_Quit();
    // SDL3销毁SDL
    SDL_Quit();
}
void Game::changeScene(Scene *scene)
{
    if (_current_scene)
    {
        _current_scene->clean();
        delete _current_scene;
    }
    _current_scene = scene;
    _current_scene->init();
}
void Game::playMusic(const std::string &music_path, int loops)
{
    if (!_bgm_track)
        return;

    // 1. 优化：如果已经在播放这首歌，就直接返回，避免重启音乐
    if (_current_music_path == music_path)
    {
        return;
    }

    // 2. 停止当前播放并解绑音频
    MIX_SetTrackAudio(_bgm_track, nullptr);

    // 3. 从资源管理器获取音频
    // 注意：AssetStore::getMusic 内部应该是 MIX_LoadAudio(..., true) 以开启流式加载
    MIX_Audio *music = _asset_store->getMusic(music_path);

    if (music)
    {
        // 4. 绑定音频到背景音轨
        MIX_SetTrackAudio(_bgm_track, music);

        // 5. 开始播放
        // loops: 0 通常代表播放一次，-1 或更大的数代表循环次数
        MIX_PlayTrack(_bgm_track, loops);

        _current_music_path = music_path;
    }
}
void Game::stopMusic()
{
    if (_bgm_track)
    {
        MIX_SetTrackAudio(_bgm_track, nullptr); // 彻底移除音频
        _current_music_path = "";
    }
}
void Game::pauseMusic()
{
    // 暂停背景音乐
    if (_bgm_track)
        MIX_PauseTrack(_bgm_track);
}
void Game::resumeMusic()
{
    if (_bgm_track)
        MIX_ResumeTrack(_bgm_track);
}
void Game::playSoundEffect(const std::string &sound_path)
{
    if (_effect_tracks.empty())
        return;

    // 1. 从资源管理器获取音效 (is_stream 为 false)
    MIX_Audio *sound = _asset_store->getSound(sound_path);
    if (!sound)
        return;

    // 2. 轮询选择下一个音轨
    MIX_Track *target_track = _effect_tracks[_next_track_index];
    _next_track_index = (_next_track_index + 1) % TRACK_POOL_SIZE;

    // 3. 强制重置并播放
    // 先解绑当前可能正在播放的声音（相当于停止旧声音）
    MIX_SetTrackAudio(target_track, nullptr);
    // 绑定新音效
    MIX_SetTrackAudio(target_track, sound);
    // 播放 1 次 (loops = 1)
    MIX_PlayTrack(target_track, 1);
}
void Game::pauseAllSoundEffects()
{
    // 暂停音效池中的所有音轨 (防止暂停时脚步声还在响)
    for (auto trk : _effect_tracks)
    {
        MIX_PauseTrack(trk);
    }
}
void Game::resumeAllSoundEffects()
{
    // 恢复音效池
    for (auto trk : _effect_tracks)
    {
        MIX_ResumeTrack(trk);
    }
}
void Game::drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask, float alpha, glm::vec3 color)
{
    SDL_SetTextureColorModFloat(texture.texture, color.x, color.y, color.z);
    drawImage(texture, position, size, mask, alpha);
    SDL_SetTextureColorModFloat(texture.texture, 1.f, 1.f, 1.f);
}
void Game::drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &mask, float alpha)
{
    // 1. 设置混合模式（必须开启混合模式，Alpha 才会生效）
    SDL_SetTextureBlendMode(texture.texture, SDL_BLENDMODE_BLEND);

    // 2. 设置透明度调制 (将 0.0~1.0 映射到 0~255)
    Uint8 alpha_val = static_cast<Uint8>(alpha * 255.0f);
    SDL_SetTextureAlphaMod(texture.texture, alpha_val);

    SDL_FRect src_rect = {
        texture.src_rect.x,
        texture.src_rect.y,
        texture.src_rect.w * mask.x,
        texture.src_rect.h * mask.y};

    SDL_FRect dst_rect = {
        position.x,
        position.y,
        size.x * mask.x,
        size.y * mask.y};

    // 3. 执行绘制
    SDL_RenderTextureRotated(
        _renderer,
        texture.texture,
        &src_rect,
        &dst_rect,
        texture.angle,
        nullptr,
        texture.flip);

    // 4. 恢复透明度为不透明（防止同一个纹理在其他地方绘制时变透明）
    SDL_SetTextureAlphaMod(texture.texture, 255);
}
TTF_Text *Game::createTTFText(const std::string &content, const std::string &font_path, int font_size)
{
    auto font = getAssetStore()->getFont(font_path, font_size);
    return TTF_CreateText(_textEngine, font, content.c_str(), 0);
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

void Game::drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const glm::vec4 color)
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
void Game::drawRect(const RectData &data)
{
    // 1. 设置颜色 (GLM float 转 SDL Uint8)
    SDL_SetRenderDrawColor(_renderer,
                           static_cast<Uint8>(data.color.r * 255),
                           static_cast<Uint8>(data.color.g * 255),
                           static_cast<Uint8>(data.color.b * 255),
                           static_cast<Uint8>(data.color.a * 255));

    // 2. 开启混合模式
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    // 3. 构建 SDL 矩形
    SDL_FRect rect = {data.position.x, data.position.y, data.size.x, data.size.y};

    // 4. 绘制逻辑
    if (data.filled)
    {
        SDL_RenderFillRect(_renderer, &rect);
    }
    else
    {
        SDL_RenderRect(_renderer, &rect); // 画空心描边
    }
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
void Game::drawText(const std::string &content, glm::vec2 position, glm::vec4 color)
{
    if (!_textEngine || !_font)
        return;

    // 1. 创建临时文字对象（如果只是偶尔画一下）
    // 注意：如果是 FPS 这种每帧都在变的，建议像你之前那样使用成员变量 _text 以复用内存
    TTF_Text *tempText = TTF_CreateText(_textEngine, _font, content.c_str(), content.length());
    if (!tempText)
        return;

    // 2. 保存旧的混合模式和颜色 (SDL3 最佳实践)
    SDL_BlendMode oldMode;
    SDL_GetRenderDrawBlendMode(_renderer, &oldMode);
    Uint8 oldR, oldG, oldB, oldA;
    SDL_GetRenderDrawColor(_renderer, &oldR, &oldG, &oldB, &oldA);

    // 3. 设置绘制环境
    // 关键点：DrawColor 必须是白色，文字才不会变暗或消失
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    // 设置文字本身的颜色
    TTF_SetTextColor(tempText,
                     (Uint8)(color.r * 255), (Uint8)(color.g * 255),
                     (Uint8)(color.b * 255), (Uint8)(color.a * 255));

    // 4. 绘制
    TTF_DrawRendererText(tempText, position.x, position.y);

    // 5. 还原环境并释放
    SDL_SetRenderDrawColor(_renderer, oldR, oldG, oldB, oldA);
    SDL_SetRenderDrawBlendMode(_renderer, oldMode);
    TTF_DestroyText(tempText);
}

void Game::drawHBar(const glm::vec2 &position, const glm::vec2 &size, float value, const glm::vec4 color)
{
    // 1. 设置颜色 (GLM float 转 SDL Uint8)
    SDL_SetRenderDrawColor(_renderer,
                           static_cast<Uint8>(color.r * 255),
                           static_cast<Uint8>(color.g * 255),
                           static_cast<Uint8>(color.b * 255),
                           static_cast<Uint8>(color.a * 255));
    SDL_FRect boundary_rect = {
        position.x,
        position.y,
        size.x,
        size.y};
    SDL_FRect fill_rect = {
        position.x,
        position.y,
        size.x * value,
        size.y};
    // 2. 开启混合模式
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(_renderer, &fill_rect);
    SDL_RenderRect(_renderer, &boundary_rect); // 画空心描边
    // 绘制完后把颜色改回黑色
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

bool Game::isMouseInRect(const RectData &data)
{
    return (_mouse_position.x >= data.position.x &&
            _mouse_position.x <= data.position.x + data.size.x &&
            _mouse_position.y >= data.position.y &&
            _mouse_position.y <= data.position.y + data.size.y);
}

std::string Game::loadTextFile(const std::string &path)
{
    std::ifstream file(path);
    std::string line;
    std::string text;
    if (!file.is_open())
    {
        SDL_Log("无法打开文件 %s", path.c_str());
        return std::string();
    }
    while (std::getline(file, line))
    {
        text += line + "\n";
    }
    return text;
}
