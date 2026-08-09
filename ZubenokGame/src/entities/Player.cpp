#include "zubrenok/entities/Player.h"

#include "zubrenok/game/GameTypes.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <cmath>
#include <stdexcept>

namespace zubrenok
{
	Player::Player()
		: sprite_(texture_)
	{
	}

	void Player::load()
	{
		sf::Image image;

		if (!image.loadFromFile("assets/textures/zubrenok.png"))
		{
			throw std::runtime_error(
				"Failed to load assets/textures/zubrenok.png"
			);
		}

		image.createMaskFromColor(sf::Color::White);

		if (!texture_.loadFromImage(image))
		{
			throw std::runtime_error(
				"Failed to create player texture"
			);
		}

		sprite_.setTextureRect(
			sf::IntRect(
				{ 407, 148 },
				{ 85, 97 }
			)
		);

		sprite_.setOrigin(
			{ 42.5f, 48.5f }
		);

		sprite_.setScale(
			{ 0.65f, 0.65f }
		);

		sprite_.setPosition(
			{
				config::windowWidth / 2.0f,
				config::windowHeight / 2.0f
			}
		);
	}


	void Player::update(float deltaTime)
	{
		sf::Vector2f direction{ 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			direction.y -= 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			direction.y += 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			direction.x -= 1.0f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			direction.x += 1.0f;
		}

		if (direction.x != 0.0f || direction.y != 0.0f)
		{
			const float length = std::sqrt(
				direction.x * direction.x + direction.y * direction.y
			);
			direction /= length;
			sprite_.move(direction * speed_ * deltaTime);
		}
	}

	void Player::draw(sf::RenderTarget& target) const
	{
		target.draw(sprite_);
	}
}
