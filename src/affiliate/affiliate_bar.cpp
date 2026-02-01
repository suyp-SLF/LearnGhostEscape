#include "affiliate_bar.h"

AffiliateBar *AffiliateBar::addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor)
{
    auto affiliate_bar = new AffiliateBar();
    affiliate_bar->init();
    affiliate_bar->setAnchor(anchor);
    affiliate_bar->setSize(size);
    if (parent)
    {
        affiliate_bar->setParent(parent);
        parent->addChild(affiliate_bar);
        affiliate_bar->setOffset(affiliate_bar->getOffset() + glm::vec2(0, 100));
    }
    return affiliate_bar;
}

void AffiliateBar::render()
{
    auto position = _parent->getRenderPosition() + _offset;
    if (_percentage > .7f)
    {
        Game::getInstance().drawHBar(position, _size, _percentage, _color_high);
    }
    else if (_percentage > .3f)
    {
        Game::getInstance().drawHBar(position, _size, _percentage, _color_mid);
    }
    else
    {
        Game::getInstance().drawHBar(position, _size, _percentage, _color_low);
    }

#ifdef DEBUG_MDOE
    // 血量
    Game::getInstance().drawText(std::to_string(_percentage), position + glm::vec2(0, 10), glm::vec4(1));
#endif
}
