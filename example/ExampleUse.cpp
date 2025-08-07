#include <iostream>

#include <Util.h>

using namespace PashaBibko;

static Util::ReturnVal<int> SafeDivide(int x, int y)
{
	if (y == 0)
		return Util::FunctionFail<>("");

	return x / y;
}

int main()
{
	/* This is a simple example of using coloured text with the Util library */
	Util::SetConsoleColor(Util::Color::LIGHT_AQUA);
	std::cout << "Hello, World!" << std::endl;
	Util::SetConsoleColor(Util::Color::DEFAULT);

	/* Example of using the Util::ReturnVal class for functions that can fail */
	Util::ReturnVal res = SafeDivide(3, 0);
	std::cout << res.Result<Util::Result::Check>() << std::endl;

	return 0;
}