#include "zubrenok/app/Application.h"

#include "zubrenok/entities/Player.h"
#include "zubrenok/game/GameTypes.h"
#include "zubrenok/levels/Level.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <filesystem>

namespace zubrenok
{
	namespace
	{
		std::filesystem::path getDatabasePath()
		{
			return std::filesystem::path("data") / "zubrenok.db";
		}
	}

	Application::Application()
		: database_(getDatabasePath())
	{
		database_.inicialize();
	}

	int Application::run()
	{
		sf::RenderWindow window(
			sf::VideoMode(
				{
					static_cast<unsigned int>(
						config::windowWidth
					),
					static_cast<unsigned int>(
						config::windowHeight
					)
				}
			),
			"Zubrenok"
		);

		window.setFramerateLimit(144);

		Level level;

		Player player;
		player.load();
		player.setPosition(
			level.tileToWorld(level.getPlayerSpawn())
		);

		sf::Clock clock;
		float animationTime = 0.0f;

		while (window.isOpen())
		{
			while (const auto event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}
			}

			const float deltaTime =
				clock.restart().asSeconds();

			animationTime += deltaTime;
			player.update(deltaTime, level);

			window.clear(
				sf::Color(
					14,
					22,
					17
				)
			);

			level.draw(
				window,
				animationTime
			);

			player.draw(window);

			window.display();
		}

		return 0;
	}
}
