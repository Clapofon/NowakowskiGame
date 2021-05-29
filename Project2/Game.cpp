#include "Game.h"
#include "TextureManager.h"
#include "GameObject.hpp"
#include "Collision.h"
#include "Text.h"
#include "Menu.h"
#include "input.h"
#include "ResourceManager.h"
#include "TextureManager.h"

#include <ctime>
#include <random>
#include <sstream>

GameObject* player;
Menu* inGameMenu;
Menu* mainMenu;
Menu* settingsMenu;
Menu* gameoverMenu;

Text* text;
Text* fps;
Text* health;
Text* keyboardText;

std::string keyboardTextString = "";

unsigned short int counter = 0;
unsigned short int counterPowerUp = 0;
unsigned short int counterPowerUpSpecial = 0;
unsigned short int num = 0;
unsigned short int numPowerUp = 0;
unsigned short int numPowerUpSpecial = 0;


int lastButtonHovered = -1;
int currentButtonHovered = -1;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect mouseRect;
SDL_Rect clippingRect = {0, 0, 1920, 1080};

Game::Game() :
    m_fps(0),
    m_frameCap(60.0f),
    m_lastTime(getTime()),
    m_fpsTimeCounter(0.0),
    m_updateTimer(1.0),
    m_frameTime(1.0 / m_frameCap),
    m_windowWidth(1920),
    m_windowHeight(1080),
    m_currentGameState(GameState::MAINMENU),
    m_lastGameState(GameState::MAINMENU)
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized!..." << std::endl;

        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(m_window)
        {
            std::cout << "Window created!..." << std::endl;
        }

        renderer = SDL_CreateRenderer(m_window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!..." << std::endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "Error : " << Mix_GetError() << std::endl;;
            m_currentGameState = GameState::EXIT;
        }

        if (TTF_Init() == -1)
        {
            std::cerr << "Error : " << TTF_GetError() << std::endl;
        }

        m_currentGameState = GameState::MAINMENU;
    } 
    else 
    {

        m_currentGameState = GameState::EXIT;
    }

    //Load music
    
    /*Mix_Music* gameMusic = Mix_LoadMUS("assets/sound/booty_bounce.mp3");
    if (gameMusic == NULL)
    {
        std::cerr << "Error : " << Mix_GetError() << std::endl;
    }

    m_music.push_back(gameMusic);*/

    //Load sound effects
    Mix_Chunk* soundEffect2 = Mix_LoadWAV("assets/sound/malphite/uwillloose.mp3");
    if (soundEffect2 == NULL)
    {
        std::cerr << "Error : " << Mix_GetError() << std::endl;
    }

    Mix_Chunk* soundEffect = Mix_LoadWAV("assets/sound/menu_sound1.wav");
    if (soundEffect == NULL)
    {
        std::cerr << "Error : " << Mix_GetError() << std::endl;
    }

    Mix_Chunk* soundEffect3 = Mix_LoadWAV("assets/sound/malphite/staydown.mp3");
    if (soundEffect == NULL)
    {
        std::cerr << "Error : " << Mix_GetError() << std::endl;
    }

    m_soundEffects.push_back(soundEffect);
    m_soundEffects.push_back(soundEffect2);
    m_soundEffects.push_back(soundEffect3);

    const char* enemyPath = "assets/zednowakgood.png";
    glm::vec2 enemySrcDimentions(674, 796);
    glm::vec2 enemyDstDimentions(150, 200);

    player = new GameObject("assets/ritson2.png", glm::vec2(0, 0), glm::vec2(950, 950), glm::vec2(64, 64));

    inGameMenu = new Menu("assets/menu.png", glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight));
    mainMenu = new Menu("assets/menu.png", glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight));
    settingsMenu = new Menu("assets/menu.png", glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight));
    gameoverMenu = new Menu("assets/gameovermenu.png", glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight));

    SDL_Color color = { 255, 255, 255 };
    SDL_Color backgroundColor = { 0, 0, 0, 0 };
    SDL_Color backgroundColorGameOver = { 0, 0, 0, 200 };
    
    std::string font = "assets/fonts/NotoSans-Regular.ttf";

    inGameMenu->addButton(font, 20, color, "Continue", glm::vec2(140, 400), glm::vec2(350, 50), backgroundColor, true);
    inGameMenu->addButton(font, 20, color, "New Game", glm::vec2(140, 450), glm::vec2(350, 50), backgroundColor, true);
    inGameMenu->addButton(font, 20, color, "Settings", glm::vec2(140, 500), glm::vec2(350, 50), backgroundColor, true);
    inGameMenu->addButton(font, 20, color, "Quit to Main Menu", glm::vec2(140, 550), glm::vec2(350, 50), backgroundColor, true);
    inGameMenu->addButton(font, 20, color, "Quit", glm::vec2(140, 600), glm::vec2(350, 50), backgroundColor, true);

    mainMenu->addButton(font, 20, color, "New Game", glm::vec2(140, 450), glm::vec2(350, 50), backgroundColor, true);
    mainMenu->addButton(font, 20, color, "Settings", glm::vec2(140, 500), glm::vec2(350, 50), backgroundColor, true);
    mainMenu->addButton(font, 20, color, "Quit", glm::vec2(140, 550), glm::vec2(350, 50), backgroundColor, true);

    settingsMenu->addButton(font, 20, color, "Sound", glm::vec2(140, 450), glm::vec2(350, 50), backgroundColor, true);
    settingsMenu->addButton(font, 20, color, "Graphics", glm::vec2(140, 500), glm::vec2(350, 50), backgroundColor, true);
    settingsMenu->addButton(font, 20, color, "Back", glm::vec2(140, 550), glm::vec2(350, 50), backgroundColor, true);

    gameoverMenu->addText(font, 72, color, "GAME OVER", glm::vec2(0, 0));
    gameoverMenu->setTextPos(0, glm::vec2(m_windowWidth / 2 - gameoverMenu->getTextDims(0).x / 2, m_windowHeight / 2 - gameoverMenu->getTextDims(0).y / 2));
    gameoverMenu->addButton(font, 20, color, "Play Again", glm::vec2(m_windowWidth / 2 - 175, 600), glm::vec2(350, 50), backgroundColorGameOver);
    gameoverMenu->addButton(font, 20, color, "Quit To Main Menu", glm::vec2(m_windowWidth / 2 - 175, 650), glm::vec2(350, 50), backgroundColorGameOver);
    gameoverMenu->addButton(font, 20, color, "Quit", glm::vec2(m_windowWidth / 2 - 175, 700), glm::vec2(350, 50), backgroundColorGameOver);
    
    //m_uiElements.emplace_back("assets/menu.png", glm::vec2(0, 0), glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight));
    //m_uiElements.emplace_back("assets/exit_button.png", glm::vec2(m_uiElements[0].getpos().x + 80, m_uiElements[0].getpos().y + 600), glm::vec2(480, 80), glm::vec2(329, 50));

    //m_texts.emplace_back("assets/fonts/NotoSans-Regular.ttf", 24, color, "EXIT", glm::vec2(222, 608));

    m_entities.push_back(new GameObject("assets/background_arena.png", glm::vec2(0, 0), glm::vec2(1920, 1080), glm::vec2(m_windowWidth, m_windowHeight)));
    m_entities.push_back(player);

    m_enemies.emplace_back(enemyPath, glm::vec2(0, m_windowHeight / 2 - enemyDstDimentions.y / 2),                                    enemySrcDimentions, enemyDstDimentions);
    m_enemies.emplace_back(enemyPath, glm::vec2(m_windowWidth - enemyDstDimentions.x, m_windowHeight / 2 - enemyDstDimentions.y / 2), enemySrcDimentions, enemyDstDimentions);
    m_enemies.emplace_back(enemyPath, glm::vec2(m_windowWidth / 2 - enemyDstDimentions.x / 2, 0),                                     enemySrcDimentions, enemyDstDimentions);
    m_enemies.emplace_back(enemyPath, glm::vec2(m_windowWidth / 2 - enemyDstDimentions.x / 2, m_windowHeight - enemyDstDimentions.y), enemySrcDimentions, enemyDstDimentions);

    SDL_Color bgColor = { 0, 0, 0, 150 };
    text = new Text(font, 20, color, "test", glm::vec2(25, 25), bgColor);
    fps = new Text(font, 20, color, "test", glm::vec2(25, 50), bgColor);
    health = new Text(font, 20, color, "test", glm::vec2(25, 75), bgColor);
    keyboardText = new Text(font, 20, color, "test", glm::vec2(25, 100), bgColor);

    //SDL_RenderSetClipRect(Game::renderer, &clippingRect);
    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));
    std::uniform_int_distribution<int> randX(m_windowWidth, m_windowWidth * 2);
    std::uniform_int_distribution<int> randY(m_windowHeight, m_windowHeight * 2 );

    /*for (int i = 0; i < 10000; i ++)
    {
        m_entities.push_back(new GameObject("assets/dobry_kafelek.png", glm::vec2(randX(randomEngine), randY(randomEngine)), glm::vec2(128, 128), glm::vec2(128, 128)));
    }*/
}

void Game::run()
{
    init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, false);

  /* if (Mix_PlayMusic(m_music[0], -1) == -1)
    {
        std::cout << "Could no play music, Error: " << Mix_GetError() << std::endl;
    }*/

    //SDL_StartTextInput();

    while (m_currentGameState != GameState::EXIT)
    {
        double currentTime = getTime();
        double passedTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        m_fpsTimeCounter += passedTime;
        m_updateTimer += passedTime;

        if (m_fpsTimeCounter >= 1.0)
        {
            double msPerFrame = 1000.0 / (double)m_fps;
            //std::cout << "[ms]" << msPerFrame << " [fps]" << m_fps << std::endl;

            std::stringstream fpsss;
            fpsss << "FPS: " << m_fps << " MS: " << msPerFrame;

            fps->setText(fpsss.str());
            fps->update();

            m_fpsTimeCounter = 0;
            m_fps = 0;
        }

        bool shouldRender = false;
        while (m_updateTimer >= m_frameTime)
        {
            m_inputManager.update();

            handleEvents();
            // begin scene update

            //std::cout << "( " << eventHandler.getMouseCoords().x << " ; " << eventHandler.getMouseCoords().y << " )" << std::endl;

            if (m_currentGameState != GameState::INGAMEMENU)
            {
                if (m_inputManager.isKeyPressed(SDLK_ESCAPE) && m_currentGameState != GameState::MAINMENU)
                {
                    m_lastGameState = m_currentGameState;
                    m_currentGameState = GameState::INGAMEMENU;
                }

                if (m_inputManager.isKeyDown(SDLK_a) || m_inputManager.isKeyDown(SDLK_LEFT))
                {
                    player->setpos(glm::vec2(player->getpos().x - 7, player->getpos().y));
                }

                if (m_inputManager.isKeyDown(SDLK_d) || m_inputManager.isKeyDown(SDLK_RIGHT))
                {
                    player->setpos(glm::vec2(player->getpos().x + 7, player->getpos().y));
                }

                if (m_inputManager.isKeyDown(SDLK_w) || m_inputManager.isKeyDown(SDLK_UP))
                {
                    player->setpos(glm::vec2(player->getpos().x, player->getpos().y - 7));
                }

                if (m_inputManager.isKeyDown(SDLK_s) || m_inputManager.isKeyDown(SDLK_DOWN))
                {
                    player->setpos(glm::vec2(player->getpos().x, player->getpos().y + 7));
                }

                if (player->getpos().x < 0)
                {
                    player->setpos(glm::vec2(0, player->getpos().y));
                }
                else if (player->getpos().x > m_windowWidth - player->getDims().x)
                {
                    player->setpos(glm::vec2(m_windowWidth - player->getDims().x, player->getpos().y));
                }

                if (player->getpos().y < 0)
                {
                    player->setpos(glm::vec2(player->getpos().x, 0));
                }
                else if (player->getpos().y > m_windowHeight - player->getDims().y)
                {
                    player->setpos(glm::vec2(player->getpos().x, m_windowHeight - player->getDims().y));
                }
            }
            else if (m_currentGameState == GameState::INGAMEMENU)
            {
                if (m_inputManager.isKeyPressed(SDLK_ESCAPE))
                {
                    m_lastGameState = m_currentGameState;
                    m_currentGameState = GameState::PLAY;
                }
            }

            update(m_frameTime);

            // end scene update

            m_updateTimer -= m_frameTime;
            shouldRender = true;
        }

        if (shouldRender)
        {
            // Begin scene render
            render();
            // End scene render

            m_fps++;
        }
        else
        {
            SDL_Delay(1);
        }
    }
    clean();
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                m_inputManager.onKeyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_inputManager.onKeyUp(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_inputManager.onKeyDown(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_inputManager.onKeyUp(event.button.button);
                break;
            case SDL_MOUSEMOTION:
                m_inputManager.setMouseCoords(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEWHEEL:
                
                break;
            case SDL_TEXTINPUT:
                //keyboardTextString += event.text.text;
                break;
            case SDL_TEXTEDITING:
                
                break;
            case SDL_QUIT:
                m_currentGameState = GameState::EXIT;
                break;
            default:
                break;
        }
    }
}

void Game::update(float deltaTime)
{
    //std::cout << "( " << exitButton->getpos().x << " ; " << exitButton->getpos().y << " )" << std::endl;
    //std::cout << mouseButton.getAmt() << std::endl;

    mouseRect.x = m_inputManager.getMouseCoords().x;
    mouseRect.y = m_inputManager.getMouseCoords().y;
    mouseRect.w = 1;
    mouseRect.h = 1;

    std::stringstream keyboardTextInput;
    keyboardTextInput << "Input: " << keyboardTextString;
    keyboardText->setText(keyboardTextInput.str());
    keyboardText->update();

    if (m_currentGameState == GameState::PLAY)
    {
        std::stringstream ss;
        ss << "Player Position: (" << player->getpos().x << " | " << player->getpos().y << " )";

        text->setText(ss.str());
        text->update();


        std::stringstream healthss;
        healthss << "Player health: " << player->getHealth();

        health->setText(healthss.str());
        health->update();

        

        counter++;
        counterPowerUp++;
        counterPowerUpSpecial++;

        num = glm::round(60 * m_frameTime);
        num *= 60;

        numPowerUp = glm::round(600 * m_frameTime);
        numPowerUp *= 60;

        numPowerUpSpecial = glm::round(1800 * m_frameTime);
        numPowerUpSpecial *= 60;

        if (counterPowerUp % numPowerUp == 0)
        {
            std::mt19937 randomEngine;
            randomEngine.seed(time(nullptr));
            std::uniform_int_distribution<int> randX(100, m_windowWidth - 100);
            std::uniform_int_distribution<int> randY(100, m_windowHeight - 100);

            m_powerUps.emplace_back("assets/bialko.png", glm::vec2(randX(randomEngine), randY(randomEngine)), glm::vec2(220, 350), glm::vec2(54, 88), 300);

            counterPowerUp = 0;
        }

        if (counterPowerUpSpecial % numPowerUpSpecial == 0)
        {
            std::mt19937 randomEngine;
            randomEngine.seed(time(nullptr));
            std::uniform_int_distribution<int> randX(250, m_windowWidth - 250);
            std::uniform_int_distribution<int> randY(250, m_windowHeight - 250);

            int x = randX(randomEngine);
            int y = randY(randomEngine);

            m_powerUps.emplace_back("assets/ritau_sport.png", glm::vec2(x, y), glm::vec2(1000, 1000), glm::vec2(250, 250), 300);


            counterPowerUpSpecial = 0;
        }

        for (int i = 0; i < m_entities.size(); i++)
        {
            m_entities[i]->update();
        }

        for (int i = 0; i < m_enemies.size(); i++)
        {
            m_enemies[i].update();
            m_enemies[i].sendBullet(m_bullets, player->getpos(), 8, 420, true, 10, counter, num);
        }

        for (int i = 0; i < m_bullets.size();)
        {
            if (m_bullets[i].update())
            {
                m_bullets[i] = m_bullets.back();
                m_bullets.pop_back();
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < m_bullets.size(); i++)
        {
            if (Collision::AABB(m_bullets[i].getRect(), player->getRect()))
            {
                player->setHealth(player->getHealth() - 10);

                m_bullets[i] = m_bullets.back();
                m_bullets.pop_back();

                if (player->getHealth() <= 0)
                {
                    m_lastGameState = m_currentGameState;
                    m_currentGameState = GameState::GAMEOVER;

                    if (Mix_PlayChannel(-1, m_soundEffects[2], 0) == -1)
                    {
                        std::cout << Mix_GetError() << std::endl;
                    }
                }
            }
        }

        for (int i = 0; i < m_powerUps.size();)
        {
            if (m_powerUps[i].update())
            {
                m_powerUps[i] = m_powerUps.back();
                m_powerUps.pop_back();
            }
            else
            {
                i++;
            }
        }

        for (int i = 0; i < m_powerUps.size(); i++)
        {
            if (Collision::AABB(m_powerUps[i].getRect(), player->getRect()))
            {
                if (player->getHealth() + 20 <= 100)
                {
                    player->setHealth(player->getHealth() + 20);
                }
                else
                {
                    player->setHealth(100);
                }

                m_powerUps[i] = m_powerUps.back();
                m_powerUps.pop_back();
            }
        }
    }
    else if (m_currentGameState == GameState::INGAMEMENU)
    {
        inGameMenu->update();

        if (Collision::AABB(inGameMenu->getButtonRect(0), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::PLAY;
        }
        else if (Collision::AABB(inGameMenu->getButtonRect(1), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            reset();
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::PLAY;
            if (Mix_PlayChannel(-1, m_soundEffects[1], 0) == -1)
            {
                std::cout << Mix_GetError() << std::endl;
            }
        }
        else if (Collision::AABB(inGameMenu->getButtonRect(2), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::SETTINGSMENU;
            lastButtonHovered = -1;
        }
        else if (Collision::AABB(inGameMenu->getButtonRect(3), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::MAINMENU;
            lastButtonHovered = -1;
        }
        else if (Collision::AABB(inGameMenu->getButtonRect(4), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::EXIT;
        }

        //checking if rendering overlay is needed

        if (Collision::AABB(inGameMenu->getButtonRect(0), mouseRect))
        {
            inGameMenu->setButtonOverlay(true, 0);

            if (lastButtonHovered != 0)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 0;
            }
        }
        else
        {
            if (lastButtonHovered == 0)
            {
                inGameMenu->setButtonOverlay(true, 0);
            }
            else
            {
                inGameMenu->setButtonOverlay(false, 0);
            }
        }

        if (Collision::AABB(inGameMenu->getButtonRect(1), mouseRect))
        {
            inGameMenu->setButtonOverlay(true, 1);

            if (lastButtonHovered != 1)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 1;
            }
        }
        else
        {
            if (lastButtonHovered == 1)
            {
                inGameMenu->setButtonOverlay(true, 1);
            }
            else
            {
                inGameMenu->setButtonOverlay(false, 1);
            }
        }

        if (Collision::AABB(inGameMenu->getButtonRect(2), mouseRect))
        {
            inGameMenu->setButtonOverlay(true, 2);

            if (lastButtonHovered != 2)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 2;
            }
        }
        else
        {
            if (lastButtonHovered == 2)
            {
                inGameMenu->setButtonOverlay(true, 2);
            }
            else
            {
                inGameMenu->setButtonOverlay(false, 2);
            }
        }

        if (Collision::AABB(inGameMenu->getButtonRect(3), mouseRect))
        {
            inGameMenu->setButtonOverlay(true, 3);

            if (lastButtonHovered != 3)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 3;
            }
        }
        else
        {
            if (lastButtonHovered == 3)
            {
                inGameMenu->setButtonOverlay(true, 3);
            }
            else
            {
                inGameMenu->setButtonOverlay(false, 3);
            }
        }

        if (Collision::AABB(inGameMenu->getButtonRect(4), mouseRect))
        {
            inGameMenu->setButtonOverlay(true, 4);

            if (lastButtonHovered != 4)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 4;
            }
        }
        else
        {
            if (lastButtonHovered == 4)
            {
                inGameMenu->setButtonOverlay(true, 4);
            }
            else
            {
                inGameMenu->setButtonOverlay(false, 4);
            }
        }
            //**************************************//
    }
    else if (m_currentGameState == GameState::MAINMENU)
    {
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

        mainMenu->update();

        if (Collision::AABB(mainMenu->getButtonRect(0), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            reset();
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::PLAY;
            if (Mix_PlayChannel(-1, m_soundEffects[1], 0) == -1)
            {
                std::cout << Mix_GetError() << std::endl;
            }
        }
        else if (Collision::AABB(mainMenu->getButtonRect(1), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::SETTINGSMENU;
            lastButtonHovered = -1;
        }
        else if (Collision::AABB(mainMenu->getButtonRect(2), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_lastGameState = m_currentGameState;
            m_currentGameState = GameState::EXIT;
        }

        //checking if rendering overlay is needed
        if (Collision::AABB(mainMenu->getButtonRect(0), mouseRect))
        {
            mainMenu->setButtonOverlay(true, 0);

            if (lastButtonHovered != 0)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 0;
            }
        }
        else
        {
            if (lastButtonHovered == 0)
            {
                mainMenu->setButtonOverlay(true, 0);
            }
            else
            {
                mainMenu->setButtonOverlay(false, 0);
            }
        }

        if (Collision::AABB(mainMenu->getButtonRect(1), mouseRect))
        {
            mainMenu->setButtonOverlay(true, 1);

            if (lastButtonHovered != 1)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 1;
            }
        }
        else
        {
            if (lastButtonHovered == 1)
            {
                mainMenu->setButtonOverlay(true, 1);
            }
            else
            {
                mainMenu->setButtonOverlay(false, 1);
            }
        }

        if (Collision::AABB(mainMenu->getButtonRect(2), mouseRect))
        {
            mainMenu->setButtonOverlay(true, 2);

            if (lastButtonHovered != 2)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 2;
            }
        }
        else
        {
            if (lastButtonHovered == 2)
            {
                mainMenu->setButtonOverlay(true, 2);
            }
            else
            {
                mainMenu->setButtonOverlay(false, 2);
            }
        }
        //**************************************//
        
    }
    else if (m_currentGameState == GameState::SETTINGSMENU)
    {
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

        settingsMenu->update();

        if (Collision::AABB(settingsMenu->getButtonRect(0), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            //setMenuOptionArea(sound);
        }
        else if (Collision::AABB(settingsMenu->getButtonRect(1), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            //setMenuOptionArea(graphics);
        }
        else if (Collision::AABB(settingsMenu->getButtonRect(2), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            GameState buffer = m_currentGameState;
            m_currentGameState = m_lastGameState;
            m_lastGameState = buffer;
            lastButtonHovered = -1;
        }

        //checking if rendering overlay is needed
        if (Collision::AABB(settingsMenu->getButtonRect(0), mouseRect))
        {
            settingsMenu->setButtonOverlay(true, 0);

            if (lastButtonHovered != 0)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 0;
            }
        }
        else
        {
            if (lastButtonHovered == 0)
            {
                settingsMenu->setButtonOverlay(true, 0);
            }
            else
            {
                settingsMenu->setButtonOverlay(false, 0);
            }
        }

        if (Collision::AABB(settingsMenu->getButtonRect(1), mouseRect))
        {
            settingsMenu->setButtonOverlay(true, 1);

            if (lastButtonHovered != 1)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 1;
            }
        }
        else
        {
            if (lastButtonHovered == 1)
            {
                settingsMenu->setButtonOverlay(true, 1);
            }
            else
            {
                settingsMenu->setButtonOverlay(false, 1);
            }
        }

        if (Collision::AABB(settingsMenu->getButtonRect(2), mouseRect))
        {
            settingsMenu->setButtonOverlay(true, 2);

            if (lastButtonHovered != 2)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 2;
            }
        }
        else
        {
            if (lastButtonHovered == 2)
            {
                settingsMenu->setButtonOverlay(true, 2);
            }
            else
            {
                settingsMenu->setButtonOverlay(false, 2);
            }
        }
        //**************************************//
    }
    else if (m_currentGameState == GameState::GAMEOVER)
    {
        gameoverMenu->update();

        if (Collision::AABB(gameoverMenu->getButtonRect(0), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_currentGameState = GameState::PLAY;
            reset();
        }
        else if (Collision::AABB(gameoverMenu->getButtonRect(1), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_currentGameState = GameState::MAINMENU;
        }
        else if (Collision::AABB(gameoverMenu->getButtonRect(2), mouseRect) && m_inputManager.isKeyPressed(Input::MOUSE_LEFT_BUTTON))
        {
            m_currentGameState = GameState::EXIT;
        }

        if (Collision::AABB(gameoverMenu->getButtonRect(0), mouseRect))
        {
            if (lastButtonHovered != 0)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 0;
            }
        }
        else if (Collision::AABB(gameoverMenu->getButtonRect(1), mouseRect))
        {
            if (lastButtonHovered != 1)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 1;
            }
        }
        else if (Collision::AABB(gameoverMenu->getButtonRect(2), mouseRect))
        {
            if (lastButtonHovered != 2)
            {
                if (Mix_PlayChannel(-1, m_soundEffects[0], 0) == -1)
                {
                    std::cout << Mix_GetError() << std::endl;
                }

                lastButtonHovered = 2;
            }
        }
    }
} 

void Game::render()
{
    SDL_RenderClear(renderer);

    if (m_currentGameState != GameState::MAINMENU && m_currentGameState != GameState::SETTINGSMENU)
    {
        for (int i = 0; i < m_entities.size(); i++)
        {
            m_entities[i]->render();
        }

        for (int i = 0; i < m_enemies.size(); i++)
        {
            m_enemies[i].draw();
        }

        for (int i = 0; i < m_bullets.size(); i++)
        {
            m_bullets[i].draw();
        }

        for (int i = 0; i < m_powerUps.size(); i++)
        {
            m_powerUps[i].draw();
        }

        text->render();
        fps->render();
        health->render();
        keyboardText->render();
    }

    if (m_currentGameState == GameState::INGAMEMENU)
    {
        inGameMenu->draw();
    }
    else if (m_currentGameState == GameState::MAINMENU)
    {
        mainMenu->draw();
    }
    else if (m_currentGameState == GameState::SETTINGSMENU)
    {
        settingsMenu->draw();
    }
    else if (m_currentGameState == GameState::GAMEOVER)
    {
        gameoverMenu->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        delete m_entities[i];
        m_entities[i] = 0;
    }

    delete inGameMenu;
    delete mainMenu;
    delete settingsMenu;
    delete gameoverMenu;

    delete text;
    delete fps;
    delete health;
    delete keyboardText;

    //SDL_StopTextInput();

    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game cleaned!..." << std::endl;
}

void Game::reset()
{
    player->setpos(glm::vec2(m_windowWidth / 2 - player->getDims().x / 2, m_windowHeight / 2 - player->getDims().y / 2));
    player->setHealth(100);
    m_bullets.clear();
    m_powerUps.clear();
    counter = 0;
    counterPowerUp = 0;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#elif defined(__linux__)
#define OS_LINUX
#elif __cplusplus >= 201103L
#define OS_OTHER_CPP11
#else
#define OS_OTHER
#endif

#ifdef OS_WINDOWS
#include <Windows.h>
#include <iostream>
static double g_freq;
static bool g_timerInitialized = false;
#endif

#ifdef OS_LINUX
#include <sys/time.h>
static const long NANOSECONDS_PER_SECOND = 1000000000L;
#endif

#ifdef OS_OTHER
#include <SDL.h>
#endif

#ifdef OS_OTHER_CPP11
#include <chrono>
static std::chrono::system_clock::time_point m_epoch = std::chrono::high_resolution_clock::now();
#endif

double Game::getTime()
{
    #ifdef OS_WINDOWS
        if (!g_timerInitialized)
        {
            LARGE_INTEGER li;
            if (!QueryPerformanceFrequency(&li))
                std::cerr << "QueryPerformanceFrequency failed in timer initialization" << std::endl;

            g_freq = double(li.QuadPart);
            g_timerInitialized = true;
        }

        LARGE_INTEGER li;
        if (!QueryPerformanceCounter(&li))
            std::cerr << "QueryPerformanceCounter failed in get time!" << std::endl;

        return double(li.QuadPart) / g_freq;
    #endif

    #ifdef OS_LINUX
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return (double)(((long)ts.tv_sec * NANOSECONDS_PER_SECOND) + ts.tv_nsec) / ((double)(NANOSECONDS_PER_SECOND));
    #endif

    #ifdef OS_OTHER_CPP11
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;
    #endif

    #ifdef OS_OTHER
        return (double)SDL_GetTicks() / 1000.0;
    #endif
}



