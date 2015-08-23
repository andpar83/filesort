#pragma once
#include <string>
#include "file_reader.h"
#include "light_string.h"
#include "buffer.h"

namespace fs
{

class buffered_file_reader
{
public:
	explicit buffered_file_reader(const std::string& filename, size_t buffer_size);
	~buffered_file_reader();

	bool eof() const { return file_.eof(); }
	bool data_available() const { return buf_.available_to_read() || !eof(); }
	light_string read_string();

private:
	file_reader file_;
	buffer		buf_;
};

}