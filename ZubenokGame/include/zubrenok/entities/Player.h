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
		sf::Texture texture_;
		sf::Sprite sprite_;

		float speed_ = 220.0f;
	};
}