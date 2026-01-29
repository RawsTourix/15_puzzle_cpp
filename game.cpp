// game.cpp

#include "game.h"
#include "textures.h"
#include <SFML/Graphics/Sprite.hpp>
#include <array>

// Конструктор по умолчанию
Game::Game()
	: Game(
		State::Ready,
		Puzzle(),
		std::array<Tile, 15>{{
			Tile(1, sf::Sprite(textures::get("b1"))),
			Tile(2, sf::Sprite(textures::get("b2"))),
			Tile(3, sf::Sprite(textures::get("b3"))),
			Tile(4, sf::Sprite(textures::get("b4"))),
			Tile(5, sf::Sprite(textures::get("b5"))),
			Tile(6, sf::Sprite(textures::get("b6"))),
			Tile(7, sf::Sprite(textures::get("b7"))),
			Tile(8, sf::Sprite(textures::get("b8"))),
			Tile(9, sf::Sprite(textures::get("b9"))),
			Tile(10, sf::Sprite(textures::get("b10"))),
			Tile(11, sf::Sprite(textures::get("b11"))),
			Tile(12, sf::Sprite(textures::get("b12"))),
			Tile(13, sf::Sprite(textures::get("b13"))),
			Tile(14, sf::Sprite(textures::get("b14"))),
			Tile(15, sf::Sprite(textures::get("b15")))
		}},
		sf::Vector2f(0, 0),
		0.0f
	) {
	int offset_x = 0;
	int offset_y = 0;
	for (auto& tile : tiles) {
		offset_x = (tile.value - 1) % 4;
		offset_y = (tile.value - 1) / 4;
		tile.sprite.setPosition(
			sf::Vector2f(
				offset_x * tile.sprite.getTextureRect().size.x,
				offset_y * tile.sprite.getTextureRect().size.y
			)
		);
	}
}

// Конструктор с параметрами
Game::Game(State state, Puzzle puzzle, std::array<Tile, 15> tiles, sf::Vector2f origin_px, float time_sec)
	: state(state),
	puzzle(puzzle),
	tiles(tiles),
	origin_px(origin_px),
	time_sec(time_sec) {
}

// Отрисовка тайлов
void Game::draw(sf::RenderTarget& target) const {
	for (auto& tile : tiles) target.draw(tile.sprite);
}

// Геттер размера игрового поля
sf::Vector2f Game::get_size() const {
	return size;
}

// Сеттер размера игрового поля
void Game::set_size(sf::RenderTarget& target) {
	size = target.getView().getSize();
}