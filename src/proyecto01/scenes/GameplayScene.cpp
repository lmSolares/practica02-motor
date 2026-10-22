#include "proyecto01/scenes/GameplayScene.hpp"
#include "motor/ColliderComponent.hpp"
#include "motor/GameObject.hpp"
#include "motor/RectRenderComponent.hpp"
#include "motor/SceneManager.hpp"
#include "motor/TransformComponent.hpp"
#include "motor/Vector2.hpp"
#include "proyecto01/components/BoomerangComponent.hpp"
#include "proyecto01/components/KnightControllerComponent.hpp"
#include "proyecto01/components/MantisControllerComponent.hpp"
#include "proyecto01/components/PixelArtComponent.hpp"
#include "proyecto01/components/StingStrikeComponent.hpp"
#include "proyecto01/scenes/GameOverScene.hpp"
#include "proyecto01/scenes/PauseScene.hpp"
#include <SDL3/SDL_pixels.h>

void GameplayScene::Init() {
  m_entities.clear();
  m_collisionManager.SetEntities(&m_entities);

  /* Entorno */

  // Paredes
  GameObject *wallLeft = CreateGameObject("Wall");
  wallLeft->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
  wallLeft->AddComponent<RectRenderComponent>(Vector2{40.0f, 540.0f},
                                              SDL_Color{26, 31, 34, 255});
  auto *obsCol = wallLeft->AddComponent<ColliderComponent>();
  obsCol->size = Vector2{40.0f, 540.0f};

  GameObject *wallRight = CreateGameObject("Wall");
  wallRight->AddComponent<TransformComponent>(Vector2{920.0f, 0.0f});
  wallRight->AddComponent<RectRenderComponent>(Vector2{40.0f, 540.0f},
                                               SDL_Color{26, 31, 34, 255});
  auto *obsCol2 = wallRight->AddComponent<ColliderComponent>();
  obsCol2->size = Vector2{40.0f, 540.0f};

  // Suelo
  GameObject *floor = CreateGameObject("Floor");
  floor->AddComponent<TransformComponent>(Vector2{180.0f, 510.0f});
  floor->AddComponent<RectRenderComponent>(Vector2{600.0f, 30.0f},
                                           SDL_Color{26, 31, 34, 255});
  auto *obsCol3 = floor->AddComponent<ColliderComponent>();
  obsCol3->size = Vector2{600.0f, 30.0f};

  // Pinchos
  GameObject *spikeLeft = CreateGameObject("Spike");
  spikeLeft->AddComponent<TransformComponent>(Vector2{40.0f, 520.0f});
  auto *trigCol = spikeLeft->AddComponent<ColliderComponent>();
  trigCol->size = Vector2{140.0f, 20.0f};
  trigCol->is_trigger = true;

  GameObject *spikeRight = CreateGameObject("Spike");
  spikeRight->AddComponent<TransformComponent>(Vector2{780.0f, 520.0f});
  auto *trigCol1 = spikeRight->AddComponent<ColliderComponent>();
  trigCol1->size = Vector2{140.0f, 20.0f};
  trigCol1->is_trigger = true;

  /* Entidades */

  // Caballero
  GameObject *knight = CreateGameObject("Knight");
  knight->AddComponent<TransformComponent>(Vector2{460.0f, 400.0f});
  auto *knightCol = knight->AddComponent<ColliderComponent>();
  knightCol->size = Vector2{32.0f, 48.0f};
  knight->AddComponent<KnightControllerComponent>(300.0f);

  // Aguijon
  GameObject *sting = CreateGameObject("Sting");
  sting->AddComponent<TransformComponent>(Vector2{-200.0f, 0.0f});
  sting->AddComponent<RectRenderComponent>(Vector2{5.0f, 40.0f},
                                           SDL_Color{176, 172, 184, 255});
  auto *stingCol = sting->AddComponent<ColliderComponent>();
  stingCol->size = Vector2{5.0f, 40.0f};
  stingCol->is_trigger = true;
  sting->AddComponent<StingStrikeComponent>();
  sting->SetActive(false);

  knight->GetComponent<KnightControllerComponent>()->SetSting(sting);
  sting->GetComponent<StingStrikeComponent>()->SetKnight(knight);

  // Mantis
  GameObject *mantis = CreateGameObject("Mantis");
  mantis->AddComponent<TransformComponent>(Vector2{-200.0f, 0.0f});
  auto *mantisCol = mantis->AddComponent<ColliderComponent>();
  mantisCol->is_trigger = true;
  mantisCol->size = Vector2{32.0f, 48.0f};
  mantis->AddComponent<MantisControllerComponent>();

  mantis->GetComponent<MantisControllerComponent>()->SetKnight(knight);

  // Boomerang
  GameObject *boomerang = CreateGameObject("Boomerang");
  boomerang->AddComponent<TransformComponent>(Vector2{200.0f, 0.0f});
  auto *boomCol = boomerang->AddComponent<ColliderComponent>();
  boomCol->is_trigger = true;
  boomCol->size = Vector2{40.0f, 40.0f};
  boomerang->AddComponent<BoomerangComponent>();
  boomerang->SetActive(false);

  mantis->GetComponent<MantisControllerComponent>()->SetBoomerang(boomerang);
  mantis->GetComponent<MantisControllerComponent>()->SetSceneManager(m_manager);
  knight->GetComponent<KnightControllerComponent>()->SetSceneManager(m_manager);

  /* PIXELS ARTS */
  std::vector<std::string> mask_art = {"  KKKK  ", " KWWWWK ", "KW.KK.WK",
                                       "KWWWWWWK", "KWWWWWWK", " KWWWWK ",
                                       "  KWWK  ", "   KK   "};
  std::vector<std::string> knight_art = {
      "  KWWK  ", " KWWWWK ", " KWWWWK ", "KWWWWWWK", "KW.KK.WK", "KWWWWWWK",
      " KWWWWK ", " KKKKKK ", " GGGGGG ", "  GGGG  ", "  K  K  ", "  K  K  "};
  std::vector<std::string> mantis_art = {
      " K    K ", " KW  WK ", " KWWWWK ", "KWWWWWWK", "KW.KK.WK", "KWWWWWWK",
      " KWWWWK ", " KKKKKK ", " KGGGGK ", " KGGGGK ", " K    K ", " K    K "};
  std::vector<std::string> boomerang_art = {
      "   GGGG   ", " GGW  WGG ", " GWG  GWG ", "GGW    WGG", "GW      WG",
      "GW      WG", "GGW    WGG", " GWG  GWG ", " GGW  WGG ", "   GGGG   "};
  std::vector<std::string> spikes_art = {"   G      G      G      G      G   ",
                                         "  GWG    GWG    GWG    GWG    GWG  ",
                                         "  GWG    GWG    GWG    GWG    GWG  ",
                                         " GWWWG  GWWWG  GWWWG  GWWWG  GWWWG ",
                                         " GWWWG  GWWWG  GWWWG  GWWWG  GWWWG "};

  auto *knight_comp = knight->GetComponent<KnightControllerComponent>();

  for (int i = 0; i < 5; ++i) {
    GameObject *mask = CreateGameObject("MaskHUD");
    mask->AddComponent<TransformComponent>(Vector2{45.0f + (i * 40.0f), 20.0f});
    mask->AddComponent<PixelArtComponent>(mask_art, 4.0f);

    knight_comp->masks_hud.push_back(mask);
  }
  knight->AddComponent<PixelArtComponent>(knight_art, 4.0f);
  mantis->AddComponent<PixelArtComponent>(mantis_art, 4.0f);
  spikeLeft->AddComponent<PixelArtComponent>(spikes_art, 4.0f);
  spikeRight->AddComponent<PixelArtComponent>(spikes_art, 4.0f);
  boomerang->AddComponent<PixelArtComponent>(boomerang_art, 4.0f);
}

void GameplayScene::FixedUpdate(float fixed_dt) {
  for (auto &entity : m_entities) {
    entity->FixedUpdate(fixed_dt);
  }
  m_collisionManager.CheckCollisions();
}

void GameplayScene::HandleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    if (event.key.scancode == SDL_SCANCODE_F1)
      m_debugDraw = !m_debugDraw;
    if (event.key.scancode == SDL_SCANCODE_P ||
        event.key.scancode == SDL_SCANCODE_ESCAPE) {
      m_manager->PushScene(std::make_unique<PauseScene>(m_manager));
    }
    if (event.key.scancode == SDL_SCANCODE_G) {
      m_manager->ChangeScene(std::make_unique<GameOverScene>(m_manager));
    }
  }
}

void GameplayScene::Render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 20, 50, 76, 255);
  SDL_RenderClear(renderer);

  for (auto &entity : m_entities)
    entity->Render(renderer);

  if (m_debugDraw) {
    for (auto &entity : m_entities) {
      if (auto *col = entity->GetComponent<ColliderComponent>())
        col->RenderDebug(renderer);
    }
  }
}
