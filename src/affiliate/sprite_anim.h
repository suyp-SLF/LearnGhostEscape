#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H

#include "sprite.h"

class SpriteAnim : public Sprite
{
    int _current_frame = 0;
    int _total_frames = 0;
    int _fps = 10;
    float _frame_timer = 0.0f;
    bool _is_loop = true; // default is loop

public:
    static SpriteAnim *addSpriteAnimChild(ObjectScreen *parent,const std::string &texture_path, float scale = 1.f);
    virtual void update(float dt) override;
    virtual void setTexture(const Texture &texture) override;

    // GETTER AND SETTER
    int getTotalFrames() { return _total_frames; }
    void setTotalFrames(int total_frames) { _total_frames = total_frames; }
    int getFps() { return _fps; }
    void setFps(int fps) { _fps = fps; }
    float getFrameTimer() { return _frame_timer; }
    void setFrameTimer(float frame_timer) { _frame_timer = frame_timer; }
    int getCurrentFrame() { return _current_frame; }
    int setCurrentFrame(int current_frame) { _current_frame = current_frame; }
};
#endif // SPRITE_ANIM_H