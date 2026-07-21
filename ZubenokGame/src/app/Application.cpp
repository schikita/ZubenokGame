#include "zubrenok/app/Application.h"

#include <filesystem>
#include <iostream>

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
		std::cout << "ZubrenokGame init successfully.\n";
		std::cout << "Database init successfully.\n";

		return 0;
	}
}
