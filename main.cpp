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
    game.syncronize_tile_positions();  // Выставление позиций тайлов

    // Создание таймера
    sf::Clock clock;
    float dt = 0.f;

    // Главный цикл отображения
    while (window.isOpen()) {

        // Обновление таймера
        dt = clock.restart().asSeconds();
        
        // Обработка событий
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Закрытие окна
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Изменение размера окна
            if (const auto* e = event->getIf<sf::Event::Resized>()) {
                const float w = static_cast<float>(e->size.x);
                const float h = static_cast<float>(e->size.y);

                window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { w, h })));

                game.set_size(window);
                game.layout_tiles();
                game.syncronize_tile_positions();
            }
            // Нажатие кнопки мыши
            if (const auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
                // Получение координат клика в пикселях и преобразование в координаты View
                sf::Vector2i pixel{ e->position.x, e->position.y };
                sf::Vector2f world = window.mapPixelToCoords(pixel);
                
                // Обработка клика
                game.handle_click(world);
            }
        }

        game.update(dt);

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}