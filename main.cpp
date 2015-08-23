#include <string>
#include <iostream>
#include <exception>
#include <chrono>
#include "file_sort.h"
#include "all_tests.h"
#include "test_data_generator.h"

const int SUCCESS = 0;
const int ERROR = 1;
const int INCORRECT_ARGUMENTS = 2;

int print_help()
{
	std::cerr << "Usage	: filesort [IN-FILE]" << std::endl;
	std::cerr << "	or	: filesort [IN-FILE] [OUT-FILE]" << std::endl;
	std::cerr << "	or	: filesort --generate [OUT-FILE] [FILE SIZE IN BYTES]" << std::endl;
	std::cerr << "	or	: filesort --test" << std::endl;
	return INCORRECT_ARGUMENTS;
}

/**
 *	All work on filenames are done with ASCII-strings so could be some problems for non-ASCII characters in paths
 **/
int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2 || !argv[1] || std::string(argv[1]) == "--help")
			return print_help();

		if (std::string(argv[1]) == "--test")
		{
			if (argc != 2)
				return print_help();
			fs::test::all_tests::test();
			return SUCCESS;
		}

		if (std::string(argv[1]) == "--generate")
		{
			if (argc != 4 || !argv[2] || !argv[3])
				return print_help();

			size_t pos = 0;
			const std::string size_arg = argv[3];
			const auto size = std::stoull(size_arg, &pos);
			if (pos != size_arg.size())
				return print_help();

			fs::test_data_generator gen;
			gen.generate_file(argv[2], size);
			return SUCCESS;
		}

		if (argc > 3)
			return print_help();

		const auto start_time = std::chrono::system_clock::now();

		const auto in_filename = argv[1];
		const auto out_filename = argc == 3 && argv[2] ? std::string(argv[2]) : in_filename;

		fs::utils::file_sort(in_filename, out_filename);

		const auto end_time = std::chrono::system_clock::now();
		std::cout << "Execution time " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count()
			<< " seconds" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error happened: " << e.what() << std::endl;
		return ERROR;
	}

	return SUCCESS;
}