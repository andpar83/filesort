#pragma once
#include <cstdio>
#include <string>

namespace fs
{

class file_handle
{
public:
	file_handle(const std::string& filename, const std::string& mode);
	~file_handle();

	FILE* handle() const { return f_; }

private:
	// Not implemented
	file_handle(const file_handle&);
	void operator=(const file_handle&);

private:
	FILE*	f_;
};

}