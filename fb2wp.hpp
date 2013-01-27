#ifndef FB2WP_HPP_
#define FB2WP_HPP_

#include <boost/filesystem.hpp>
#include <boost/tr1/regex.hpp>

#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace fb2wp
{
	struct book_skel
	{
			std::vector<std::string> genre, book_title, book_name, publisher, city, year, isbn,

			first_name, last_name,

			tales;
	};

	class books
	{
		private:
			typedef std::vector<boost::filesystem::path> file_vector;

			file_vector file_list;
			std::string text;

		public:
			void find_in(const char *search_dir);
			void load_in_memory(const char *file_path);

			void regex_search(const char *pattern, std::vector<std::string> &storage);

			file_vector get_file_list() { return file_list; }
	};

	extern books books;
}

#endif /* FB2WP_HPP_ */
