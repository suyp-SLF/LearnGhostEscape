#include <glm/glm.hpp>
#include <SDL3/SDL.h>

struct RectData {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 size     = {100.0f, 100.0f};
    glm::vec4 color    = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA (0.0 - 1.0)
    float rotation     = 0.0f;                    // 方便后期做旋转
    bool filled        = true;                    // 是实心还是空心框
};