#include "textures.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <optional>

int main() {

    // Создание окна
    sf::RenderWindow window(sf::VideoMode({ 300u, 300u }), "15 puzzle");
    window.setVerticalSyncEnabled(true);

    // Загрузка текстур
    textures::load_all();

    // Объект игры
    Game game;

    // Главный цикл отображения
    while (window.isOpen()) {
        // Обработка событий
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Закрытие окна
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Изменение размера окна
            else if (event->is<sf::Event::Resized>()) {
                game.set_size(window);
            }
        }

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}