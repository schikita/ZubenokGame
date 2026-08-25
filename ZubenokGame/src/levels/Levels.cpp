#include "zubrenok/levels/Level.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>

namespace zubrenok
{
	namespace
	{
		constexpr char wallTile = '#';
		constexpr char berryTile = '.';
		constexpr char acornTile = 'o';
		constexpr char playerSpawnTile = 'P';
		constexpr char enemySpawnTile = 'E';
		constexpr char emptyTile = ' ';

		constexpr float wallPadding = 2.0f;
	}

	Level::Level()
	{
		reset();
	}

	void Level::reset() {
		loadDefaultMap();
		parseMapObjects();
	}

	void Level::loadDefaultMap() {
		tiles_.assign(
			config::mapHeight,
			std::string(
				config::mapWidth,
				berryTile
			)
		);

		for (int x = 0; x < config::mapWidth; ++x)
		{
			tiles_[0][x] = wallTile;
			tiles_[config::mapHeight - 1][x] = wallTile;
		}

		for (int y = 0; y < config::mapHeight; ++y)
		{
			tiles_[y][0] = wallTile;
			tiles_[y][config::mapWidth - 1] = wallTile;
		}

		auto addHorizontWall = [this](
			int startX,
			int y,
			int lenght
			)
			{
				for (int x = startX; x < startX + lenght; x++)
				{
					if (x <= 0 || x >= config::mapWidth - 1 || y <= 0 || y >= config::mapHeight - 1)
					{
						continue;
					}

					tiles_[y][x] = wallTile;
				}
			};

		auto addVerticalWall = [this](
			int x,
			int startY,
			int length
			)
			{
				for (int y = startY; y < startY + length; ++y)
				{
					if (x <= 0 || x >= config::mapWidth - 1 || y <= 0 || y >= config::mapHeight - 1)
					{
						continue;
					}

					tiles_[y][x] = wallTile;
				}
			};

		addHorizontWall(3, 3, 8);
		addHorizontWall(14, 3, 12);
		addHorizontWall(29, 3, 8);

		addHorizontWall(5, 7, 11);
		addHorizontWall(24, 7, 11);

		addHorizontWall(3, 11, 9);
		addHorizontWall(15, 11, 10);
		addHorizontWall(28, 11, 9);
		/*...*/
		
		tiles_[2][2]= acornTile;
		tiles_[2][config::mapWidth - 3] = acornTile;
		/*...*/

		tiles_[20][20] = playerSpawnTile;

		tiles_[13][18] = enemySpawnTile;
		tiles_[13][19] = enemySpawnTile;
		tiles_[13][20] = enemySpawnTile;
		tiles_[13][21] = enemySpawnTile;
	}

	void Level::parseMapObjects()
	{
		playerSpawn_ = {1,1};
		enemySpawns_.clear();

		remainingCollectibles_ = 0;

		for (int y = 0; y < config::mapHeight; ++y)
		{
			for (int x = 0; x < config::mapWidth; ++x)
			{
				char& tile = tiles_[y][x];

				switch (tile)
				{
				case playerSpawnTile:
					playerSpawn_ = { x, y };
					tile = emptyTile;
					break;

				case enemySpawnTile:
					enemySpawns_.push_back(
						{ x, y }
					);

					tile = emptyTile;
					break;

				case berryTile:
					++remainingCollectibles_;
					break;

				case acornTile:
					++remainingCollectibles_;
					break;


				default:
					break;
				}
			}
		}
	}


	bool Level::isInside(
		TilePosition position
	) const
	{
		return
			position.x >= 0 &&
			position.y >= 0 &&
			position.x < config::mapWidth &&
			position.y < config::mapHeight;
	}

	bool Level::isWalkable(
		TilePosition position
	) const
	{
		if (!isInside(position))
		{
			return false;
		}

		return tiles_[position.y][position.x] != wallTile;
	}

	bool Level::canMove(
		TilePosition position,
		Direction direction
	) const
	{
		if (direction == Direction::None)
		{
			return false;
		}

		const TilePosition offset = directionToOffset(direction);

		const TilePosition target{
			position.x + offset.x,
			position.y + offset.y
		};

		return isWalkable(target);
	}

	bool Level::isNearTileCenter(
		sf::Vector2f worldPosition,
		float tolerance
	) const
	{
		const TilePosition tile = worldToTile(worldPosition);

		if (!isInside(tile))
		{
			return false;
		}

		const sf::Vector2f center = tileToWorld(tile);

		return std::abs(worldPosition.x - center.x) <= tolerance &&
			std::abs(worldPosition.y - center.y) <= tolerance;
	}

	TilePosition Level::worldToTile(
		sf::Vector2f worldPosition
	) const
	{
		const float mapX = worldPosition.x;

		const float mapY = worldPosition.y - static_cast<float>(config::hudHeight);

		return {
			static_cast<int>(
					std::floor(
						mapX / static_cast<float>(config::tileSize)
					)
				),
			static_cast<int>(
					std::floor(
						mapY / static_cast<float>(config::tileSize)
					)
				)
		};
	}

	sf::Vector2f Level::tileToWorld(
		TilePosition tilePosition
	) const
	{
		const float halfTile = static_cast<float>(config::tileSize) / 2.0f;

		return {
			static_cast<float>(
					tilePosition.x * config::tileSize
				) + halfTile,

			static_cast<float>(
				config::hudHeight + 
					tilePosition.y * config::tileSize
				) + halfTile
		};
	}

	CollectibleType Level::consumeCollectible(
		sf::Vector2f worldPosition
	)
	{
		const TilePosition tilePostion = worldToTile(worldPosition);

		if (!isInside(tilePostion))
		{
			return CollectibleType::None;
		}

		if (!isNearTileCenter(worldPosition, config::tileSize * 0.35f))
		{
			return CollectibleType::None;
		}

		char& tile = tiles_[tilePostion.y][tilePostion.x];

		if (tile == berryTile)
		{
			tile = emptyTile;

			remainingCollectibles_ = std::max(0, remainingCollectibles_ - 1);

			return CollectibleType::Berry;
		}

		if (tile == acornTile)
		{
			tile = emptyTile;

			remainingCollectibles_ = std::max(0, remainingCollectibles_ - 1);

			return CollectibleType::Acorn;
		}

		return CollectibleType::None;
	}

	int Level::getRemainingCollectibles() const
	{
		return remainingCollectibles_;
	}

	TilePosition Level::getPlayerSpawn() const {
		return playerSpawn_;
	}

	const std::vector<TilePosition>&
		Level::getEnemySpawns() const
	{
		return enemySpawns_;
	}
	/*.....25.08.2026*/
}
