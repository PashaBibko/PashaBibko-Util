#include <iostream>
#include <array>

#include <Util.h>

static PB::Util::ReturnVal<int> SafeDivide(int x, int y)
{
	if (y == 0)
		return PB::Util::FunctionFail<>("");

	return x / y;
}

struct LogableExample
{
	void LogStr(PB::Util::LogStream& stream) const
	{
		stream << "Custom log method called" << PB::Util::NewLine;
		stream << "Can be on multiple lines" << PB::Util::NewLine;
		stream << "And will be indented properly";
	}
};

PB_TEST(testGroup, testName)
{
	PB::Util::PrintLn("Test has been called");
};

int main()
{
	/**/
	PB::Util::PrintLn<PB::Util::Colour::LightRed>(PB::Util::TempFilePath("file.txt"));

	/* This is a simple example of using coloured text with the Util library */
	PB::Util::Print<PB::Util::Colour::LightAqua>("Hello, World!", PB::Util::NewLine);

	/* Example of using custom log functions */
	LogableExample object;
	PB::Util::PrintLn(object);

	/* Example of auto de-referencing pointers */
	int temp = 3;
	int* ptr = &temp;
	PB::Util::PrintLn(ptr);

	int** ptrRecursion = &ptr;
	PB::Util::PrintLn("PointerRecursion: ", ptrRecursion);

	int* null = nullptr;
	PB::Util::PrintLn(null);

	/* Example of using an iterator with the log */
	std::array<LogableExample, 2> array = {};
	PB::Util::Log("Example-Array", array);

	/* Vector example usage */
	PB::Util::Vec<4, int> vecA(2, 3, 4, 5);
	vecA += vecA;

	PB::Util::Vec<4, int> vecB(5);
	PB::Util::Vec<4, int> vecC = vecA + vecB;

	PB::Util::Log("Vector: ", vecC);

	/* Check vectors are not equal */
	PB::Util::Log("Are vectors equal: ", vecA != vecB);

	/* Example of using the PB::Util::ReturnVal class for functions that can fail */
	PB::Util::ReturnVal res = SafeDivide(6, 0);
	if (res.Failed())
	{
		return 1;
	}

	return 0;
}
