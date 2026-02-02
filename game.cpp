// game.cpp

#include "game.h"
#include "textures.h"
#include "random.h"
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <utility>
#include <algorithm>
#include <iostream>

// Конструктор по умолчанию
MovingTile::MovingTile()
	: MovingTile(0, 0.f, Game::DURATION) {
}

// Конструктор с параметрами
MovingTile::MovingTile(int value, float time, float duration)
	: value(value),
	time(time),
	duration(duration) {
}

// Задание значений
void MovingTile::start_moving(int value, float time, float duration) {
	*this = { value, time, duration };
}

// Обнуление
void MovingTile::stop_moving() {
	*this = {};
}

// Конструктор по умолчанию
Game::Game()
	: Game(
		State::Solved,
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
		0.f,
		false
	) {
}

// Конструктор с параметрами
Game::Game(State state, Puzzle puzzle, std::array<Tile, 15> tiles, float timer, bool timer_running)
	: state(state),
	puzzle(puzzle),
	tiles(tiles),
	timer(timer),
	timer_running(timer_running) {
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

// Получение вектора направления
sf::Vector2i Game::vector_direction(Direction dir) {
	if (dir == Direction::Up) return sf::Vector2i{ -1, 0 };
	else if (dir == Direction::Down) return sf::Vector2i{ 1, 0 };
	else if (dir == Direction::Left) return sf::Vector2i{ 0, -1 };
	else if (dir == Direction::Right) return sf::Vector2i{ 0, 1 };
	else return sf::Vector2i{};
}

// Масштабирование тайлов
void Game::layout_tiles() {
	// Расчёт размера клетки и левого верхнего угла
	cell = std::min(size.x / COLUMNS, size.y / ROWS);
	origin = { (size.x - COLUMNS * cell) / 2, (size.y - ROWS * cell) / 2 };

	// Подгонка тайлов по размеру
	for (auto& tile : tiles) {
		sf::IntRect rect = tile.sprite.getTextureRect();
		float sx = cell / static_cast<float>(rect.size.x);
		float sy = cell / static_cast<float>(rect.size.y);

		tile.sprite.setScale({ sx, sy });
	}
}

// Выставление позиций тайлов
void Game::syncronize_tile_positions() {
	const auto& pos = puzzle.get_pos();
	for (auto& tile : tiles) {
		// Если текущий тайл не перемещается
		if (tile.value != moving_tile.value) {
			int value = tile.value;

			// Получение логических позиций
			sf::Vector2i rc = pos.at(value);

			// Преобразование в позиции x и y
			sf::Vector2f xy{ float(rc.y), float(rc.x) };

			tile.sprite.setPosition(origin + xy * cell);
		}
	}
}

// Обработка клика
void Game::handle_click(sf::Vector2f pos) {

	// Не перемещение,не перемешивание, и не пауза
	if (state != State::Move && state != State::Shuffle && state != State::Pause) {

		// Проверка попадания клика на тайл
		auto it = std::find_if(tiles.begin(), tiles.end(), [pos](const Tile& tile) {
			return tile.sprite.getGlobalBounds().contains(pos);
		});

		// Если попал
		if (it != tiles.end()) {
			Tile& tile = *it;
			int value = tile.value;
			std::cout << "Tile value: " << value << std::endl;

			// Если пазл собран
			if (state == State::Solved) {
				// Сброс таймера
				timer = 0.f;

				// Задаём рандомное число перемещений для перемешивания
				shuffle_num = rand_int(SHUFFLE_NUM_RAND.x, SHUFFLE_NUM_RAND.y);

				// Перемешивание
				is_shuffle = true;
				state = State::Shuffle;
				std::cout << "Shuffle." << std::endl;
			}

			// Если готов
			else if (state == State::Ready) {
				//Запуск таймера
				timer_running = true;

				// Игра
				state = State::Play;
				std::cout << "Play!" << std::endl;
			}

			// Если игра идёт
			if (state == State::Play) {
				// Получение направления перемещения
				Direction dir = puzzle.get_direction(value);

				// Если тайл можно переместить
				if (puzzle.can_move(value) && dir != Direction::None) {
					// Запуск перемещения
					moving_tile.start_moving(value, 0, DURATION);
					
					// Перемещение
					state = State::Move;
					std::cout << "Move tile." << std::endl;
				}
			}
		}
		else {
			std::cout << "Empty tile" << std::endl;
		}
	}

}

// Обновление процессов, связанных с временем
void Game::update(float dt) {
	// Обновление игрового таймера
	if (timer_running) timer += dt;

	// Обновление анимации
	if (moving_tile.value != 0) {
		// Вычисление временичx
		moving_tile.time += dt;
		float t = std::clamp(moving_tile.time / moving_tile.duration, 0.f, 1.f);
		t = t * t * (3 - 2 * t); // (smoothstep)

		// Получение итератора на тайл по значению
		int value = moving_tile.value;
		auto it = std::find_if(tiles.begin(), tiles.end(), [value](const Tile& tile) {
			return value == tile.value;
		});
		
		// Если итератор указывает не на конец
		if (it != tiles.end()) {
			// Получение ссылки на спрайт
			sf::Sprite& sprite = it->sprite;

			// Получение константной ссылки логических позиций
			const auto& pos = puzzle.get_pos();

			// Получение конечной и начальной логических позиций
			sf::Vector2i to_pos_rc = pos.at(0);
			sf::Vector2i from_pos_rc = pos.at(value);

			// Преобразование в позиции x и y
			sf::Vector2f to_pos_xy = { float(to_pos_rc.y), float(to_pos_rc.x) };
			sf::Vector2f from_pos_xy = { float(from_pos_rc.y), float(from_pos_rc.x) };

			// Вычисление конечной позиции
			sf::Vector2f target_px = origin + to_pos_xy * cell;

			// Если анимация ещё идёт
			if (t < 1) {

				// Вычисление начальной позиции
				sf::Vector2f start_px = origin + from_pos_xy * cell;

				// Вычисление текущей позиции перемещения
				sf::Vector2f p = start_px + (target_px - start_px) * t;

				sprite.setPosition(p);
			}
			// Если анимация закончилась
			else {
				// Установка конечной позиции
				sprite.setPosition(target_px);

				// Логическое перемещение тайла
				puzzle.move(moving_tile.value);

				// Остановка перемещаемого тайла
				moving_tile.stop_moving();
				
				// Если пазл перемешивается
				if (is_shuffle) {
					state = State::Shuffle;
				}
				else {
					// Если головоломка собрана
					if (puzzle.is_solved()) {
						// Выключение таймера
						timer_running = false;

						// Собрана
						state = State::Solved;

						/* поздравление */
						std::cout << "Solved!!!" << std::endl;
					}
					else {
						// Игра
						state = State::Play;
						std::cout << "Continue playing..." << std::endl;
					}
				}
			}
		}
	}
	// Перемешивание
	if (state == State::Shuffle) {
		// Получение значений, которые можно переместить
		std::vector<int> values;
		for (int v = 0; v < ROWS * COLUMNS; ++v) {
			if (puzzle.can_move(v) && v != prev_shuffle_value) values.push_back(v);
		}

		// Если есть тайлы для перемещения (ну мало ли их может не быть, хз)
		if (values.size() > 0) {
			// Выбор тайла для перемещения
			int n = rand_int(0, static_cast<int>(values.size()) - 1);
			int value = values.at(n);

			// Запуск перемещения
			moving_tile.start_moving(value, 0, SHUFFLE_DURATION);
			prev_shuffle_value = value;
			--shuffle_num;

			// Перемещение
			state = State::Move;
			std::cout << "Move tile." << std::endl;
		}
		// Если нет тайлов для перемещения
		else {
			shuffle_num = 0;
			std::cout << "Shuffle Error: no tiles to move." << std::endl;
		}

		// Если перемешано
		if (shuffle_num <= 0) {
			// Готовность
			is_shuffle = false;
			state = State::Ready;
			std::cout << "Ready!" << std::endl;
		}
	}
}