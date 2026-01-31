#ifndef BG_STAR_H
#define BG_STAR_H
#include "../core/object.h"
#include <vector>
#include <glm/glm.hpp>
class BGStar : public Object
{
protected:
    std::vector<glm::vec2> _far_star;
    std::vector<glm::vec2> _mid_star;
    std::vector<glm::vec2> _near_star;

    float _far_scale = .2f;
    float _mid_scale = .5f;
    float _near_scale = .8f;

    glm::vec4 _far_color = glm::vec4(0, 0, 0, 1);
    glm::vec4 _mid_color = glm::vec4(0, 0, 0, 1);
    glm::vec4 _near_color = glm::vec4(0, 0, 0, 1);

    float _timer = 0;
    int _num = 1000;  //每一层的星星数量
public:
    virtual void update(float dt) override;
    static BGStar* addBgStarChild(Object *parent, glm::vec2 size, Anchor anchor = Anchor::CENTER);
};
#endif // BG_STAR_H