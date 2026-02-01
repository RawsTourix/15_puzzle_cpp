#include "logic.h"
#include <utility>

//// Конструктор преобразования малый
//Tile::Tile(int value, sf::Sprite sprite)
//	: Tile(value, sprite, sprite.getPosition()) {
//}
//
//// Конструктор преобразования средний
//Tile::Tile(int value, sf::Sprite sprite, sf::Vector2f current_px)
//	: Tile(value, sprite, current_px, sf::Vector2f{ 0, 0 }, sf::Vector2f{ 0, 0 }) {
//}
//
//// Конструктор преобразования большой
//Tile::Tile(int value, sf::Sprite sprite, sf::Vector2f current_px, sf::Vector2f start_px, sf::Vector2f target_px)
//	: Tile(value, sprite, current_px, start_px, target_px, 0.0f, 0.0f, false) {
//}

// Конструктор с параметрами
Tile::Tile(int value, sf::Sprite sprite) //sf::Vector2f current_px, sf::Vector2f start_px, sf::Vector2f target_px, float elapsed, float duration, bool moving
	: value(value),
	sprite(sprite)
	//current_px(current_px),
	//start_px(start_px),
	//target_px(target_px),
	//elapsed(elapsed),
	//duration(duration),
	//moving(moving) {
{
}

// Конструктор перемещения
Tile::Tile(Tile&& other) noexcept
	: value(std::exchange(other.value, 0)),
	sprite(std::move(other.sprite))
	//current_px(std::move(other.current_px)),
	//start_px(std::move(other.start_px)),
	//target_px(std::move(other.target_px)),
	//elapsed(std::exchange(other.elapsed, 0.0f)),
	//duration(std::exchange(other.duration, 0.0f)),
	//moving(other.moving) {
{
}