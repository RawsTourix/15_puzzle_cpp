#include "textures.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <exception>
#include <windows.h>

int main() {

    // Создание окна
    sf::RenderWindow window(sf::VideoMode({ 300u, 300u }), Game::TITLE);
    window.setVerticalSyncEnabled(true);

    // Загрузка текстур
    try {
        textures::load_all();
    }
    catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "15_puzzle - error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Объект игры
    Game game;

    try {
        game.set_size(window);             // Задание размера игрового поля
        game.set_tile_rects();             // Нарезка тайлмапа
        game.layout_tiles();               // Масштабирование тайлов
        game.syncronize_tile_positions();  // Выставление позиций тайлов
    }
    catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "15_puzzle - error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Создание таймера
    sf::Clock clock;
    float dt = 0.f;

    // Данные об изменении размера окна
    sf::Vector2u pending_resize{};
    bool has_resize = false;

    // Данные о нажатии кнопки мыши
    sf::Vector2i pending_mouse_button_press{};
    bool has_mouse_button_press = false;
    

    // Главный цикл отображения
    while (window.isOpen()) {

        // Обновление таймера
        dt = clock.restart().asSeconds();
        
        // Обработка событий
        while (auto event = window.pollEvent()) {
            // Закрытие окна
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Изменение размера окна
            if (const auto* e = event->getIf<sf::Event::Resized>()) {
                // Получение размера окна в пикселях
                pending_resize = e->size;
                has_resize = true;
            }
            // Нажатие кнопки мыши
            if (const auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
                // Получение координат клика в пикселях
                pending_mouse_button_press = e->position;
                has_mouse_button_press = true;
            }
            // Нажатие клавиши клавиатуры
            if (const auto* k = event->getIf<sf::Event::KeyPressed>())
            {
                // Клавиша Escape
                if (k->code == sf::Keyboard::Key::Escape)
                {
                    // Обработка паузы
                    game.handle_pause(window);
                }
            }
        }

        // Если было изменение размера окна
        if (has_resize) {
            const float w = static_cast<float>(pending_resize.x);
            const float h = static_cast<float>(pending_resize.y);

            window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { w, h })));

            game.set_size(window);
            game.layout_tiles();
            game.syncronize_tile_positions();

            has_resize = false;
        }

        // Если было нажатие кнопкой мыши
        if (has_mouse_button_press) {
            // Преобразование в координаты мира
            sf::Vector2f world = window.mapPixelToCoords(pending_mouse_button_press);

            // Обработка клика
            game.handle_click(window, world);

            has_mouse_button_press = false;
        }

        game.update(window, dt);

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}