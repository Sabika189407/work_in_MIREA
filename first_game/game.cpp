#include "game.h"

//check videomode
static sf::VideoMode check_videomode()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    if (mode.width == 0 || mode.height == 0)
    {
        mode.width = 800;
        mode.height = 600;
    }
    return mode;
}

//out of main
Game::Game() : Game(check_videomode().width, check_videomode().height) 
{
}

//ready w and h
Game::Game(unsigned int w, unsigned int h)
    : window_width(w), window_height(h), window(sf::VideoMode(w, h), "Stroller - Childhood", sf::Style::Fullscreen),
      map(([&](){ wall_tex.loadFromFile("assets/wall.png"); potion_tex.loadFromFile("assets/potion.png"); return Map(window_width, window_height, wall_tex, potion_tex); })()),
      stroller(([&](){ 
          pacman_tex.loadFromFile("assets/pacman.png"); 
          pacman_strong_tex.loadFromFile("assets/pacman_strong.png"); // Загружаем усиленную текстуру
          return PacMan(map, pacman_tex, pacman_strong_tex); 
      })()),
      pause_menu(static_cast<float>(window_width), static_cast<float>(window_height)),
      card_form(static_cast<float>(window_width), static_cast<float>(window_height)),
      start_screen(static_cast<float>(window_width), static_cast<float>(window_height)),
      main_menu(static_cast<float>(window_width), static_cast<float>(window_height)),
      end_screen(static_cast<float>(window_width), static_cast<float>(window_height)),
      current_state(Game_state::INTRO_VIDEO)
{

    int total_frames = 0;
    while (true)
    {
        std::ifstream file("assets/intro/frame_" + std::to_string(total_frames) + ".png");
        if (!file.good()) break;
        total_frames++;
    }

    if (total_frames > 0)
    {
        intro_frames.resize(total_frames);
        for (int i = 0; i < total_frames; ++i)
        {
            intro_frames[i].loadFromFile("assets/intro/frame_" + std::to_string(i) + ".png");
        }

        intro_sprite.setTexture(intro_frames[0]);
        
        sf::Vector2u tex_size = intro_frames[0].getSize();
        if (tex_size.x > 0 && tex_size.y > 0)
        {
            intro_sprite.setScale(static_cast<float>(window_width) / tex_size.x, static_cast<float>(window_height) / tex_size.y);
        }
    } 

    //window.create(sf::VideoMode(window_width, window_height), "Stroller - Childhood", sf::Style::Fullscreen);
    ghost_tex.loadFromFile("assets/ghost.png");

    ghosts.push_back(Ghost(map, Ghost_type::RANDOM, sf::Color::Green, ghost_tex));
    ghosts.push_back(Ghost(map, Ghost_type::CHASER, sf::Color::Red, ghost_tex));
    ghosts.push_back(Ghost(map, Ghost_type::CHASER, sf::Color::Magenta, ghost_tex));
    window.setFramerateLimit(120);

    font.loadFromFile("assets/minecraft.ttf");
    wall_tex.loadFromFile("assets/wall.png");
    potion_tex.loadFromFile("assets/potion.png");
    pacman_tex.loadFromFile("assets/pacman.png");

    wall_sprite.setTexture(wall_tex);
    potion_sprite.setTexture(potion_tex);
    pacman_sprite.setTexture(pacman_tex);

    score_text.setFont(font);
    score_text.setString("Score: 0");
    score_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::Black);
    score_text.setPosition(10.0f, 10.0f);

    timer_text.setFont(font);
    timer_text.setCharacterSize(24);
    timer_text.setFillColor(sf::Color::Black);
    timer_text.setPosition(window_width - 220.0f, 10.0f);
}

void Game::restart_game()
{
    score = 0;
    game_time = 0.0f;
    released_ghosts = 0;
    map = Map(window_width, window_height, wall_tex, potion_tex); //textures
    stroller = PacMan(map, pacman_tex, pacman_strong_tex);
    ghosts.clear();
    ghosts.push_back(Ghost(map, Ghost_type::RANDOM, sf::Color::Green, ghost_tex));
    ghosts.push_back(Ghost(map, Ghost_type::CHASER, sf::Color::Red, ghost_tex));
    ghosts.push_back(Ghost(map, Ghost_type::CHASER, sf::Color::Magenta, ghost_tex));
}

void::Game::run()
{
    sf::Clock clock;

    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        process_events();
        update(dt);
        render();
    }
}

void Game::process_events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (current_state == Game_state::INTRO_VIDEO)
        {
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
            {
                current_state = Game_state::START_SCREEN;
            }
            continue;
        }

        //typing text
        if (event.type == sf::Event::TextEntered)
        {
            if (current_state == Game_state::CARD_REGISTRATION)
            {
                card_form.handle_text_input(event.text.unicode);
            }
        }

        //mouse click
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

            switch (current_state)
            {
                case Game_state::START_SCREEN:
                {
                    if (start_screen.is_start_clicked(mouse_pos))
                    {
                        current_state = Game_state::CARD_REGISTRATION;
                    }
                    break;
                }

                case Game_state::CARD_REGISTRATION:
                {
                    card_form.handle_click(mouse_pos); //selecting input label
                    if (card_form.is_submit_clicked(mouse_pos)) //check registration button
                    {
                        current_state = Game_state::MAIN_MENU;
                    }
                    break;
                }

                case Game_state::MAIN_MENU:
                {
                    Main_menu_option opt = main_menu.handle_click(mouse_pos);
                    if (opt == Main_menu_option::PLAY)
                    {
                        current_state = Game_state::PLAYING;
                    }
                    else if (opt == Main_menu_option::EXIT)
                    {
                        window.close();
                    }
                    break;
                }

                case Game_state::PAUSED:
                {
                    Menu_option option = pause_menu.handle_click(mouse_pos);
                    if (option == Menu_option::CONTINUE)
                    {
                        current_state = Game_state::PLAYING;
                    }
                    else if (option == Menu_option::EXIT)
                    {
                        window.close();
                    }
                    break;
                }

                case Game_state::VICTORY:
                case Game_state::GAME_OVER:
                {
                    if (end_screen.is_restart_clicked(mouse_pos))
                    {
                        restart_game();
                        current_state = Game_state::PLAYING;
                    }
                    break;
                }

                default:
                    break;
            }
        }

        // esc for pause
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (current_state == Game_state::PLAYING)
                {
                    current_state = Game_state::PAUSED;
                } else if (current_state == Game_state::PAUSED)
                {
                    current_state = Game_state::PLAYING;
                }
            }
        }
    }
}

void Game::update(float dt)
{
    if (current_state == Game_state::INTRO_VIDEO)
    {
        if (intro_frames.empty())
        {
            current_state = Game_state::START_SCREEN;
            return;
        }

        frame_timer += dt;
        if (frame_timer >= frame_duration)
        {
            frame_timer -= frame_duration;
            current_frame++;

            if (current_frame < intro_frames.size())
            {
                intro_sprite.setTexture(intro_frames[current_frame]);
            }
            else
            {
                // Видео закончилось — переходим к стартовому экрану!
                current_state = Game_state::START_SCREEN;
            }
        }
        return;
    }

    if (current_state == Game_state::PLAYING)
    {
        game_time += dt;

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << game_time;
        timer_text.setString("Time: " + ss.str() + "s");

        if(released_ghosts < 3 && game_time >= (released_ghosts + 1) * 5.0f)
        {
            ghosts[released_ghosts].release_from_house();
            released_ghosts++;
        }

        stroller.handleInput();
        stroller.update(dt, map);

        //ate dots
        int points = map.check_dot_collisions(stroller.getBounds());
        if(points > 0)
        {
            score += points;
        }

        //ate potions
        if(map.check_potion_collisions(stroller.getBounds()))
        {
            score += 50;
            stroller.activate_potion(5.0f);
        }

        //ate ghosts
        for (auto& ghost : ghosts)
        {
            ghost.set_frightened(stroller.is_ghost_hunter());
            ghost.update(dt, map, stroller.getBounds().getPosition());

            if (stroller.getBounds().intersects(ghost.get_bounds()))
            {
                if (ghost.get_state() == Ghost_state::FRIGHTENED)
                {
                    score += 200;
                    ghost.reset();
                }
                else if (ghost.get_state() == Ghost_state::ACTIVE)
                {
                    end_screen.setup(false, score, game_time); //loose
                    current_state = Game_state::GAME_OVER;
                    return;
                }
            }
        }

        if(map.get_remaining_dots() == 0 && map.get_remaining_potions() == 0)
        {
            end_screen.setup(true, score, game_time); //win
            current_state = Game_state::VICTORY;
        }

        score_text.setString("Score: " + std::to_string(score));
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    switch (current_state)
    {
        case Game_state::INTRO_VIDEO:
        {
            window.draw(intro_sprite);
            break;
        }
        case Game_state::START_SCREEN:
        {
            start_screen.render(window);
            break;
        }

        case Game_state::CARD_REGISTRATION:
        {
            card_form.render(window);
            break;
        }

        case Game_state::MAIN_MENU:
        {
            main_menu.render(window);
            break;
        }

        case Game_state::PLAYING:
        {
            window.draw(map);
            stroller.render(window);

            for (auto& ghost : ghosts)
            {
                ghost.render(window);
            }

            window.draw(score_text);
            window.draw(timer_text);
            break;
        }
        case Game_state::PAUSED:
        {
            window.draw(map);
            stroller.render(window);

            for (auto& ghost : ghosts)
            {
                ghost.render(window);
            }

            window.draw(score_text);

            pause_menu.render(window);
            break;
        }
        case Game_state::VICTORY:
        case Game_state::GAME_OVER:
        {
            end_screen.render(window);
            break;
        }
    }
    window.display();
}