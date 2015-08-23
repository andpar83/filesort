#include "string_sort.h"
#include <cstdint>
#include <utility>
#include <algorithm>
#include <future>

namespace fs { namespace utils
{

namespace impl
{

struct positional_less_comparator
{
	positional_less_comparator(size_t p) : pos(p)
	{
	}

	bool operator()(const light_string& lhs, const light_string& rhs)
	{
		if (pos >= lhs.size() || pos >= rhs.size())
			return lhs.size() < rhs.size();
		auto r = memcmp(lhs.data() + pos, rhs.data() + pos, std::min(lhs.size() - pos, rhs.size() - pos));
		if (r)
			return r < 0;
		return lhs.size() < rhs.size();
	}

	size_t pos;
};

std::pair<std::int64_t, std::int64_t> string_partition
(
	std::vector<light_string>& data,
	const size_t lo,
	const size_t hi,
	const size_t pos
)
{
	assert(lo <= hi && hi < data.size());

	auto lt = lo, gt = hi;
	const auto pivot = data[lo].get_char(pos);

	for (auto i = lo + 1; i <= gt;)
	{
		const auto cur = data[i].get_char(pos);
		if (cur < pivot)
		{
			std::swap(data[lt], data[i]);
			++lt;
			++i;
		}
		else if (cur > pivot)
		{
			std::swap(data[i], data[gt]);
			--gt;
		}
		else
			++i;
	}

	return std::make_pair(static_cast<std::int64_t>(lt) - 1, gt + 1);
}

void string_sort(std::vector<light_string>& data, const std::int64_t lo, const std::int64_t hi, const size_t pos);

std::future<void> run_async_sort(std::vector<light_string>& data, const std::int64_t lo, const std::int64_t hi, const size_t pos)
{
	const size_t MIN_PARALLEL_SIZE = 50000;

	std::future<void> result;
	if (hi + 1 - lo >= MIN_PARALLEL_SIZE)
		result = std::async(&string_sort, std::ref(data), lo, hi, pos);
	return result;
}

void string_sort(std::vector<light_string>& data, const std::int64_t lo, const std::int64_t hi, const size_t pos)
{
	if (hi <= lo)
		return;

	const auto part = string_partition(data, static_cast<size_t>(lo), static_cast<size_t>(hi), pos);
	const auto less_last_index = part.first;
	const auto greater_first_index = part.second;
	
	std::future<void> future_less = run_async_sort(data, lo, less_last_index, pos);
	std::future<void> futute_greater = run_async_sort(data, greater_first_index, hi, pos);

	if (!future_less.valid())
		string_sort(data, lo, less_last_index, pos);
	if (!futute_greater.valid())
		string_sort(data, greater_first_index, hi, pos);

	// This partition is not empty and if strings are not finished 
	// (by length, which means that get_char returns -1) yet, continue sorting by next symbol
	if (data[static_cast<size_t>(less_last_index + 1)].get_char(pos) >= 0)
		string_sort(data, less_last_index + 1, greater_first_index - 1, pos + 1);

	if (future_less.valid())
		future_less.wait();
	if (futute_greater.valid())
		futute_greater.wait();
}

}

void string_sort(std::vector<light_string>& data)
{
	impl::string_sort(data, 0, static_cast<std::int64_t>(data.size()) - 1, 0);
}

}}