#include "zubrenok/app/Application.h"

#include <exception>
#include <iostream>

int main()
{
	try
	{
		zubrenok::Application application;
		return application.run();
	}
	catch (const std::exception& exception)
	{
		std::cerr
			<< "Critical application error: "
			<< exception.what()
			<< '\n';

		return 1;
	}
}
