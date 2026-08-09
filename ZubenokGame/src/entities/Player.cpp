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

		updateSpriteFrame();

		sprite_.setOrigin(
			{
				frameWidth_ / 2.0f,
				frameHeight_ / 2.0f
			}
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
		sf::Vector2f movement{ 0.0f, 0.0f };

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			movement.y -= 1.0f;
			direction_ = Direction::Up;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			movement.y += 1.0f;
			direction_ = Direction::Down;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			movement.x -= 1.0f;
			direction_ = Direction::Left;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			movement.x += 1.0f;
			direction_ = Direction::Right;
		}

		const bool moving = movement.x != 0.0f || movement.y != 0.0f;

		if (moving) {
			const float lenght = std::sqrt(
				movement.x * movement.x + movement.y * movement.y
			);

			movement.x /= lenght;
			movement.y /= lenght;

			sprite_.move(
				movement * speed_ * deltaTime);
		}

		updateAnimation(deltaTime, moving);
	}

	void Player::updateAnimation(float deltaTime, bool moving)
	{
		if (!moving)
		{
			animationTimer_ = 0.0f;
			animationFrame_ = 1;

			updateSpriteFrame();

			return;
		}

		animationTimer_ -= animationFrameTime_;
		animationFrame_++;

		if (animationFrame_ >= framesPerDirection_)
		{
			animationFrame_ = 0;
		}

		updateSpriteFrame();
	}

	void Player::updateSpriteFrame()
	{
		int row = 0;
		int columnOffset = 0;

		switch (direction_)
		{
		case zubrenok::Player::Direction::Right:
			row = 0;
			columnOffset = 0;
			break;
		case zubrenok::Player::Direction::Left:
			row = 0;
			columnOffset = 3;
			break;
		case zubrenok::Player::Direction::Up:
			row = 1;
			columnOffset = 0;
			break;
		case zubrenok::Player::Direction::Down:
			row = 1;
			columnOffset = 3;
			break;		
		}

		const int column = columnOffset + animationFrame_;

		sprite_.setTextureRect(
			sf::IntRect(
				{
				column * frameWidth_,
				row * frameHeight_
				},
				{
				frameWidth_,
				frameHeight_
				}
			)
		);
	}

	void Player::draw(sf::RenderTarget& target) const
	{
		target.draw(sprite_);
	}
}
