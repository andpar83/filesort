#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <random>

namespace fs
{

class test_data_generator
{
public:
	test_data_generator();
	~test_data_generator();

	void generate_file(const std::string& filename, std::uint64_t size);
	std::vector<std::string> generate_strings(size_t num_lines);

private:
	static std::string get_symbols();

	std::string generate_string(size_t size);

private:
	std::string								symbols_;
	std::default_random_engine				gen_;
	//! For symbol generation
	std::uniform_int_distribution<size_t>	sym_distr_;
	//! For string size generation
	std::uniform_int_distribution<size_t>	size_distr_;
};

}