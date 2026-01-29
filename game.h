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
    Victory   // Пазл собран. Таймер остановлен. Следующее нажатие запустит перемешивание.
};

// Игра
class Game {
private:
    sf::Vector2f size;           // Размер игрового поля
    State state;                 // Состояние игры
    Puzzle puzzle;               // Состояние игрового поля
    std::array<Tile, 15> tiles;  // Состояние тайлов
    sf::Vector2f origin_px;      // Левый верхний край
    float time_sec;              // Таймер игры


public:
    // Конструктор по умолчанию
    Game();

    // Конструктор с параметрами
    Game(State, Puzzle, std::array<Tile, 15>, sf::Vector2f, float);

    // Деструктор
    ~Game() = default;

    // Отрисовка тайлов
    void draw(sf::RenderTarget&) const;

    // Геттер размера игрового поля
    sf::Vector2f get_size() const;
    
    // Сеттер размера игрового поля
    void set_size(sf::RenderTarget&);

};

#endif // GAME_H