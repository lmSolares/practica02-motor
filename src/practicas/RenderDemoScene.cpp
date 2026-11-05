#include "practicas/RenderDemoScene.hpp"
#include "engine/GameObject.hpp"

void RenderDemoScene::LoadEntities() {
  m_camera.SetViewportSize(960.0f, 540.0f);
  m_camera.SetBounds(Vector2{0.0f, 0.0f}, Vector2{2400.0f, 540.0f});

  SDL_Texture *texSky = m_resourceManager.GetTexture("assets/bg_sky.png");
  GameObject *sky = CreateGameObject("Sky");
  sky->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f},
                                        Vector2{3.0f, 1.0f});
  auto *skySprite = sky->AddComponent<SpriteComponent>(texSky);
  skySprite->SetLayer(-30);
  skySprite->SetParallaxFactor(Vector2{0.05f, 0.0f});

  SDL_Texture *texMountains =
      m_resourceManager.GetTexture("assets/bg_mountains.png");
  GameObject *mountains = CreateGameObject("Mountains");
  mountains->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f},
                                              Vector2{3.0f, 1.0f});
  auto *mountainsSprite =
      mountains->AddComponent<SpriteComponent>(texMountains);
  mountainsSprite->SetLayer(-20);
  mountainsSprite->SetParallaxFactor(Vector2{0.25f, 0.0f});

  SDL_Texture *texTrees = m_resourceManager.GetTexture("assets/bg_trees.png");
  GameObject *trees = CreateGameObject("Trees");
  trees->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f},
                                          Vector2{3.0f, 1.0f});
  auto *treesSprite = trees->AddComponent<SpriteComponent>(texTrees);
  treesSprite->SetLayer(-10);
  treesSprite->SetParallaxFactor(Vector2{0.50f, 0.0f});

  SDL_Texture *texGround = m_resourceManager.GetTexture("assets/ground.png");
  GameObject *ground = CreateGameObject("Ground");
  ground->AddComponent<TransformComponent>(Vector2{0.0f, 476.0f},
                                           Vector2{3.0f, 1.0f});
  auto *groundSprite = ground->AddComponent<SpriteComponent>(texGround);
  groundSprite->SetLayer(0);
  groundSprite->SetParallaxFactor(Vector2{1.0f, 1.0f});

  SDL_Texture *texEnemy = m_resourceManager.GetTexture("assets/enemy.png");
  GameObject *enemy = CreateGameObject("Enemy");
  enemy->AddComponent<TransformComponent>(Vector2{1400.0f, 412.0f});
  auto *enemySprite = enemy->AddComponent<SpriteComponent>(texEnemy);
  enemySprite->SetLayer(5);
  enemySprite->SetParallaxFactor(Vector2{1.0f, 1.0f});

  SDL_Texture *texPlayer =
      m_resourceManager.GetTexture("assets/player_sheet.png");
  GameObject *player = CreateGameObject("Player");
  m_playerTransform =
      player->AddComponent<TransformComponent>(Vector2{100.0f, 412.0f});
  m_playerSprite = player->AddComponent<SpriteComponent>(texPlayer);
  m_playerSprite->SetLayer(10);
  m_playerSprite->SetParallaxFactor(Vector2{1.0f, 1.0f});

  m_playerAnim = player->AddComponent<AnimationComponent>(32, 32);
  m_playerAnim->AddClip("idle", 0, 4, 0.15f, true, 0);
  m_playerAnim->AddClip("walk", 1, 4, 0.1f, true, 0);

  GameObject *hud = CreateGameObject("HUD");
  hud->AddComponent<TransformComponent>(Vector2{20.0f, 20.0f});
  auto *hudSprite = hud->AddComponent<SpriteComponent>(texPlayer);
  hudSprite->SetLayer(100);
  hudSprite->SetAffectedByCamera(false);
  hudSprite->m_useSrcRect = true;
  hudSprite->m_srcRect = {0.0f, 0.0f, 32.0f, 32.0f};
}

void RenderDemoScene::Update(float dt) {
  if (!m_initialized)
    return;

  const bool *keys = SDL_GetKeyboardState(nullptr);
  bool moving = false;

  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
    m_playerTransform->position.x -= 200.0f * dt;
    m_playerSprite->m_flip = SDL_FLIP_HORIZONTAL;
    m_playerAnim->Play("walk");
    moving = true;
  }
  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
    m_playerTransform->position.x += 200.0f * dt;
    m_playerSprite->m_flip = SDL_FLIP_NONE;
    m_playerAnim->Play("walk");
    moving = true;
  }

  if (!moving) {
    m_playerAnim->Play("idle");
  }

  m_camera.Follow(m_playerTransform->position, 4.5f, dt);
  Camera2D::SetMain(&m_camera);

  Scene::Update(dt);
}

void RenderDemoScene::Render(SDL_Renderer *renderer) {
  if (!m_initialized) {
    m_resourceManager.SetRenderer(renderer);
    LoadEntities();
    m_initialized = true;
  }

  Camera2D::SetMain(&m_camera);
  Scene::Render(renderer);
}

void RenderDemoScene::Exit() {
  m_resourceManager.Clear();
  m_entities.clear();
  Camera2D::SetMain(nullptr);
}
