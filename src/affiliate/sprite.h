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
    glm::vec2 _percentage =glm::vec2(1.f);
public:
    static Sprite *addSpriteChild(ObjectScreen *parent, const std::string& texture_path, float scale = 1.f, Anchor anchor = Anchor::CENTER);
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
    // 百分比
    glm::vec2 getPercentage() const { return _percentage; }
    void setPercentage(glm::vec2 percentage) { _percentage = percentage; }
};
#endif // SPRITE_H