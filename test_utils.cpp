#include "test_utils.h"

namespace fs { namespace test
{ 

buffer buffer_from_string(const std::string& s)
{
	buffer buf(s.size());
	if (!s.empty())
	{
		memcpy(buf.data_to_write(), s.data(), s.size());
		buf.write(s.size());
	}
	return buf;
}

std::vector<light_string> light_from_normal(const std::vector<std::string>& v)
{
	std::vector<light_string> r;
	for (const auto& s : v)
		r.emplace_back(s);
	return r;
}

}}