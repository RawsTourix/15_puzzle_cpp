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

    game.set_size(window);             // Задание размера игрового поля
    game.set_tile_rects();             // Нарезка тайлмапа
    game.layout_tiles();               // Масштабирование тайлов
    game.syncronize_tile_positions();  // Выставление исходных позиций тайлов

    // Главный цикл отображения
    while (window.isOpen()) {
        // Обработка событий
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Закрытие окна
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Изменение размера окна
            else if (const auto* e = event->getIf<sf::Event::Resized>()) {
                const float w = static_cast<float>(e->size.x);
                const float h = static_cast<float>(e->size.y);

                window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { w, h })));

                game.set_size(window);
                game.layout_tiles();
                game.syncronize_tile_positions();
            }
        }

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}