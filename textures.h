// textures.h

#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics/Texture.hpp>
#include <array>
#include "logic.h"

namespace textures {

    // Загрузка текстур
    void load_all();

    // Геттер карты текстур
    const sf::Texture& get(const std::string& key);

    // Нарезка тайлмапа
    sf::IntRect tile_rect(const sf::Texture&, int, int, int);

}

#endif // TEXTURES_H