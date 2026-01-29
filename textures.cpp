#include "textures.h"
#include "assets.h"
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
        load("b1", assets::play_button_1);
        load("b2", assets::play_button_2);
        load("b3", assets::play_button_3);
        load("b4", assets::play_button_4);
        load("b5", assets::play_button_5);
        load("b6", assets::play_button_6);
        load("b7", assets::play_button_7);
        load("b8", assets::play_button_8);
        load("b9", assets::play_button_9);
        load("b10", assets::play_button_10);
        load("b11", assets::play_button_11);
        load("b12", assets::play_button_12);
        load("b13", assets::play_button_13);
        load("b14", assets::play_button_14);
        load("b15", assets::play_button_15);
        load("continue", assets::menu_button_continue);
        load("exit", assets::menu_button_exit);
        load("pause", assets::menu_button_pause);
        load("replay", assets::menu_button_replay);

    }

    // Геттер карты текстур
    const sf::Texture& get(const std::string key) {
        return loaded.at(key);
    }

}