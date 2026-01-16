#ifndef ASSET_STORE_H
#define ASSET_STORE_H

#include <string>
#include <unordered_map> //无序map，性能比mao稍好
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class AssetStore
{
private:
    SDL_Renderer *_renderer = nullptr; // 渲染器指针
    MIX_Mixer *_mixer = nullptr; // 音效指针
    std::unordered_map<std::string, SDL_Texture *> _textures;
    std::unordered_map<std::string, MIX_Audio *> _sounds;
    std::unordered_map<std::string, MIX_Audio *> _musics;
    std::unordered_map<std::string, TTF_Font *> _fonts;

    // 载入函数,返回地址
    SDL_Texture *loadTexture(const std::string &path);
    MIX_Audio *loadSound(const std::string &path);
    MIX_Audio *loadMusic(const std::string &path);
    TTF_Font *loadFont(const std::string &path, int size);

public:
    AssetStore(SDL_Renderer *renderer, MIX_Mixer *mixer) : _renderer(renderer), _mixer(mixer) {};
    ~AssetStore() = default;

    void clean(); // 清理函数
    // 获取函数
    SDL_Texture *getTexture(const std::string &name);
    MIX_Audio *getSound(const std::string &name);
    MIX_Audio *getMusic(const std::string &name);
    TTF_Font *getFont(const std::string &name, int font_size);
};

#endif // ASSET_STORE_H