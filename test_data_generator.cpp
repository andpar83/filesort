#include "test_data_generator.h"
#include <random>
#include "file_writer.h"

namespace fs
{

test_data_generator::test_data_generator() :
	symbols_(get_symbols()),
	gen_((std::random_device())()),
	sym_distr_(0, symbols_.size() - 1),
	size_distr_(10, 100)
{
}

test_data_generator::~test_data_generator()
{
}

void test_data_generator::generate_file(const std::string& filename, std::uint64_t size)
{
	// Result file
	file_writer out(filename);

	while (out.written() < size)
	{
		auto sz = size_distr_(gen_);
		if (out.written() + sz > size)
			sz = static_cast<size_t>(size - out.written());
		
		auto line = generate_string(sz);
		out.write(line);
	}
}

std::vector<std::string> test_data_generator::generate_strings(size_t num_lines)
{
	std::vector<std::string> r;

	for (size_t i = 0; i < num_lines; ++i)
	{
		const auto sz = size_distr_(gen_);
		r.push_back(generate_string(sz));
	}

	return r;
}

std::string test_data_generator::generate_string(size_t size)
{
	assert(size);
	std::string line(size, 0);
	for (size_t i = 0; i < size - 1; ++i)
		line[i] = symbols_[sym_distr_(gen_)];
	line.back() = '\n';
	return line;
}

std::string test_data_generator::get_symbols()
{
	// Allowed symbols
	std::string symbols;
	for (char ch = 'a'; ch <= 'z'; ++ch)
		symbols.push_back(ch);
	for (char ch = 'A'; ch <= 'Z'; ++ch)
		symbols.push_back(ch);
	for (char ch = '0'; ch <= '9'; ++ch)
		symbols.push_back(ch);
	return symbols;
}

}