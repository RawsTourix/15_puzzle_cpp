// game.h

#ifndef GAME_H
#define GAME_H

#include "logic.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

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
    float time;                    // Прошедшее время движения
    float duration;                // Продолжительность движения

    // Конструктор по умолчанию
    MovingTile();

    // Конструктор с параметрами
    MovingTile(int, float, float);

    // Деструктор
    ~MovingTile() = default;

    // Задание значений
    void start_moving(int, float, float);

    // Обнуление
    void stop_moving();
};

// Игра
class Game {
private:
    // Основные поля
    sf::Vector2f size;                  // Размер игрового поля
    State state;                        // Состояние игры
    Puzzle puzzle;                      // Состояние игрового поля
    std::array<Tile, 15> tiles;         // Состояние тайлов
    float timer;                        // Таймер игры
    bool timer_running;                 // Флаг таймера

    // Дополнительные поля
    float cell = 0.f;                   // Вычисляемый размер клетки для тайла
    sf::Vector2f origin;                // Вычисляемый верхний левый угол игрового поля
    MovingTile moving_tile;             // Перемещаемый тайл
    bool is_shuffle = false;            // Флаг перемешивания
    int shuffle_num = 0;                // Количество шагов перемешивания
    int prev_shuffle_value = 0;         // Значение предыдущего перемещённого тайла при перемешивании (чтобы следующий ход не отменял предыдущий)
    int total_sec = -1;                 // Время в секундах

public:
    // Название игры
    static constexpr const char* TITLE = "15 puzzle";

    // Константы количества строк и столбцов
    static constexpr int ROWS = 4;
    static constexpr int COLUMNS = 4;

    // Константы скорости перемещения
    static constexpr float DURATION = 0.12f;
    static constexpr float SHUFFLE_DURATION = 0.02f;

    // Константы рандома для перемешивания
    static constexpr sf::Vector2i SHUFFLE_NUM_RAND{ 30, 50 };

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

    // Обновление процессов, зависящих от времени
    void update(float);

    // Обновление названия окна
    void update_title(sf::RenderWindow&);

    // Форматирование времени
    std::string format_hhmmss(int);

};

#endif // GAME_H