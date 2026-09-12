#include "Map.h"
/*Map::Map()
{
    for(size_t r = 0; r < map_grid.size(); r++)
    {
        for(size_t c = 0; c < map_grid[r].size(); c++)
        {
            float x = c * tile_size;
            float y = r * tile_size;
            if (map_grid[r][c] == 1)
            {
                sf::RectangleShape wall(sf::Vector2f(tile_size, tile_size));
                wall.setFillColor(sf::Color::Blue);
                wall.setPosition(x, y);
                walls.push_back(wall);
            }

            else if(map_grid[r][c] == 3)
            {
                sf::CircleShape agusha(4.0f);
                agusha.setFillColor(sf::Color::White);
                agusha.setPosition(x + tile_size / 2.0f - 4.0f, y + tile_size / 2.0f - 4.0f);
                dots.push_back(agusha);
            }
            else if(map_grid[r][c] == 4)
            {
                sf::RectangleShape monster(sf::Vector2f(8.0f, 8.0f));
                monster.setFillColor(sf::Color::Green);
                monster.setPosition(x + tile_size / 2.0f - 4.0f, y + tile_size / 2.0f - 4.0f);
                potions.push_back(monster);
            }
        }
        
    }
}*/

Map::Map(unsigned int window_width, unsigned int window_height, const sf::Texture& wall_tex, const sf::Texture& potion_tex)
    :cols(window_width / target_tile_size), rows(window_height / target_tile_size),
    tile_size(std::min(static_cast<float>(window_width) / cols, static_cast<float>(window_height) / rows)),
    seed(static_cast<int>(std::time(nullptr))),
    dot_radius(tile_size * 0.1f), potion_size(tile_size * 1.0f), m_wall_texture(&wall_tex) //potion size was 0.25
{
    if (rows < 7 || cols < 7)
    {
    std::cerr << "Error: Window size is too small for generating map!" << std::endl;
    std::exit(1);
    }
    map_grid.resize(rows, std::vector<int>(cols, 0));
    unsigned int mid_row = rows/2;
    unsigned int mid_col = cols/2;
    for (unsigned int r = 0; r < rows; r++)
    {
        for (unsigned int c = 0; c < cols; c++)
        {
            bool is_border = (r == 0 || r == rows - 1 || c == 0 || c == cols - 1); //borders - perimeter
            bool is_room_wall = (r == mid_row - 2 || r == mid_row + 2) && (c >= mid_col - 2 && c <= mid_col + 2) ||
                    (c == mid_col - 2 || c == mid_col + 2) && (r >= mid_row - 2 && r <= mid_row + 2);                //mid room
            if (is_border || is_room_wall)
            {
                map_grid[r][c] = 1;
            }
        }
    }
    map_grid[mid_row-2][mid_col] = 0;
    map_grid[mid_row-2][mid_col+1] = 0;
    map_grid[mid_row-2][mid_col-1] = 0; //exit from the room

    for(unsigned int r = 2; r < rows - 2; r += 2)
    {
        for (unsigned int c = 2; c < cols -2 ; c += 2)
        {
            bool is_near_center = (r >= mid_row - 3 && r <= mid_row + 3) && (c >= mid_col - 3 && c <= mid_col + 3); //ignore central room
            if (is_near_center)
            {
                continue;
            }
            float h = hash(r, c); //hash for this coordinate
            if (h > 0.35f) //if hash is more than this number - wall
            {
                map_grid[r][c] = 1;
            }
            if (h > 0.75f && c + 1 < cols - 1)
            {
                map_grid[r][c+1] = 1;
            }
        }
    }

    //int potions_spawned = 0;
    int num_c = 6;
    int num_r = 10;
    unsigned int zone_w = cols/num_c;
    unsigned int zone_h = rows/num_r;
    for (int zx = 0; zx < num_c; zx++)
    {
        for (int zy = 0; zy < num_r; zy++)
        {
            bool placed = false;
            //scanning zx zy block
            unsigned int max_r = std::min((zy + 1) * zone_h, rows - 1);
            unsigned int max_c = std::min((zx + 1) * zone_w, cols - 1);
            for (unsigned int r = zy * zone_h + 1; r < max_r && !placed; r++)
            {
                for (unsigned int c = zx * zone_w + 1; c < max_c && !placed; c++)
                {
                    bool is_in_room = (r >= mid_row - 2 && r <= mid_row + 2) && (c >= mid_col - 2 && c <= mid_col + 2);
                    if (map_grid[r][c] == 0 && !is_in_room)
                    {
                        map_grid[r][c] = 4;
                        placed = true;
                    }
                }
            }
        }
    }

    for (unsigned int r = 1; r < rows - 1; r++)
    {
        for (unsigned int c = 1; c < cols - 1; c++)
        {
            bool is_in_room = (r >= mid_row - 2 && r <= mid_row + 2) && (c >= mid_col - 2 && c <= mid_col + 2);

            if (map_grid[r][c] == 0 && !is_in_room)
            {
                map_grid[r][c] = 3;
            }
        }
    }


    m_walls.setPrimitiveType(sf::Quads);
    m_walls.clear();

    sf::Vector2u w_tex_size = wall_tex.getSize();

    for(size_t r = 0; r < map_grid.size(); r++)
    {
        for(size_t c = 0; c < map_grid[r].size(); c++)
        {
            float x = c * tile_size;
            float y = r * tile_size;
            if (map_grid[r][c] == 1) // wall
            {
                m_walls.append(sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(0.f, 0.f)));
                m_walls.append(sf::Vertex(sf::Vector2f(x + tile_size, y), sf::Vector2f(w_tex_size.x, 0.f)));
                m_walls.append(sf::Vertex(sf::Vector2f(x + tile_size, y + tile_size), sf::Vector2f(w_tex_size.x, w_tex_size.y)));
                m_walls.append(sf::Vertex(sf::Vector2f(x, y + tile_size), sf::Vector2f(0.f, w_tex_size.y)));
            }

            else if(map_grid[r][c] == 3)
            {
                sf::CircleShape agusha(dot_radius);
                agusha.setFillColor(sf::Color::White);
                agusha.setPosition(x + tile_size / 2.0f - dot_radius, y + tile_size / 2.0f - dot_radius);
                dots.push_back(agusha);
            }
            else if(map_grid[r][c] == 4)
            {
                sf::RectangleShape monster(sf::Vector2f(potion_size, potion_size));
                monster.setTexture(&potion_tex); //tex into rectangle shape
                monster.setPosition(x + tile_size / 2.0f - potion_size / 2.0f, y + tile_size / 2.0f - potion_size / 2.0f);
                potions.push_back(monster);
            }
        }   
    } 
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //transform map
    states.transform *= getTransform();

    //draw all of walls
    states.texture = m_wall_texture;
    target.draw(m_walls, states);

    states.texture = nullptr; //reset texture for other objects

    //draw all other objects
    for (const auto& monster : potions)
    {
        target.draw(monster, states);
    }

    for (const auto& agusha : dots)
    {
        target.draw(agusha, states);
    }
}

float Map::get_tile_size() const
{
    return tile_size;
}

unsigned int Map::get_cols() const
{
    return cols;
}

unsigned int Map::get_rows() const
{
    return rows;
}

float Map::hash(int r, int c)
{
    int n = r * 374761393 + c * 668265263 + seed * 144675703;
    n = (n ^ (n >> 13)) * 1274126177;
    return static_cast<float>(n & 0x7FFFFFFF) / static_cast<float>(0x7FFFFFFF);
}

/*void Map::render(sf::RenderWindow& window)
{
    for(const auto& wall : walls)
    {
        window.draw(wall);
    }
    for(const auto& agusha : dots)
    {
        window.draw(agusha);
    }
    for(const auto& monster : potions)
    {
        window.draw(monster);
    }
    return;
}*/

bool Map::check_collision(const sf::FloatRect& borders) const
{
    int start_c = static_cast<int>(borders.left / tile_size);
    int end_c   = static_cast<int>((borders.left + borders.width) / tile_size);
    int start_r = static_cast<int>(borders.top / tile_size);
    int end_r   = static_cast<int>((borders.top + borders.height) / tile_size);

    for (int r = start_r; r <= end_r; ++r) {
        for (int c = start_c; c <= end_c; ++c) {
            if (is_wall(r, c)) return true;
        }
    }
    return false;
}

int Map::check_dot_collisions(const sf::FloatRect& stroller_bounds)
{
    int score = 0;
    for(size_t i = 0; i < dots.size();)
    {
        //collision pacman with dot
        if(stroller_bounds.intersects(dots[i].getGlobalBounds()))
        {
            score += 10;
            //swap with last el and del tail
            dots[i] = dots.back();
            dots.pop_back();
            //not i++ bc we swapped
        }
        else
        {
            i++;
        }
    }
    return score;
}

bool Map::check_potion_collisions(const sf::FloatRect& stroller_bounds)
{
    for (size_t i = 0; i < potions.size(); i++)
    {
        if (stroller_bounds.intersects(potions[i].getGlobalBounds()))
        {
            potions[i] = potions.back();
            potions.pop_back();
            return true;
        }
    }
    return false;
}

int Map::get_remaining_dots() const
{
    return dots.size();
}

int Map::get_remaining_potions() const
{
    return potions.size();
}