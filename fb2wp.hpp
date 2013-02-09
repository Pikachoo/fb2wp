#ifndef FB2WP_HPP_
#define FB2WP_HPP_

#include <boost/algorithm/string/replace.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
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
			std::vector<std::string> genre, title, name, publisher, publisherCity, publisherYear, publisherISBN, authorFirstName,
					authorLastName, tales, titles, imagesEncoded, imagesIDs, imagesDecoded;
	};

	struct settings_T
	{
			std::string blogURL, blogTitle, blogDescription, blogLanguage, blogPubDate, authorNickName, authorDisplayName,
					authorEmail, generatorVersion, postStatus, postType, postVisibility, postComments, postCategoryName,
					postCategoryNiceName, postDate, postDateGMT, postPubDate;
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
			void SearchInVector(const char *pattern, std::vector<std::string> &text, std::vector<std::string> &storage);
			void ReverseSearchInVector(const char *pattern, std::vector<std::string> &text, std::vector<std::string> &storage);

			void SearchPrimaryInfo();
			void SearchAuthorsInfo();
			void SearchContent();
			void SearchImages();

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
			void PrepareImages();

			void SaveHeader();
			void SaveBody();
			void SaveFooter();
			void SaveImages();

			void MarkupCleaner(std::vector<std::string> &text);
			std::string StringCleaner(std::string &text);
			std::string Replace(std::string &text, std::string &s, std::string &d);
			std::string CyrToLat(std::string &text);

			inline bool IsBase64(unsigned char c);
			std::string DecodeImage(std::string const &encoded_string);
	};

	extern Book Book;
	extern Settings Settings;
	extern XML XML;
}

#endif /* FB2WP_HPP_ */
