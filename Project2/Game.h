#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <glm.hpp>
#include <SDL_mixer.h>

#include "InputManager.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PowerUp.h"

class GameObject;
class Enemy;
class Text;

enum class GameState
{
    PLAY,
    INGAMEMENU,
    MAINMENU,
    SETTINGSMENU,
    GAMEOVER,
    EXIT
};

class Game
{
public:
    Game();
    ~Game();

    void run();

    static SDL_Renderer *renderer;
    static SDL_Event event;

private:

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();
    void reset();

    Uint32 m_fps;
    double m_frameCap;
    double m_lastTime;
    double m_fpsTimeCounter;
    double m_updateTimer;
    float m_frameTime;

    double getTime();

    GameState m_currentGameState;
    GameState m_lastGameState;
    SDL_Window *m_window;

    std::vector<GameObject*> m_entities;
    std::vector<Bullet> m_bullets;
    std::vector<Enemy> m_enemies;
    std::vector<PowerUp> m_powerUps;
    std::vector<Mix_Music*> m_music;
    std::vector<Mix_Chunk*> m_soundEffects;

    int m_windowWidth;
    int m_windowHeight;

    InputManager m_inputManager;

};

#endif // GAME_H_INCLUDED
