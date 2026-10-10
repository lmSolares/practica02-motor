#pragma once

#include "CollisionManager.hpp"
#include "GameObject.hpp"
#include "GameOverScene.hpp"
#include "PauseScene.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "RectRenderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "BallComponent.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>

class GameScene : public Scene {

    private:
        CollisionManager m_collisionManager{nullptr};
        float m_physicsAccumulator{0.0f};
        bool m_debugDraw{false};

    public :

        GameScene (SceneManager *m_manager) : Scene(m_manager, "Game Scene") {}

        void Init() override
        {
            m_entities.clear();
            m_collisionManager.SetEntities(&m_entities);

            // Jugador
            GameObject* player = CreateGameObject("Player");
            player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f});
            player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
                                                      SDL_Color{60, 180, 100, 255});
            player->AddComponent<PlayerControllerComponent>(300.0f, false);
            player->AddComponent<ColliderComponent>();

            // Obstáculo
            GameObject* obstacle = CreateGameObject("Obstacle");
            obstacle->AddComponent<TransformComponent>(Vector2{180.0f, 140.0f});
            obstacle->AddComponent<RectRenderComponent>(Vector2{80.0f, 80.0f},
                                                        SDL_Color{220, 70, 70, 255});
            auto *obsCol = obstacle->AddComponent<ColliderComponent>();
            obsCol->size = Vector2{80.0f, 80.0f};

            // Pelota
            GameObject* ball = CreateGameObject("Ball");
            ball->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f});
            ball->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
                                                    SDL_Color{240, 210, 60, 255});
            auto *ballCol = ball->AddComponent<ColliderComponent>();
            ballCol->size = Vector2{24.0f, 24.0f};
            ball->AddComponent<BallComponent>();

        }

        void Update(float dt) override
        {
            constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
            m_physicsAccumulator += dt;

            while (m_physicsAccumulator >= FIXED_TIMESTEP)
            {
                for (auto &entity : m_entities)
                {
                    entity->Update(FIXED_TIMESTEP);
                }
                m_collisionManager.CheckCollisions();
                m_physicsAccumulator -= FIXED_TIMESTEP;
            }
        }

        void HandleEvent(const SDL_Event &event) override
        {
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if(event.key.scancode == SDL_SCANCODE_F1) m_debugDraw = !m_debugDraw;
                if(event.key.scancode == SDL_SCANCODE_P || event.key.scancode == SDL_SCANCODE_ESCAPE)
                {
                    m_manager->PushScene(std::make_unique<PauseScene>(m_manager));
                }
                if(event.key.scancode == SDL_SCANCODE_G)
                {
                    m_manager->ChangeScene(std::make_unique<GameOverScene>(m_manager));
                }
            }
        }

        void Render(SDL_Renderer *renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
            SDL_RenderClear(renderer);

            for (auto &entity : m_entities) entity->Render(renderer);

            if (m_debugDraw)
            {
                for (auto &entity : m_entities)
                {
                    if (auto *col = entity->GetComponent<ColliderComponent>()) col->RenderDebug(renderer);
                }
            }
        }

};
