// game.cpp

#include "game.h"
#include "textures.h"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <utility>

// Конструктор по умолчанию
Game::Game()
	: Game(
		State::Ready,
		Puzzle(),
		std::array<Tile, 15>{{
			Tile(1, sf::Sprite(textures::get("play_tilemap"))),
			Tile(2, sf::Sprite(textures::get("play_tilemap"))),
			Tile(3, sf::Sprite(textures::get("play_tilemap"))),
			Tile(4, sf::Sprite(textures::get("play_tilemap"))),
			Tile(5, sf::Sprite(textures::get("play_tilemap"))),
			Tile(6, sf::Sprite(textures::get("play_tilemap"))),
			Tile(7, sf::Sprite(textures::get("play_tilemap"))),
			Tile(8, sf::Sprite(textures::get("play_tilemap"))),
			Tile(9, sf::Sprite(textures::get("play_tilemap"))),
			Tile(10, sf::Sprite(textures::get("play_tilemap"))),
			Tile(11, sf::Sprite(textures::get("play_tilemap"))),
			Tile(12, sf::Sprite(textures::get("play_tilemap"))),
			Tile(13, sf::Sprite(textures::get("play_tilemap"))),
			Tile(14, sf::Sprite(textures::get("play_tilemap"))),
			Tile(15, sf::Sprite(textures::get("play_tilemap")))
		}},
		sf::Vector2f(0, 0),
		0.0f
	) {
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

// Задание тайлам нарезанных участков тайлмапа
void Game::set_tile_rects() {
	for (auto& tile : tiles) {
		const auto& atlas = textures::get("play_tilemap");
		tile.sprite.setTextureRect(textures::tile_rect(atlas, tile.value, COLUMNS, ROWS));
	}
}

// Масштабирование тайлов
void Game::layout_tiles() {
	const float cell = std::min(size.x / COLUMNS, size.y / ROWS);
	const sf::Vector2f origin = { (size.x - COLUMNS * cell) / 2, (size.y - ROWS * cell) / 2 };

	for (auto& tile : tiles) {
		sf::IntRect rect = tile.sprite.getTextureRect();
		float sx = cell / static_cast<float>(rect.size.x);
		float sy = cell / static_cast<float>(rect.size.y);

		tile.sprite.setScale({ sx, sy });
	}
}

// Расстановка тайлов в начальное состояние
void Game::syncronize_tile_positions() {
	const float cell = std::min(size.x / COLUMNS, size.y / ROWS);
	const sf::Vector2f origin = { (size.x - COLUMNS * cell) / 2, (size.y - ROWS * cell) / 2 };

	for (auto& tile : tiles) {
		int idx = tile.value - 1;
		int col = idx % COLUMNS;
		int row = idx / COLUMNS;
		const auto& r = tile.sprite.getTextureRect();

		tile.sprite.setPosition({ origin.x + col * cell, origin.y + row * cell });
	}
}