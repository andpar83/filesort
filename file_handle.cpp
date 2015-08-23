#include "file_handle.h"
#include <cassert>
#include <stdexcept>

namespace fs
{

file_handle::file_handle(const std::string& filename, const std::string& mode) :
	f_(fopen(filename.c_str(), mode.c_str()))	
{
	if (!f_)
		throw std::runtime_error("failed to open file");
}

file_handle::~file_handle()
{
	auto ret = fclose(f_);
	assert(!ret);
}

}