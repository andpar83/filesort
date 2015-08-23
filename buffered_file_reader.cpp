#include "buffered_file_reader.h"
#include <cassert>
#include <stdexcept>

namespace fs
{

buffered_file_reader::buffered_file_reader(const std::string& filename, size_t buffer_size) :
	file_(filename),
	buf_(buffer_size)
{
}

buffered_file_reader::~buffered_file_reader()
{
}

light_string buffered_file_reader::read_string()
{
	if (buf_.empty_to_read())
		file_.read(buf_);

	auto end = buf_.first_string_end();
	if (!end)
	{
		buf_.move_data_to_begin();
		file_.read(buf_);
		end = buf_.first_string_end();
		if (!end)
			throw std::logic_error("file is not terminated with a newline character");
	}

	light_string r(buf_.data_to_read(), end - buf_.data_to_read());
	buf_.read(r.size());
	return r;
}

}