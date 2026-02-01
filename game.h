// game.h

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <array>
#include "logic.h"

// Состояние игры
enum class State {
    Shuffle,  // Перемешивание. Действия заблокированы. Таймер не запущен.
    Ready,    // Ожидание начала игры, когда уже всё перемешано. Таймер не запущен.
    Play,     // Игра. Таймер запущен.
    Move,     // Тайл перемещается. Действия на время анимации перемещения заблокированы. Таймер идёт.
    Pause,    // Пауза. Действия заблокированы. Таймер на паузе.
    Solved    // Пазл собран. Таймер остановлен. Следующее нажатие запустит перемешивание.
};

// Перемещаемый тайл
struct MovingTile {
    int value;                     // Значение тайла (0 - нет анимации)
    sf::Vector2i from_pos;  // Значение клетки, откуда начинается движение
    sf::Vector2i to_pos;    // Значение клетки, куда направлено движение
    float time;                    // Прошедшее время движения
    float duration;                // Продолжительность движения

    // Конструктор по умолчанию
    MovingTile();

    // Конструктор с параметрами
    MovingTile(int, sf::Vector2i, sf::Vector2i, float, float);

    // Деструктор
    ~MovingTile() = default;

    // Задание значений
    void start_moving(int, sf::Vector2i from_pos, sf::Vector2i to_pos, float, float);

    // Обнуление
    void stop_moving();
};

// Игра
class Game {
private:
    sf::Vector2f size;           // Размер игрового поля
    State state;                 // Состояние игры
    Puzzle puzzle;               // Состояние игрового поля
    std::array<Tile, 15> tiles;  // Состояние тайлов
    float timer;                 // Таймер игры
    bool timer_running;          // Флаг таймера

    float cell = 0.f;            // Вычисляемый размер клетки для тайла
    sf::Vector2f origin;         // Вычисляемый верхний левый угол игрового поля
    MovingTile moving_tile;      // Перемещаемый тайл

public:
    // Константы количества строк и столбцов
    static constexpr int ROWS = 4;
    static constexpr int COLUMNS = 4;

    // Константы скорости перемещения
    static constexpr float DURATION = 0.12f;
    static constexpr float SHUFFLE_DURATION = 0.02f;

    // Конструктор по умолчанию
    Game();

    // Конструктор с параметрами
    Game(State, Puzzle, std::array<Tile, 15>, float, bool);

    // Деструктор
    ~Game() = default;

    // Отрисовка тайлов
    void draw(sf::RenderTarget&) const;

    // Геттер размера игрового поля
    sf::Vector2f get_size() const;
    
    // Сеттер размера игрового поля
    void set_size(sf::RenderTarget&);

    // Задание тайлам нарезанных участков тайлмапа
    void set_tile_rects();

    // Получение вектора направления
    sf::Vector2i vector_direction(Direction);

    // Масштабирование тайлов
    void layout_tiles();

    // Выставление позиций тайлов
    void syncronize_tile_positions();

    // Обработка клика
    void handle_click(sf::Vector2f);

    // Обновление таймера
    void update(float);

};

#endif // GAME_H