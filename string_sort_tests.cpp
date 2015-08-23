#include "string_sort_tests.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include "string_sort.h"
#include "test_utils.h"
#include "test_data_generator.h"

namespace fs { namespace test
{

namespace impl
{

void check_sort(const std::vector<std::string>& data, bool timing)
{
	auto light_data = light_from_normal(data);

	const auto my_start_time = std::chrono::system_clock::now();
	utils::string_sort(light_data);
	const auto my_end_time = std::chrono::system_clock::now();

	if (timing)
	{
		std::cout << "My sort time " << std::chrono::duration_cast<std::chrono::milliseconds>(my_end_time - my_start_time).count()
			<< " milliseconds" << std::endl;
	}

	auto sorted_data = data;

	const auto std_start_time = std::chrono::system_clock::now();
	std::sort(sorted_data.begin(), sorted_data.end());
	const auto std_end_time = std::chrono::system_clock::now();

	TEST_CHECK(light_data.size() == data.size());

	for (size_t i = 0; i < data.size(); ++i)
	{
		TEST_CHECK(light_data[i].to_string() == sorted_data[i]);
	}

	if (timing)
	{
		std::cout << "Std sort time " << std::chrono::duration_cast<std::chrono::milliseconds>(std_end_time - std_start_time).count()
			<< " milliseconds" << std::endl;
	}
}

}

void string_sort_tests::test()
{
	random_small_test();
	random_big_test();
}

void string_sort_tests::random_small_test()
{
	test_data_generator generator;
	const auto data = generator.generate_strings(100);
	impl::check_sort(data, false);
}

void string_sort_tests::random_big_test()
{
	test_data_generator generator;
	const auto data = generator.generate_strings(10000000);
	impl::check_sort(data, true);
}

}}