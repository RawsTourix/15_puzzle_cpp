// logic.h

#ifndef LOGIC_H
#define LOGIC_H

#include <SFML/Graphics/Sprite.hpp>
#include "textures.h"
#include <array>

// Тайл
struct Tile {
	int value;               // номер тайла (0—15)
	sf::Sprite sprite;       // спрайт тайла
	sf::Vector2f current_px; // текущая позиция (px)
	sf::Vector2f start_px;   // старт анимации (px)
	sf::Vector2f target_px;  // цель анимации (px)
	float elapsed;           // прошло времени (s)
	float duration;          // длительность (s)
	bool moving;             // флаг перемещения

	// Конструктор по умолчанию
	Tile() = delete;

	// Конструктор преобразования малый
	Tile(int, sf::Sprite);

	// Конструктор преобразования средний
	Tile(int, sf::Sprite, sf::Vector2f);

	// Конструктор преобразования большой
	Tile(int, sf::Sprite, sf::Vector2f, sf::Vector2f, sf::Vector2f);

	// Конструктор с параметрами
	Tile(int, sf::Sprite, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, float, bool);

	// Конструктор копирования
	Tile(const Tile&) = default;
	Tile& operator=(const Tile&) = default;

	// Конструктор перемещения
	Tile(Tile&& other) noexcept;
	Tile& operator=(Tile&&) noexcept = default;

	// Деструктор
	~Tile() = default;
};

// Игровое поле
class Puzzle {
private:
	std::array<std::pair<int, int>, 16> pos;

public:
	// Конструктор по умолчанию
	Puzzle();

	// Конструктор с параметрами
	Puzzle(std::array<std::pair<int, int>, 16>);

	// Конструктор копирования
	Puzzle(const Puzzle&) = default;
	Puzzle& operator=(const Puzzle&) = default;

	// Конструктор перемещения
	Puzzle(Puzzle&& other) noexcept;
	Puzzle& operator=(Puzzle&&) noexcept = default;

	// Деструктор
	~Puzzle() = default;

	// Геттер поля
	std::array<std::pair<int, int>, 16> get_pos() const;

	// Проверка возможности перемещения тайла
	bool can_move(int) const;

	// Перемещение
	void move(int);

};

#endif // LOGIC_H