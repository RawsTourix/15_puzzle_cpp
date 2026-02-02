// puzzle.cpp

#include "logic.h"
#include <cmath>
#include <utility>

// Константа собранного состояния
const std::array<sf::Vector2i, 16> Puzzle::SOLVED_POS = Puzzle::get_solved();

// Конструктор по умолчанию
Puzzle::Puzzle()
	: pos(SOLVED_POS) {
}

// Конструктор с параметрами
Puzzle::Puzzle(std::array<sf::Vector2i, 16> pos)
	: pos(std::move(pos)) {
}

// Конструктор перемещения
Puzzle::Puzzle(Puzzle&& other) noexcept
	: pos(std::move(other.pos)) {
}

// Геттер поля
std::array<sf::Vector2i, 16> Puzzle::get_pos() const {
	return pos;
}

// Проверка возможности перемещения тайла
bool Puzzle::can_move(int n) const {
	if (n > 0 && n < 16)
		return (std::abs(pos[n].x - pos[0].x) + abs(pos[n].y - pos[0].y) == 1);
	return false;
}

// Получение направления перемещения
Direction Puzzle::get_direction(int n) const {
	int dx = pos[n].x - pos[0].x;
	int dy = pos[n].y - pos[0].y;

	// Если перемещение по горизонтали
	if (dx == 0) {
		// Если движение влево
		if (dy > 0) return Direction::Left;
		// Если движение вправо
		else if (dy < 0) return Direction::Right;
	}
	// Если перемещение по вертикали
	else if (dy == 0) {
		// Если движение вверх
		if (dx > 0) return Direction::Up;
		// Если движение вниз
		else if (dx < 0) return Direction::Down;
	}
	// Если нет перемещения
	return Direction::None;
}

// Перемещение
void Puzzle::move(int n) {
	if (n > 0 && n < 16)
		std::swap(pos[n], pos[0]);
}

// Возврат решённого состояния
std::array<sf::Vector2i, 16> Puzzle::get_solved() {
	std::array<sf::Vector2i, 16> a{};
	for (int i = 1; i < 16; ++i)
		a[i] = { (i - 1) / 4, (i - 1) % 4 };

	a[0] = { 3, 3 };
	return a;
}

// Проверка решения головоломки
bool Puzzle::is_solved() const {
	return pos == SOLVED_POS;
}