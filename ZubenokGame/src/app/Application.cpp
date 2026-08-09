#include "zubrenok/app/Application.h"

#include "zubrenok/entities/Player.h"
#include "zubrenok/game/GameTypes.h"

#include <SFML/Graphics/Color.hpp>
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
					static_cast<unsigned int>(config::windowWidth),
					static_cast<unsigned int>(config::windowHeight)
				}
			),
			"Zubrenok Game"
		);

		window.setFramerateLimit(144);

		Player player;
		player.load();

		sf::Clock clock;

		while (window.isOpen())
		{
			while (const auto event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}
			}

			const float deltaTime = clock.restart().asSeconds();

			player.update(deltaTime);

			window.clear(
				sf::Color(30, 45, 34)
			);

			player.draw(window);

			window.display();
		}

		return 0;
	}
}
