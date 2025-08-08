#include <iostream>
#include <array>

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

	/* Example of auto de-referencing pointers */
	int temp = 3;
	int* ptr = &temp;
	Util::PrintLn(ptr);

	/* Example of using an iterator with the log */
	std::array<int, 5> array = { 1, 2, 3, 4, 5 };
	Util::LogContainer("Example-Array", array);

	/* Example of using the Util::ReturnVal class for functions that can fail */
	Util::ReturnVal res = SafeDivide(6, 2);
	if (res.Failed())
	{
		return 1;
	}

	return 0;
}