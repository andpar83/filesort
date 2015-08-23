#include "file_sort.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <queue>
#include <functional>
#include <utility>
#include "file_reader.h"
#include "file_writer.h"
#include "buffer.h"
#include "buffer_parser.h"
#include "buffered_file_reader.h"
#include "string_sort.h"

namespace fs { namespace utils
{

namespace impl
{

void merge_sorted_files(const std::string& out_filename, const std::vector<std::string>& files)
{
	typedef std::pair<light_string, size_t> string_and_file;
	std::priority_queue<string_and_file, std::vector<string_and_file>, std::greater<string_and_file>> min_q;

	std::vector<std::unique_ptr<buffered_file_reader>> readers;
	const size_t MERGE_FILE_BUFFER = 10 * 1024 * 1024;
	for (size_t i = 0; i < files.size(); ++i)
	{
		readers.emplace_back(new buffered_file_reader(files[i], MERGE_FILE_BUFFER));
		if (readers.back()->data_available())
			min_q.push(std::make_pair(readers.back()->read_string(), i));
	}

	file_writer out(out_filename);

	while (!min_q.empty())
	{
		auto cur = min_q.top();
		min_q.pop();

		out.write(cur.first);

		if (readers[cur.second]->data_available())
			min_q.push(std::make_pair(readers[cur.second]->read_string(), cur.second));
	}
}

}

void file_sort(const std::string& in_filename, const std::string& out_filename)
{
	const std::uint64_t SPLIT_SIZE = 1024ULL * 1024 * 1024;
	file_reader in(in_filename);
	buffer buf(SPLIT_SIZE);

	size_t tmp_file_num = 0;
	std::vector<std::string> created_files;

	buffer_parser parser;
	
	while (!in.eof() || !buf.empty_to_read())
	{
		in.read(buf);
		if (buf.empty_to_read())
			break;
		buf.terminate_with_newline_if_necessary();

		auto strings = parser.parse(buf);

		string_sort(strings);

		const auto tmp_file_name = in_filename + ".tmp." + std::to_string(tmp_file_num++);
		created_files.push_back(tmp_file_name);
		file_writer out(tmp_file_name);
		for (const auto& s : strings)
			out.write(s);

		buf.move_data_to_begin();
	}

	impl::merge_sorted_files(out_filename, created_files);
}

}}