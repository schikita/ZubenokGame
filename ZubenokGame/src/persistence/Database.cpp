#include "zubrenok/persistence/Database.h"

namespace
{
	std::filesystem::path prepareDatabasePath(
		const std::filesystem::path& path
	) {
		
		const std::filesystem::path  directory = path.parent_path();

		if (!directory.empty()) {
			std::filesystem::create_directories(directory);
		}

		return path;
	}
}

namespace zubrenok
{
	Database::Database(const std::filesystem::path& path)
		: connection_(
			prepareDatabasePath(path),
			SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE,
			3000
		)
	{
	}

	void Database::initialize()
	{
		connection_.exec("PRAGMA foreign_keys = ON;");
		connection_.exec("PRAGMA journal_mode = WAL");
		connection_.exec("PRAGMA synchronous = NORMAL");

		connection_.exec(
			R"sql(
				CREATE TABLE IF NOT EXISTS settings
					(
						key TEXT PRIMARY KEY,
						value TEXT NOT NULL
					);

				CREATE TABLE IF NOT EXISTS save_games
					(
						id INTEGER PRIMARY KEY AUTOINCREMENT,
						profile_name TEXT NOT NULL,
						level INTEGER NOT NULL DEFAULT 1
							CHECK(level > 0),
						score INTEGER NOT NULL DEFAULT 0
							CHECK(score >= 0),
						lives INTEGER NOT NULL DEFAULT 3
							CHECK(lives >= 0),
						updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
					);

				CREATE TABLE IF NOT EXISTS high_scores
				(
					id INTEGER PRIMARY KEY AUTOINCREMENT,
					player_name TEXT NOT NULL,
					score INTEGER NOT NULL
						CHECK(score >= 0),
					level INTEGER NOT NULL
						CHECK(level > 0),
					created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
				);

				CREATE INDEX IF NOT EXISTS
					idx_high_scores_score
				ON high_scores(score DESC);

				CREATE INDEX IF NOT EXISTS
					idx_save_games_updated_at 
				ON save_games(updated_at DESC);
			)sql"
		);
	}
}

