#include "all_tests.h"
#include <iostream>
#include "buffer_parser_tests.h"
#include "string_sort_tests.h"

namespace fs { namespace test
{

void all_tests::test()
{
	buffer_parser_tests::test();
	string_sort_tests::test();
	std::cout << "ALL TESTS SUCCEEDED" << std::endl;
}

}}