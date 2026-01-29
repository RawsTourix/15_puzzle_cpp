// puzzle.cpp

#include "logic.h"
#include <cmath>
#include <utility>

// Конструктор по умолчанию
Puzzle::Puzzle()
	: pos()
{
	for (int i = 1; i < 16; ++i)
		pos[i] = { (i - 1) / 4, (i - 1) % 4 };

	pos[0] = { 3, 3 };
}

// Конструктор с параметрами
Puzzle::Puzzle(std::array<std::pair<int, int>, 16> pos)
	: pos(std::move(pos)) {
}

// Конструктор перемещения
Puzzle::Puzzle(Puzzle&& other) noexcept
	: pos(std::move(other.pos)) {
}

// Геттер поля
std::array<std::pair<int, int>, 16> Puzzle::get_pos() const {
	return pos;
}

// Проверка возможности перемещения тайла
bool Puzzle::can_move(int n) const {
	if (n > 0 && n < 16)
		return (std::abs(pos[n].first - pos[0].first) + abs(pos[n].second - pos[0].second) == 1);
	return false;
}

// Перемещение
void Puzzle::move(int n) {
	swap(pos[n], pos[0]);
}