#pragma once
#include <vector>
#include <cstring>
#include <utility>
#include <cassert>

namespace fs
{

class buffer
{
public:
	explicit buffer(size_t size) :
		data_(size),
		begin_(0),
		end_(0)
	{
	}

	buffer(buffer&& other) :
		data_(std::move(other.data_)),
		begin_(other.begin_),
		end_(other.end_)
	{
	}

	buffer& operator=(buffer&& other)
	{
		data_ = std::move(other.data_);
		begin_ = other.begin_;
		end_ = other.end_;
	}

	const char* data_to_read() const
	{
		assert(!empty_to_read());
		return data_.data() + begin_;
	}

	const char* data_to_read_end() const
	{
		return data_.data() + end_;
	}

	bool empty_to_read() const
	{
		return begin_ == end_;
	}

	size_t available_to_read() const
	{
		return end_ - begin_;
	}

	void read(size_t cnt)
	{
		assert(begin_ + cnt <= end_);
		begin_ += cnt;
		if (begin_ == end_)
			clear();
	}

	void clear()
	{
		begin_ = 0;
		end_ = 0;
	}

	char* data_to_write()
	{
		assert(!empty_to_write());
		return data_.data() + end_;
	}

	bool empty_to_write() const
	{
		return end_ == data_.size();
	}

	size_t available_to_write() const
	{
		return data_.size() - end_;
	}

	void write(size_t cnt)
	{
		assert(end_ + cnt <= data_.size());
		end_ += cnt;
	}

	const char* first_string_end() const
	{
		auto end = static_cast<const char*>(memchr(data_to_read(), '\n', available_to_read()));
		return end ? end + 1 : nullptr;
	}

	void terminate_with_newline_if_necessary()
	{
		// If it is empty, full or already terminates than do nothing
		if (empty_to_read() || end_ == data_.size() || data_[end_ - 1] == '\n')
			return;
		data_[end_ - 1] = '\n';
	}

	void move_data_to_begin()
	{
		if (empty_to_read())
			return;

		const auto sz = available_to_read();
		memmove(data_.data(), data_to_read(), sz);
		begin_ = 0;
		end_ = sz;
	}

private:
	std::vector<char>	data_;
	size_t				begin_;
	size_t				end_;
};

}