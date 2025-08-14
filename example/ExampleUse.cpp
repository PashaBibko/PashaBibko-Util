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
	std::string LogStr() const
	{
		return "Custom Log method called";
	}
};

CTG_Python("len([1, 2, 3])");

CTG_Python("print(\"hello world\")");

int main()
{
	/* Initalises the compile-time python */
	Util::CTG::InitialisePythonCTG();

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
	std::array<int, 5> array = { 1, 2, 3, 4, 5 };
	Util::Log("Example-Array", array);

	/* Vector example usage */
	Util::Vec<4, int> vecA(2, 3, 4, 5);
	vecA += vecA;

	Util::Vec<4, int> vecB(5);
	Util::Vec<4, int> vecC = vecA + vecB;

	Util::Log("Vector: ", vecC);

	/* Example of using the Util::ReturnVal class for functions that can fail */
	Util::ReturnVal res = SafeDivide(6, 0);
	if (res.Failed())
	{
		return 1;
	}

	return 0;
}