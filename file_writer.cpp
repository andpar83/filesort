#include "file_writer.h"
#include <stdexcept>
#include <cassert>
#include "buffer.h"

namespace fs
{

file_writer::file_writer(const std::string& filename) :
	f_(filename, "wb"),
	written_(0)
{
}

file_writer::~file_writer()
{
}

void file_writer::write(buffer& b)
{
	write(b, b.available_to_read());
}

void file_writer::write(buffer& b, size_t cnt)
{
	assert(cnt <= b.available_to_read());
	if (b.empty_to_read())
		return;
	if (fwrite(b.data_to_read(), 1, cnt, f_.handle()) != cnt)
		throw std::runtime_error("failed to write to the file");
	written_ += cnt;
	b.read(cnt);
}

void file_writer::write(const std::string& s)
{
	if (s.empty())
		return;
	if (fwrite(s.data(), 1, s.size(), f_.handle()) != s.size())
		throw std::runtime_error("failed to write to the file");
	written_ += s.size();
}

void file_writer::write(const light_string& s)
{
	if (fwrite(s.data(), 1, s.size(), f_.handle()) != s.size())
		throw std::runtime_error("failed to write to the file");
	written_ += s.size();
}

}