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
    glm::vec3 _color = glm::vec3(1.f);
    Texture _texture;
    glm::vec2 _percentage =glm::vec2(1.f);
public:
    static Sprite *addSpriteChild(ObjectScreen *parent, const std::string& texture_path, float scale = 1.f, Anchor anchor = Anchor::CENTER, glm::vec3 color = glm::vec3(1.f));
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
    // 颜色
    glm::vec3 getColor() const { return _color; }
    void setColor(glm::vec3 color) { _color = color; }
};
#endif // SPRITE_H