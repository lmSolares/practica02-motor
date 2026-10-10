
#include "TitleScene.hpp"
#include "GameScene.hpp"

void TitleScene::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if(event.key.scancode == SDL_SCANCODE_SPACE || event.key.key == SDL_SCANCODE_RETURN)
        {
            m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
        }
    }
}
