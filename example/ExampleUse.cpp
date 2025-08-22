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

struct LogableExample
{
	void LogStr(std::ostringstream& os, unsigned depth) const
	{
		os << "Custom log method called\n";
		os << std::string(depth, ' ');
		os << "Can be on multiple lines";
	}
};

int main()
{
	/* This is a simple example of using coloured text with the Util library */
	Util::Print<Util::Colour::LightAqua>("Hello, World!\n");

	/* Example of using custom log functions */
	LogableExample object;
	Util::PrintLn(object);

	/* Example of auto de-referencing pointers */
	int temp = 3;
	int* ptr = &temp;
	Util::PrintLn(ptr);

	int** ptrRecursion = &ptr;
	Util::PrintLn("PointerRecursion: ", ptrRecursion);

	int* null = nullptr;
	Util::PrintLn(null);

	/* Example of using an iterator with the log */
	std::array<LogableExample, 2> array = {};
	Util::Log("Example-Array", array);

	/* Vector example usage */
	Util::Vec<4, int> vecA(2, 3, 4, 5);
	vecA += vecA;

	Util::Vec<4, int> vecB(5);
	Util::Vec<4, int> vecC = vecA + vecB;

	Util::Log("Vector: ", vecC);

	/* Check vectors are not equal */
	Util::Log("Are vectors equal: ", vecA != vecB);

	/* Example of using the Util::ReturnVal class for functions that can fail */
	Util::ReturnVal res = SafeDivide(6, 0);
	if (res.Failed())
	{
		return 1;
	}

	return 0;
}
