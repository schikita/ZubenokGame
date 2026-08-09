#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace zubrenok
{
	class Player
	{
	public:
		Player();

		void load();
		void update(float deltaTime);
		void draw(sf::RenderTarget& target) const;

	private:
		enum class Direction
		{
			Right,
			Left,
			Up,
			Down
		};

		void updateAnimation(float deltatime, bool moving);
		void updateSpriteFrame();

		sf::Texture texture_;
		sf::Sprite sprite_;

		Direction direction_ = Direction::Down;

		int animationFrame_ = 1;

		float speed_ = 220.0f;
		float animationTimer_ = 0.0f;
		float animationFrameTime_ = 0.12f;

		static constexpr int frameWidth_ = 130;
		static constexpr int frameHeight_ = 95;
		static constexpr int framesPerDirection_ = 3;
	};
}