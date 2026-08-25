#pragma once

#include <SFML/System/Vector2.hpp>

namespace zubrenok
{
	namespace config
	{
		inline constexpr int tileSize = 32;
		inline constexpr int mapWidth = 40;
		inline constexpr int mapHeight = 28;
		inline constexpr int hudHeight = 88;

		inline constexpr int windowWidth =
			mapWidth * tileSize;

		inline constexpr int windowHeight =
			mapHeight * tileSize + hudHeight;

		inline constexpr float fixedTimeStep =
			1.0f / 120.0f;

		inline constexpr float playerSpeed = 138.0f;
		inline constexpr float enemySpeed = 112.0f;
		inline constexpr float frightenedEnemySpeed = 86.0f;
		inline constexpr float returningEnemySpeed = 190.0f;

		inline constexpr float powerModeDuration = 7.0f;
		inline constexpr float collisionDistance = 23.0f;

		inline constexpr int initialLives = 3;

		inline constexpr int berryScore = 10;
		inline constexpr int acornScore = 50;
		inline constexpr int enemyScore = 200;
		inline constexpr int victoryScore = 1000;
	}

	enum class Direction
	{
		None,
		Up,
		Down,
		Left,
		Right
	};

	enum class GameState
	{
		MainMenu,
		NameInput,
		Playing,
		Paused,
		Leaderboard,
		GameOver,
		Victory
	};

	enum class EnemyMode
	{
		Chase,
		Scatter,
		Frightened,
		Returning
	};

	enum class EnemyType
	{
		Wolf,
		Fox,
		Lynx,
		Boar
	};

	enum class CollectibleType
	{
		None,
		Berry,
		Acorn
	};

	struct TilePosition
	{
		int x = 0;
		int y = 0;

		bool operator==(const TilePosition& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const TilePosition& other) const
		{
			return !(*this == other);
		}
	};

	inline sf::Vector2f directionToVector(
		Direction direction
	)
	{
		switch (direction)
		{
		case Direction::Up:
			return { 0.0f, -1.0f };

		case Direction::Down:
			return { 0.0f, 1.0f };

		case Direction::Left:
			return { -1.0f, 0.0f };

		case Direction::Right:
			return { 1.0f, 0.0f };

		case Direction::None:
		default:
			return { 0.0f, 0.0f };
		}
	}

	inline TilePosition directionToOffset(
		Direction direction
	)
	{
		switch (direction)
		{
		case Direction::Up:
			return { 0, -1 };

		case Direction::Down:
			return { 0, 1 };

		case Direction::Left:
			return { -1, 0 };

		case Direction::Right:
			return { 1, 0 };

		case Direction::None:
		default:
			return { 0, 0 };
		}
	}

	inline Direction getOppositeDirection(
		Direction direction
	)
	{
		switch (direction)
		{
		case Direction::Up:
			return Direction::Down;

		case Direction::Down:
			return Direction::Up;

		case Direction::Left:
			return Direction::Right;

		case Direction::Right:
			return Direction::Left;

		case Direction::None:
		default:
			return Direction::None;
		}
	}

	inline float directionToAngle(
		Direction direction
	)
	{
		switch (direction)
		{
		case Direction::Right:
			return 0.0f;

		case Direction::Down:
			return 90.0f;

		case Direction::Left:
			return 180.0f;

		case Direction::Up:
			return 270.0f;

		case Direction::None:
		default:
			return 0.0f;
		}
	}
}