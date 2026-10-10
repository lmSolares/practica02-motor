#include "GameOverScene.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"

void GameOverScene::HandleEvent(const SDL_Event &event)
{
    if(event.type == SDL_EVENT_KEY_DOWN)
    {
        if(event.key.scancode == SDL_SCANCODE_R)
        {
            m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
        }
        if(event.key.scancode == SDL_SCANCODE_M)
        {
            m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
        }
    }
}
