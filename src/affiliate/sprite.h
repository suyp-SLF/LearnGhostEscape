#ifndef SPRITE_H
#define SPRITE_H

#include "../core/object_affiliate.h"

struct Texture
{
    SDL_Texture *texture = nullptr;
    SDL_FRect src_rect = {0, 0, 0, 0};
    float angle = 0;
    SDL_FlipMode flip = SDL_FLIP_NONE;
    Texture() = default;
    Texture(const std::string& file_path);
};
class Sprite : public ObjectAffiliate
{
protected:
    Texture _texture;
public:
    static Sprite *addSpriteChild(ObjectScreen *parent, const std::string& texture_path, float scale = 1.f);
    Sprite() = default;
    void setScale(float scale){ _size *= scale; }
    virtual void render() override;
    // GETTER AND SETTER
    // 图片
    Texture getTexture() const { return _texture; }
    virtual void setTexture (const Texture &texture);
    // 反转
    bool getFlip() const { return _texture.flip; }
    void setFlip (SDL_FlipMode flip) { _texture.flip = flip; }
    // 角度
    float getAngle() const { return _texture.angle; }
    void setAngle(float angle) { _texture.angle = angle; }
};
#endif // SPRITE_H