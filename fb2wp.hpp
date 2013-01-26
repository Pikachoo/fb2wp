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
		std::vector<std::string>	genre,
									book_title,
									book_name,
									publisher,
									city,
									year,
									isbn,

									first_name,
									last_name,

									tales;
	};

	class books
	{
		private:
			typedef std::vector<boost::filesystem::path> vector;

		public:
			vector v;

			std::string text;

			void find_in(const char *search_dir);
			void parse();

			void set_field(const char *pattern);

			void regex_search(const char *pattern, std::vector<std::string> &storage);
	};

	extern class books books;
}

#endif /* FB2WP_HPP_ */
