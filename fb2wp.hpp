#ifndef FB2WP_HPP_
#define FB2WP_HPP_

#include <boost/algorithm/string/replace.hpp>
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
	struct book_T
	{
			std::vector<std::string> genre, title, name,
			publisher, publisherCity, publisherYear, publisherISBN,
			authorFirstName, authorLastName,
			tales, titles;
	};

	struct settings_T
	{
			std::string blogURL, blogTitle, blogDescription, blogLanguage, blogPubDate,
					authorNickName, authorDisplayName, authorEmail,
					generatorVersion,
					postStatus, postType, postVisibility, postComments,
					postDate, postDateGMT, postPubDate;
	};

	struct file_export_T
	{
			std::string xml_header;
			std::string xml_content;
			std::string xml_footer;
	};

	class Book
	{
		private:
			typedef std::vector<boost::filesystem::path> file_vector;
			file_vector __file_list;
			std::string __text;
			book_T __book;

		public:
			void Find(const char *search_dir);

			void Read(const char *file_name);

			void Search(const char *pattern, std::vector<std::string> &storage);
			void SearchInVector(const char *pattern, std::vector<std::string> &text,
					std::vector<std::string> &storage);

			void SearchPrimaryInfo();
			void SearchAuthorsInfo();
			void SearchContent();

			book_T & GetBook();
			book_T & GetContent();
			file_vector & GetFileList();
	};

	class Settings
	{
		private:
			settings_T __settings;

		public:
			void Read(const char *file_name);

			settings_T & GetSettings();
	};

	class XML
	{
		private:
			file_export_T __file_export;

			std::string __xml_header;
			std::string __xml_body;
			std::string __xml_footer;

		public:
			file_export_T & GetFileExport();

			std::string Read(const char *file_name);

			void PrepareHeader();
			void PrepareBody();
			void PrepareFooter();

			void SaveHeader();
			void SaveBody();
			void SaveFooter();

			std::string Replace(std::string &text, std::string &s, std::string &d);
	};

	extern Book Book;
	extern Settings Settings;
	extern XML XML;
}

#endif /* FB2WP_HPP_ */
