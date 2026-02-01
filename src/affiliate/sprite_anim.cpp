#include "sprite_anim.h"

SpriteAnim *SpriteAnim::addSpriteAnimChild(ObjectScreen *parent, const std::string &texture_path, Anchor anchor, float scale)
{
    auto sprite_anim = new SpriteAnim();
    sprite_anim->init();
    sprite_anim->setTexture(Texture(texture_path));
    sprite_anim->setParent(parent);
    sprite_anim->setScale(scale);
    // sprite_anim->setActive(false);
    sprite_anim->setOffsetByAnchor(anchor);
    if (parent)
        parent->addChild(sprite_anim);
    return sprite_anim;
}

void SpriteAnim::update(float dt)
{
    Sprite::update(dt);
    _frame_timer += dt;
    if (!_is_loop && (_current_frame == _total_frames))
    {
        _is_finish = true;
        //_is_delete = true;
        return;
    }
    if (_frame_timer >= 1.0f / _fps)
    {
        _current_frame++;
        if (_current_frame >= _total_frames)
        {
            if (_is_loop)
            {
                _current_frame = 0;
            }
        }
        _frame_timer = 0.0f;
    }
    _texture.src_rect.x = _texture.src_rect.w * _current_frame;
}

void SpriteAnim::render()
{
    Sprite::render();
#ifdef DEBUG_MDOE
//碰撞箱
    Game::getInstance().drawText(
        // 获得类名
        std::to_string(_current_frame),
        _parent->getRenderPosition() + _offset,
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
#endif
}

void SpriteAnim::setTexture(const Texture &texture)
{
    _texture = texture;
    _total_frames = texture.src_rect.w / texture.src_rect.h;
    _texture.src_rect.w = texture.src_rect.h;
    _size = {texture.src_rect.h, texture.src_rect.h};
}
