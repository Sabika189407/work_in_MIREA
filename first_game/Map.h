#pragma once
#include <iostream>
#include <exception>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

class Map: public sf::Drawable, public sf::Transformable
{
private:
    float target_tile_size = 40.0f;//if ur changing change in Pacman.cpp
    unsigned int cols = 15;
    unsigned int rows = 20;
    float tile_size = 40.0f;
    float dot_radius = 4.0f;
    float potion_size = 8.0f;
    int seed = 1234;
    
    const sf::Texture* m_wall_texture = nullptr;

    //int max_potions = 15;
    /*std::vector<sf::RectangleShape> walls;*/
    
    std::vector<std::vector<int>> map_grid;
    /*Vertex Array (массив вершин) — это структура данных,
    которая объединяет множество графических примитивов
    (точек, линий или треугольников) в один массив,
    чтобы отрисовать их все за один вызов видеокарты (Draw Call).
    Вместо того чтобы просить видеокарту нарисовать каждую стену или плитку по отдельности,
    вы передаете ей один большой массив с координатами и текстурами.
    */
    sf::VertexArray m_walls;
    std::vector<sf::CircleShape> dots;
    std::vector<sf::RectangleShape> potions;
    //sfml draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Map(unsigned int window_width, unsigned int window_height, const sf::Texture& wall_tex, const sf::Texture& potion_tex);//turn matrix into grafix
    float get_tile_size() const;
    unsigned int get_cols() const;
    unsigned int get_rows() const;
    float hash(int, int);
    //void render(sf::RenderWindow& window);           draw that shit
    bool check_collision(const sf::FloatRect& borders) const;//func that checks if out stroller collises into borders
    
    bool is_wall(int r, int c) const
    {
        if (r < 0 || r >= static_cast<int>(rows) || c < 0 || c >= static_cast<int>(cols))
        {
            return true;
        }
        return map_grid[r][c] == 1;
    }
    int check_dot_collisions(const sf::FloatRect&);
    bool check_potion_collisions(const sf::FloatRect&);
    int get_remaining_dots() const;
    int get_remaining_potions() const;
};