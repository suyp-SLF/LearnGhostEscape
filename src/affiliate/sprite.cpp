#include "sprite.h"

Texture::Texture(const std::string &file_path)
{
    texture = Game::GetInstance().getAssetStore()->getTexture(file_path);
    SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite *Sprite::addSpriteChild(ObjectScreen *parent, const std::string &texture_path, float scale, Anchor anchor)
{
    auto sprite = new Sprite();
    sprite->init();
    sprite->setTexture(Texture(texture_path));
    sprite->setScale(scale);
    sprite->setOffsetByAnchor(anchor);
    sprite->setParent(parent);
    parent->addChild(sprite);
    return sprite;
}

void Sprite::render()
{
    Object::render();
    if (_texture.texture == nullptr)
    {
        return;
    }
    auto pos = _parent->getRenderPosition() + _offset;
    _game.drawImage(_texture, pos, _size);
}

void Sprite::setTexture(const Texture &texture)
{
    _texture = texture;
    _size = glm::vec2(_texture.src_rect.w, _texture.src_rect.h);
}
