#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>
#include <memory>

namespace zubrenok
{
	class Database
	{
	public:
		explicit Database(const std::filesystem::path& path);

		void inicialize();

	private:
		SQLite::Database connection_;
	};
}
