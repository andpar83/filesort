#pragma once
#include <string>
#include <cstdint>
#include "file_handle.h"
#include "light_string.h"

namespace fs
{

class buffer;

class file_writer
{
public:
	explicit file_writer(const std::string& filename);
	~file_writer();

	void write(buffer& b);
	void write(buffer& b, size_t cnt);
	void write(const std::string& s);
	void write(const light_string& s);

	std::uint64_t written() const { return written_; }

private:
	file_handle		f_;
	std::uint64_t	written_;
};

}