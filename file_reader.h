#pragma once
#include <string>
#include "file_handle.h"

namespace fs
{

class buffer;

class file_reader
{
public:
	explicit file_reader(const std::string& filename);
	~file_reader();

	bool eof() const { return feof(f_.handle()) != 0; }
	void read(buffer& buf);

private:
	file_handle	f_;
};

}