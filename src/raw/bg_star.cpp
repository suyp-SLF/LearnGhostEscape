#include "bg_star.h"
#include "../core/scene.h"

BGStar *BGStar::addBgStarChild(Object *parent, int num, float _far_scale, float _mid_scale, float _near_scale)
{
    auto bg_star = new BGStar();
    bg_star->init();
    bg_star->_num = num;

    bg_star->_far_star.reserve(num); // 预分配内存
    bg_star->_mid_star.reserve(num);
    bg_star->_near_star.reserve(num);
    auto extra = Game::GetInstance().getCurrentScene()->getWorldSize() - Game::GetInstance().getScreenSize();
    for (int i = 0; i < num; i++)
    {
        bg_star->_far_star.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * _far_scale));
        bg_star->_mid_star.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * _mid_scale));
        bg_star->_near_star.push_back(Game::GetInstance().randomVec2(glm::vec2(0), Game::GetInstance().getScreenSize() + extra * _near_scale));
    }
    if (parent) parent->addChild(bg_star);
    return bg_star;
}

void BGStar::update(float dt)
{
    _timer += dt;
    _far_color = glm::vec4(.5f + 0.5f * sinf(_timer * 0.7f), .5f + 0.5f * sinf(_timer * 0.9f), .5f + 0.5f * sinf(_timer * 0.8f), 1);
    _mid_color = glm::vec4(.5f + 0.5f * sinf(_timer * 0.8f), .5f + 0.5f * sinf(_timer * 0.8f), .5f + 0.5f * sinf(_timer * 0.9f), 1);
    _near_color = glm::vec4(.5f + 0.5f * sinf(_timer * 0.9f), .5f + 0.5f * sinf(_timer * 0.7f), .5f + 0.5f * sinf(_timer * 0.7f), 1);
}

void BGStar::render()
{
    auto pos = _game.getCurrentScene()->getCameraPosition();
    _game.drawPoint(_far_star, -pos * _far_scale, _far_color);
    _game.drawPoint(_mid_star, -pos * _mid_scale, _mid_color);
    _game.drawPoint(_near_star, -pos * _near_scale, _near_color);
}
