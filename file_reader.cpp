#include "file_reader.h"
#include <stdexcept>
#include <cassert>
#include "buffer.h"

namespace fs
{

file_reader::file_reader(const std::string& filename) :
	f_(filename, "rb")
{
}

file_reader::~file_reader()
{
}

void file_reader::read(buffer& buf)
{
	auto read = fread(buf.data_to_write(), 1, buf.available_to_write(), f_.handle());
	if (read != buf.available_to_write())
	{
		if (!feof(f_.handle()))
			throw std::runtime_error("failed to read from file");
	}

	assert(read <= buf.available_to_write());
	buf.write(read);
}

}
