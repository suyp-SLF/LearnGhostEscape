#include "sprite.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::getInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &texture_path, float scale, Anchor anchor, glm::vec3 color)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setTexture(Texture(texture_path));
    sprite->setScale(scale);
    sprite->setOffsetByAnchor(anchor);
    sprite->setColor(color);
    if (parent)
    {
        sprite->setParent(parent);
        parent->safeAddChild(sprite);
    }
    return sprite;
}

void Sprite::setScale(float scale)
{
    _size *= scale;
    setOffsetByAnchor(_anchor);
}

void Sprite::render()
{
    Object::render();
    if (_texture.texture == nullptr)
    {
        return;
    }
    auto pos = _parent->getRenderPosition() + _offset;
    Game::getInstance().drawImage(_texture, pos, _size, _percentage, 1.f, _color);
#ifdef DEBUG_MDOE
    // 碰撞箱
    Game::getInstance().drawBoundary(_parent->getRenderPosition() + _offset, _parent->getRenderPosition() + _offset + _size, 1, {255, 255, 255, 255});
#endif
}

void Sprite::setTexture(const Texture &texture)
{
    _texture = texture;
    _size = glm::vec2(_texture.src_rect.w, _texture.src_rect.h);
}
