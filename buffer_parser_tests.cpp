#include "buffer_parser_tests.h"
#include "buffer_parser.h"
#include "test_utils.h"

namespace fs { namespace test
{ 

void buffer_parser_tests::test()
{
	test_empty_buffer();
	test_parse_single_string();
	test_parse_multiple_strings();
	test_parse_incomplete_single_string();
	test_parse_incomplete_multiple_strings();
}

void buffer_parser_tests::test_empty_buffer()
{
	buffer_parser parser;
	auto buf = buffer_from_string("");
	auto r = parser.parse(buf);
	TEST_CHECK(r.empty());
	TEST_CHECK(buf.empty_to_read());
}

void buffer_parser_tests::test_parse_single_string()
{
	{
		buffer_parser parser;
		auto buf = buffer_from_string("zzz\n");
		auto r = parser.parse(buf);
		TEST_CHECK(r.size() == 1);
		TEST_CHECK(r[0].to_string() == "zzz\n");
		TEST_CHECK(buf.empty_to_read());
	}

	{
		buffer_parser parser;
		auto buf = buffer_from_string("\n");
		auto r = parser.parse(buf);
		TEST_CHECK(r.size() == 1);
		TEST_CHECK(r[0].to_string() == "\n");
		TEST_CHECK(buf.empty_to_read());
	}
}

void buffer_parser_tests::test_parse_multiple_strings()
{
	buffer_parser parser;
	auto buf = buffer_from_string("zzz\nf\n\nddddd\n");
	auto r = parser.parse(buf);
	TEST_CHECK(r.size() == 4);
	TEST_CHECK(r[0].to_string() == "zzz\n");
	TEST_CHECK(r[1].to_string() == "f\n");
	TEST_CHECK(r[2].to_string() == "\n");
	TEST_CHECK(r[3].to_string() == "ddddd\n");
	TEST_CHECK(buf.empty_to_read());
}

void buffer_parser_tests::test_parse_incomplete_single_string()
{
	buffer_parser parser;
	auto buf = buffer_from_string("aaa");
	auto r = parser.parse(buf);
	TEST_CHECK(r.empty());
	TEST_CHECK(buf.available_to_read() == 3);
}

void buffer_parser_tests::test_parse_incomplete_multiple_strings()
{
	buffer_parser parser;
	auto buf = buffer_from_string("aaa\nb\n\ncccc");
	auto r = parser.parse(buf);
	TEST_CHECK(r.size() == 3);
	TEST_CHECK(r[0].to_string() == "aaa\n");
	TEST_CHECK(r[1].to_string() == "b\n");
	TEST_CHECK(r[2].to_string() == "\n");
	TEST_CHECK(buf.available_to_read() == 4);
}

}}