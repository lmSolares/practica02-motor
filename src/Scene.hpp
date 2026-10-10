#pragma once
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <string>
#include <vector>

class Scene {
    protected:
        SceneManager *m_manager;
        std::vector<std::unique_ptr<GameObject>> m_entities;
        std::string m_name;

    public:

        // Eliminar copia, asignación y se agrega semántica de movimiento
        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

        Scene(Scene&&) = default;
        Scene& operator=(Scene&&) = default;

        // Destructor
        virtual ~Scene() = default;

        // Constructor
        Scene(SceneManager *m_manager, std::string m_name)
        {
            this->m_manager = m_manager;
            this->m_name = m_name;
        }

        GameObject* CreateGameObject(std::string tag) {
            auto entity = std::make_unique<GameObject>(tag);
            GameObject* ptr = entity.get();
            m_entities.push_back(std::move(entity));
            return ptr;
        }

        virtual std::vector<std::unique_ptr<GameObject>>& GetEntities() {
            return m_entities;
        }

        virtual void Init() {}

        virtual void Exit() {}

        virtual void Update(float dt) {
            for(auto &entity : m_entities) entity->Update(dt);
        }

        virtual void HandleEvent(const SDL_Event &event) {}

        virtual void Render(SDL_Renderer *renderer) {
            for(auto &entity : m_entities) entity->Render(renderer);
        }

};
