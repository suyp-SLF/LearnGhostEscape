#include "asset_store.h"

void AssetStore::clean()
{
    for (auto &pair : _textures)
    {
        SDL_DestroyTexture(pair.second);
    }
    _textures.clear();

    for (auto &pair : _sounds)
    {
        MIX_DestroyAudio(pair.second);
    }
    _sounds.clear();

    for (auto &pair : _musics)
    {
        MIX_DestroyAudio(pair.second);
    }
    _musics.clear();

    for (auto &pair : _fonts)
    {
        TTF_CloseFont(pair.second);
    }
    _fonts.clear();
}

SDL_Texture *AssetStore::loadTexture(const std::string &_file_path)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, _file_path.c_str());
    if (texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "加载图片失败: %s", SDL_GetError());
        return nullptr;
    }
    //_textures[_file_path] = texture;
    _textures.emplace(_file_path, texture);
    return texture;
}

MIX_Audio *AssetStore::loadSound(const std::string &_file_path)
{
    // is_stream = false: 全量加载到内存，适合短促音效
    MIX_Audio* audio = MIX_LoadAudio(_mixer, _file_path.c_str(), false);
    if (!audio) {
        SDL_Log("音效加载失败: %s -> %s", _file_path.c_str(), SDL_GetError());
    }
    _sounds.emplace(_file_path, audio);
    return audio;
}

MIX_Audio *AssetStore::loadMusic(const std::string &_file_path)
{
    // is_stream = true: 流式播放，适合长背景音乐
    MIX_Audio* audio = MIX_LoadAudio(_mixer, _file_path.c_str(), true);
    if (!audio) {
        SDL_Log("音乐加载失败: %s -> %s", _file_path.c_str(), SDL_GetError());
    }
    _musics.emplace(_file_path, audio);
    return audio;
}

TTF_Font *AssetStore::loadFont(const std::string &_file_path, int font_size)
{
    TTF_Font *font = TTF_OpenFont(_file_path.c_str(), font_size);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "加载字体失败: %s", SDL_GetError());
        return nullptr;
    }
    _fonts.emplace(_file_path + std::to_string(font_size), font);
    return font;
}



SDL_Texture *AssetStore::getTexture(const std::string &file_path)
{
    // _textures找到name，返回it
    auto it = _textures.find(file_path);
    if (it == _textures.end())
    {
        return loadTexture(file_path);
    }
    else
    {
        return it->second;
    }
}

MIX_Audio *AssetStore::getSound(const std::string &file_path)
{
    // _sounds找到name，返回it
    auto it = _sounds.find(file_path);
    if (it == _sounds.end())
    {
        return loadSound(file_path);
    }
    else
    {
        return it->second;
    }
}

MIX_Audio *AssetStore::getMusic(const std::string &file_path)
{
    // _musics找到name，返回it
    auto it = _musics.find(file_path);
    if (it == _musics.end())
    {
        return loadMusic(file_path);
    }
    else
    {
        return it->second;
    }
}

TTF_Font *AssetStore::getFont(const std::string &file_path, int font_size)
{
    // _fonts找到name，返回it
    auto it = _fonts.find(file_path + std::to_string(font_size));
    if (it == _fonts.end())
    {
        return loadFont(file_path, font_size);
    }
    else
    {
        return it->second;
    }
}
