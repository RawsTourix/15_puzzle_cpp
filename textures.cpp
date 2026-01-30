#include "textures.h"
#include "assets.h"
#include <SFML/Graphics/Rect.hpp>
#include <unordered_map>
#include <stdexcept>

namespace {
    std::unordered_map<std::string, sf::Texture> loaded;
}

namespace textures {

    // Загрузка текстур
    void load_all() {

        // Вспомогательная функция для загрузки
        auto load = [](const char* key, const char* path) {
            sf::Texture t;
            if (!t.loadFromFile(std::string(path)))
                throw std::runtime_error(std::string("Failed to load: ") + std::string(path));
            t.setSmooth(false);
            loaded.emplace(key, std::move(t));
        };

        // Загрузка текстур
        load("play_tilemap", assets::play_tilemap);
        load("continue", assets::menu_button_continue);
        load("exit", assets::menu_button_exit);
        load("pause", assets::menu_button_pause);
        load("replay", assets::menu_button_replay);

    }

    // Геттер карты текстур
    const sf::Texture& get(const std::string& key) {
        return loaded.at(key);
    }

    // Нарезка тайлмапа
    sf::IntRect tile_rect(const sf::Texture& atlas, int value, int cols, int rows)
    {
        // Значение: 1..(cols*rows) или 1..15
        const auto s = atlas.getSize();
        const int atlas_w = static_cast<int>(s.x);
        const int atlas_h = static_cast<int>(s.y);

        // Защита от кривого атласа
        if (cols <= 0 || rows <= 0) throw std::runtime_error("Bad grid");
        if (atlas_w % cols != 0 || atlas_h % rows != 0) throw std::runtime_error("Atlas size not divisible by grid");
        if (value < 1 || value > cols * rows) throw std::runtime_error("Bad tile value");

        const int tile_w = atlas_w / cols;
        const int tile_h = atlas_h / rows;

        const int idx = value - 1;
        const int col = idx % cols;
        const int row = idx / cols;

        return sf::IntRect({ col * tile_w, row * tile_h }, { tile_w, tile_h });
    }

}