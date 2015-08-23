#pragma once
#include <cassert>
#include <cstring>
#include <string>
#include <algorithm>

namespace fs
{

//! String class which contains pointer to the beginning and size of unmodifiable non-empty string
/**
 *	String shouldn't be null-terminated but should be newl-line-symbol terminated
 *	This string does not own its resources
 */
class light_string
{
public:
	light_string(const char* s, size_t size) :
		s_(s),
		size_(size)
	{
		assert(s_);
		assert(size_);
		assert(s_[size_ - 1] == '\n');
	}

	explicit light_string(const std::string& s) :
		s_(s.data()),
		size_(s.size())
	{
		assert(size_);
		assert(s_[size_ - 1] == '\n');
	}

	const char* data() const { return s_; }
	size_t size() const { return size_; }

	//! This method makes easier to sort strings of different lengths
	/**
	 *	It lets assume that strings have the same length and sorter string will be a smaller one
	 */
	int get_char(size_t pos) const { return pos < size_ ? s_[pos] : -1; }

	//! Converts to std::string for testing purposes
	std::string to_string() const
	{
		return std::string(s_, size_);
	}

private:
	const char*	s_;
	size_t		size_;
};

inline bool operator<(const light_string& lhs, const light_string& rhs)
{
	auto r = memcmp(lhs.data(), rhs.data(), std::min(lhs.size(), rhs.size()));
	if (r)
		return r < 0;
	return lhs.size() < rhs.size();
}

}