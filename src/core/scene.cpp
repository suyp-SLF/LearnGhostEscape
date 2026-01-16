#include "scene.h"

void Scene::setCameraPosition(const glm::vec2 camera_position)
{
    _camera_position = camera_position;
    //限制摄像头的位置
    _camera_position = glm::clamp(
        _camera_position, 
        glm::vec2(-30), 
        _world_size - _game.getScreenSize() + glm::vec2(30));
}