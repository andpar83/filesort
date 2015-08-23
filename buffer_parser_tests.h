#pragma once

namespace fs { namespace test
{

class buffer_parser_tests
{
public:
	static void test();

private:
	static void test_empty_buffer();
	static void test_parse_single_string();
	static void test_parse_multiple_strings();
	static void test_parse_incomplete_single_string();
	static void test_parse_incomplete_multiple_strings();
};

}}