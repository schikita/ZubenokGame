#pragma once

#include "zubrenok/persistence/Database.h"

namespace zubrenok
{
	class Application
	{
	public:
		Application();

		int run();

	private:
		Database database_;
	};
}
