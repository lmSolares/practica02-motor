#pragma once

#include <SDL3/SDL_render.h>
#include <memory>
#include <vector>
#include "Scene.hpp"

enum class SceneAction {
    None,
    Change,
    Push,
    Pop,
    Clear
};

class SceneManager {
    private:
        std::vector<std::unique_ptr<Scene>> m_scenes;
        SceneAction m_pendingAction {SceneAction::None};
        std::unique_ptr<Scene> m_pendingScene {nullptr};

    public:

        // Métodos de transición
        void ChangeScene(std::unique_ptr<Scene> new_scene)
        {
            m_pendingAction = SceneAction::Change;
            m_pendingScene = std::move(new_scene);
        }

        void PushScene(std::unique_ptr<Scene> new_scene)
        {
            m_pendingAction = SceneAction::Push;
            m_pendingScene = std::move(new_scene);
        }

        void PopScene()
        {
            m_pendingAction = SceneAction::Pop;
        }

        void Clear()
        {
            m_pendingAction = SceneAction::Clear;
        }

        void ProcessPendingChanges()
        {
            switch (m_pendingAction)
            {
                case SceneAction::None:
                    return;
                case SceneAction::Change:
                    if(!m_scenes.empty())
                    {
                        m_scenes.back()->Exit();
                        m_scenes.pop_back();
                    }
                    if(m_pendingScene != nullptr)
                    {
                        m_scenes.push_back(std::move(m_pendingScene));
                        m_scenes.back()->Init();
                    }
                    break;
                case SceneAction::Push:
                    if (m_pendingScene != nullptr)
                    {
                        m_scenes.push_back(std::move(m_pendingScene));
                        m_scenes.back()->Init();
                    }
                    break;
                case SceneAction::Pop:
                    if(!m_scenes.empty())
                    {
                        m_scenes.back()->Exit();
                        m_scenes.pop_back();
                    }
                    break;
                case SceneAction::Clear:
                    while (!m_scenes.empty())
                    {
                        m_scenes.back()->Exit();
                        m_scenes.pop_back();
                    }
                    break;
            }
            m_pendingAction = SceneAction::None;
            m_pendingScene.reset();
        }

        void HandleEvent(const SDL_Event &event)
        {
            if(!m_scenes.empty()) m_scenes.back()->HandleEvent(event);
        }

        void Update(float dt)
        {
            if(!m_scenes.empty()) m_scenes.back()->Update(dt);
        }

        void Render(SDL_Renderer *renderer)
        {
            for(auto &scene : m_scenes) scene->Render(renderer);
        }

        bool HasScenes()
        {
            return !m_scenes.empty();
        }

};
