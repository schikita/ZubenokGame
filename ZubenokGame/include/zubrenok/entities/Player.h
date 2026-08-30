#pragma once

#include "zubrenok/game/GameTypes.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace zubrenok
{
	class Level;

	class Player
	{
	public:
		Player();

		void load();
		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition() const;

		CollectibleType update(float deltaTime, Level& level);
		void draw(sf::RenderTarget& target) const;

	private:
		enum class Facing
		{
			Right,
			Left,
			Up,
			Down
		};

		void updateAnimation(float deltaTime, bool moving);
		void updateSpriteFrame();

		sf::Texture texture_;
		sf::Sprite sprite_;

		Facing facing_ = Facing::Down;

		int animationFrame_ = 1;

		float speed_ = 220.0f;
		float animationTimer_ = 0.0f;
		float animationFrameTime_ = 0.12f;

		static constexpr int frameWidth_ = 130;
		static constexpr int frameHeight_ = 95;
		static constexpr int framesPerDirection_ = 3;
		static constexpr float spriteScale_ = 0.4f;
		static constexpr float collisionRadius_ = 10.0f;
	};
}
