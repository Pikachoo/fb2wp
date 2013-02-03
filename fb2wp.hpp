#ifndef FB2WP_HPP_
#define FB2WP_HPP_

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include <boost/tr1/regex.hpp>

#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace fb2wp
{
	struct skel_book
	{
			std::vector<std::string> genre, book_title, book_name, publisher, city, year, isbn,

			first_name, last_name,

			tales, titles;
	};

	struct skel_settings
	{
			std::string blogURL, blogTitle, blogDescription, blogLanguage,

			postAuthor, postStatus, postType, postVisibility, postComments,

			postDate, postDateGMT, postPubDate;
	};

	class books
	{
		private:
			typedef std::vector<boost::filesystem::path> file_vector;
			file_vector file_list;

			skel_book book;
			skel_settings settings;

			std::string text;

		public:
			void find_books(const char *search_dir);

			void load_settings(const char *file_name);
			void load_book(const char *file_name);

			void get_the_primary_info();
			void get_the_authors_info();
			void get_the_content();

			file_vector &	get_the_file_list() { return file_list; }
			skel_book &		get_book() { return book; }
			skel_settings &	get_settings() { return settings; }

			void regex_search(const char *pattern, std::vector<std::string> &storage);
			void regex_search_in(const char *pattern, std::vector<std::string> &text, std::vector<std::string> &storage);
	};

	extern books books;
}

#endif /* FB2WP_HPP_ */
