#ifndef AFFILIATE_BAR_H
#define AFFILIATE_BAR_H

#include "../core/object_affiliate.h"

#include <glm/glm.hpp>

class AffiliateBar : public ObjectAffiliate
{
protected:
    float _percentage = 1.f;
    glm::vec4 _color_high = glm::vec4(0.f, 1.f, 0.f, 1.f);
    glm::vec4 _color_mid = glm::vec4(1.f, 1.f, 0.f, 1.f);
    glm::vec4 _color_low = glm::vec4(1.f, 0.f, 0.f, 1.f);

public:
    static AffiliateBar* addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor = Anchor::BOTTOM_CENTER);
    virtual void render() override;

    // GETTER AND SETTER
    float getPercentage() { return _percentage;}
    void setPercentage(float percentage){ _percentage = percentage;}
    glm::vec4 getColorHigh() { return _color_high;}
    void setColorHigh(const glm::vec4& color_high){ _color_high = color_high;}
    glm::vec4 getColorMid() { return _color_mid;}
    void setColorMid(const glm::vec4& color_mid){ _color_mid = color_mid;}
    glm::vec4 getColorLow() { return _color_low;}
    void setColorLow(const glm::vec4& color_low){ _color_low = color_low;}
};
#endif // AFFILIATE_BAR_H