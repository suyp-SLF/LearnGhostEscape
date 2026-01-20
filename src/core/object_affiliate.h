#ifndef OBJECT_AFFILIATE_H
#define OBJECT_AFFILIATE_H

#include "object_screen.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen *_parent = nullptr;    // 父节点
    glm::vec2 _offset = glm::vec2(0, 0);    //相对父节点的位置
    glm::vec2 _size = glm::vec2(0, 0);    //大小
    Anchor _anchor = Anchor::CENTER;    //锚点
public:
    void setOffsetByAnchor(const Anchor anchor);
    // GETTER AND SETTER
    void setParent(ObjectScreen *parent) { _parent = parent; }
    ObjectScreen *getParent() { return _parent; }
    void setOffset(glm::vec2 offset) { _offset = offset; }
    glm::vec2 getOffset() { return _offset; }
    void setSize(glm::vec2 size);
    glm::vec2 getSize() { return _size; }
    void setAnchor(Anchor anchor) { _anchor = anchor; }
    Anchor getAnchor() { return _anchor; }
};
#endif // OBJECT_AFFILIATE_H