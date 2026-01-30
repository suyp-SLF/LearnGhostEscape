#ifndef ENEMY_H
#define ENEMY_H

#include "core/actor.h"
#include "affiliate/sprite_anim.h"
#include "player.h"

#include <glm/glm.hpp>

class Enemy : public Actor
{
private:
    enum class State { 
        NORMAL,
        HURT,
        DIE 
    };
    Player *_target = nullptr;

    State _current_state = State::NORMAL;
    SpriteAnim *_anim_normal = nullptr;
    SpriteAnim *_anim_hurt = nullptr;
    SpriteAnim *_anim_die = nullptr;
    SpriteAnim *_current_anim = nullptr;

    int _score = 10; // score when enemy is killed
public:
    virtual void init() override;
    virtual bool handleEvents(SDL_Event &event) override;
    virtual void update(float dt) override;
    virtual void render() override;
    virtual void clean() override;

    static Enemy* addEnemyChild(Object *parent, glm::vec2 postion, Player *_target);

    void attack();
    void aim_target(Player *target);
    void checkState();
    void changeState(State new_state);
    void remove();

    // GETTER AND SETTER
    Player *get_target() const { return _target; }
    void set_target(Player *target) { _target = target; }
};
#endif // ENEMY_H