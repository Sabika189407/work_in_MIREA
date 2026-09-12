#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "Pacman.h"
#include "Map.h"
#include "Ghost.h"
#include "PauseMenu.h"
#include "Registration.h"
#include "StartScreen.h"
#include "MainMenu.h"
#include "EndScreen.h"

enum class Game_state
{
    INTRO_VIDEO,
    START_SCREEN,
    CARD_REGISTRATION,
    MAIN_MENU,
    PLAYING,
    PAUSED,
    VICTORY,
    GAME_OVER
};

class Game
{
private:
    unsigned int window_width;
    unsigned int window_height; 
    
    Game_state current_state;

    sf::RenderWindow window;
    sf::Sprite wall_sprite;
    sf::Sprite potion_sprite;
    sf::Sprite pacman_sprite;
    
    sf::Font font;
    sf::Text score_text;

    sf::Texture wall_tex;
    sf::Texture potion_tex;
    sf::Texture pacman_tex;
    sf::Texture pacman_strong_tex;
    sf::Texture ghost_tex;

    Map map;
    PacMan stroller;
    
    std::vector<Ghost> ghosts;
    float game_time = 0.0f;
    int released_ghosts = 0;
    int score = 0;
    sf::Text timer_text;

    Card_form card_form;
    Start_screen start_screen;
    Main_menu main_menu;
    End_screen end_screen;

    Game(unsigned int w, unsigned int h);
    void restart_game();

    bool is_paused = false;
    Pause_menu pause_menu;
    void process_events();
    void update(float dt);
    void render();

    std::vector<sf::Texture> intro_frames;
    sf::Sprite intro_sprite;
    size_t current_frame = 0;
    float frame_timer = 0.0f;
    float frame_duration = 1.0f / 30.0f;

public:
    Game();
    void run();
};

