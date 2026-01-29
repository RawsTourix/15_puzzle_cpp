// textures.h

#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics/Texture.hpp>

namespace textures {

    // Загрузка текстур
    void load_all();

    // Геттер карты текстур
    const sf::Texture& get(const std::string key);
}

#endif // TEXTURES_H