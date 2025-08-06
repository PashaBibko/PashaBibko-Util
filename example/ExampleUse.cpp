#include <iostream>

#include <Util.h>

using namespace PashaBibko;

int main()
{
	/* This is a simple example of using the Util library */
	Util::SetConsoleColor(Util::Color::LIGHT_AQUA);
	std::cout << "Hello, World!" << std::endl;
	Util::SetConsoleColor(Util::Color::DEFAULT);
	
	return 0;
}