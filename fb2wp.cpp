#include "fb2wp.hpp"

class fb2wp::Book fb2wp::Book;
class fb2wp::Settings fb2wp::Settings;
class fb2wp::XML fb2wp::XML;

void fb2wp::Settings::Read(const char *file_name)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_name, pt);

	__settings.blogURL = pt.get<std::string>("fb2wp.BlogURL");
	__settings.blogTitle = pt.get<std::string>("fb2wp.BlogTitle");
	__settings.blogDescription = pt.get<std::string>("fb2wp.BlogDescription");
	__settings.blogLanguage = pt.get<std::string>("fb2wp.BlogLanguage");

	__settings.postAuthor = pt.get<std::string>("fb2wp.PostAuthor");
	__settings.postStatus = pt.get<std::string>("fb2wp.PostStatus");
	__settings.postType = pt.get<std::string>("fb2wp.PostType");
	__settings.postVisibility = pt.get<std::string>("fb2wp.PostVisibility");
	__settings.postComments = pt.get<std::string>("fb2wp.PostComments");

	__settings.postDate = pt.get<std::string>("fb2wp.PostDate");
	__settings.postDateGMT = pt.get<std::string>("fb2wp.PostDateGMT");
	__settings.postPubDate = pt.get<std::string>("fb2wp.PostPubDate");
}

void fb2wp::Book::Find(const char *search_dir)
{
	__file_list.clear();

	boost::filesystem::path directory(search_dir);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory))
	{
		/* ================= *
		 * Get the file list
		 * ================= */

		std::copy(boost::filesystem::directory_iterator(directory),
				boost::filesystem::directory_iterator(), std::back_inserter(__file_list));
	}

	/* =============== *
	 * Sorting results
	 * =============== */

	std::sort(__file_list.begin(), __file_list.end());
}

void fb2wp::Book::Read(const char *file_name)
{
	__text.clear();

	/* ============= *
	 * Read the file
	 * ============= */

	std::string line;
	std::ifstream myfile;

	myfile.open(file_name);

	while (myfile.good())
	{

		std::getline(myfile, line);
		__text.append(line);
	}

	myfile.close();
}

void fb2wp::Book::SearchPrimaryInfo()
{
	/* ================ *
	 * Get primary info
	 * ================ */

	fb2wp::Book.Search("(?<=<genre>)(.*?)(?=</genre>)",  __book.genre);
	fb2wp::Book.Search("(?<=<book-name>)(.*?)(?=</book-name>)", __book.book_name);
	fb2wp::Book.Search("(?<=<book-title>)(.*?)(?=</book-title>)", __book.book_title);
	fb2wp::Book.Search("(?<=<publisher>)(.*?)(?=</publisher>)", __book.publisher);
	fb2wp::Book.Search("(?<=<city>)(.*?)(?=</city>)", __book.city);
	fb2wp::Book.Search("(?<=<year>)(.*?)(?=</year>)", __book.year);
	fb2wp::Book.Search("(?<=<isbn>)(.*?)(?=</isbn>)", __book.isbn);
}

void fb2wp::Book::SearchAuthorsInfo()
{
	/* =========== *
	 * Get authors
	 * =========== */

	fb2wp::Book.Search("(?<=<first-name>)(.*?)(?=</first-name>)", __book.first_name);
	fb2wp::Book.Search("(?<=<last-name>)(.*?)(?=</last-name>)", __book.last_name);
}

void fb2wp::Book::SearchContent()
{
	/* ================================== *
	 * Get tales per each <section> in it
	 * ================================== */

	fb2wp::Book.Search("(?<=<section>)(.*?)(?=</section>)", __book.tales);
	fb2wp::Book.SearchInVector("(?<=<title>)(.*?)(?=</title>)", __book.tales, __book.titles);
}

void fb2wp::Book::Search(const char *pattern, std::vector<std::string> &storage)
{
	/* ========================= *
	 * Regular expression search
	 * ========================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (boost::sregex_token_iterator it(__text.begin(), __text.end(), regex, 0), it_end; it != it_end;
			++it)
	{
		storage.push_back(*it);
	}

	std::cout << "[" << storage.size() << "]" << std::endl;
}

void fb2wp::Book::SearchInVector(const char *pattern, std::vector<std::string> &text,
		std::vector<std::string> &storage)
{
	/* ================================================= *
	 * Regular expression search in the vector of string
	 * ================================================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (std::vector<std::string>::iterator it = text.begin(), it_end = text.end(); it != it_end;
			++it)
	{
		std::copy(std::tr1::sregex_token_iterator(it->begin(), it->end(), regex),
				std::tr1::sregex_token_iterator(), std::back_inserter(storage));
	}

	std::cout << "[" << storage.size() << "]" << std::endl;
}

fb2wp::Book::file_vector & fb2wp::Book::GetFileList()
{
	return __file_list;
}

fb2wp::book_T & fb2wp::Book::GetBook()
{
	return __book;
}

fb2wp::settings_T & fb2wp::Settings::GetSettings()
{
	return __settings;
}

fb2wp::file_export_T & fb2wp::XML::GetFileExport()
{
	return __file_export;
}
