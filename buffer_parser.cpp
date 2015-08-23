#include "buffer_parser.h"
#include <stdexcept>

namespace fs
{

std::vector<light_string> buffer_parser::parse(buffer& buf) const
{
	std::vector<light_string> strings;

	while (buf.available_to_read())
	{
		auto end = buf.first_string_end();
		if (!end)
		{
			// For this line there is no \n-symbol yet, will be processed in the next turn
			break;
		}
		auto cur_sz = end - buf.data_to_read();
		strings.push_back(light_string(buf.data_to_read(), cur_sz));
		buf.read(cur_sz);
	}

	return strings;
}

}