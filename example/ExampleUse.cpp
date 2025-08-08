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
	Util::PrintAs<Util::Colour::LightAqua>("Hello, World!\n");
	Util::Print("This is on the same line");
	Util::PrintLn(" as this");
	Util::Log("This is put in the console and log");

	/* Example of using the Util::ReturnVal class for functions that can fail */
	Util::ReturnVal res = SafeDivide(6, 2);
	std::cout << res.Result<Util::Result::Check>() << std::endl;

	return 0;
}