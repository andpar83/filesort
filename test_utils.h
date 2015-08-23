#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include "buffer.h"
#include "light_string.h"

namespace fs { namespace test
{ 

//! Simple exception which is thrown when test fails. Doesn't contain any useful info for simplicity
class test_exception : public std::logic_error
{
public:
	test_exception() : std::logic_error("test failed")
	{
	}
};

//! Simple test check correct conditions. Throws test_exception if cond is false
#define TEST_CHECK(cond)					\
do											\
{											\
	if (!(cond))							\
		throw test_exception();				\
}											\
while (false)


//! Fills in buffer object with data from string
buffer buffer_from_string(const std::string& s);

//! Converts vector of usual strings to vector of lisght strings (v must not die before result array)
std::vector<light_string> light_from_normal(const std::vector<std::string>& v);

}}
