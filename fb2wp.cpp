#include "fb2wp.hpp"

class fb2wp::books fb2wp::books;

void fb2wp::books::load_settings(const char *file_name)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_name, pt);

	settings.blogURL = pt.get<std::string>("fb2wp.BlogURL");
	settings.blogTitle = pt.get<std::string>("fb2wp.BlogTitle");
	settings.blogDescription = pt.get<std::string>("fb2wp.BlogDescription");
	settings.blogLanguage = pt.get<std::string>("fb2wp.BlogLanguage");

	settings.postAuthor = pt.get<std::string>("fb2wp.PostAuthor");
	settings.postStatus = pt.get<std::string>("fb2wp.PostStatus");
	settings.postType = pt.get<std::string>("fb2wp.PostType");
	settings.postVisibility = pt.get<std::string>("fb2wp.PostVisibility");
	settings.postComments = pt.get<std::string>("fb2wp.PostComments");

	settings.postDate = pt.get<std::string>("fb2wp.PostDate");
	settings.postDateGMT = pt.get<std::string>("fb2wp.PostDateGMT");
	settings.postPubDate = pt.get<std::string>("fb2wp.PostPubDate");
}

void fb2wp::books::find_books(const char *search_dir)
{
	file_list.clear();

	boost::filesystem::path directory(search_dir);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory))
	{
		/* ================= *
		 * Get the file list
		 * ================= */

		std::copy(boost::filesystem::directory_iterator(directory),
				boost::filesystem::directory_iterator(), std::back_inserter(file_list));
	}

	/* =============== *
	 * Sorting results
	 * =============== */

	sort(file_list.begin(), file_list.end());
}

void fb2wp::books::load_book(const char *file_name)
{
	text.clear();

	/* ============= *
	 * Read the file
	 * ============= */

	std::string line;
	std::ifstream myfile;

	myfile.open(file_name);

	while (myfile.good())
	{

		std::getline(myfile, line);
		text.append(line);
	}

	myfile.close();
}

void fb2wp::books::get_the_primary_info()
{
	/* ================ *
	 * Get primary info
	 * ================ */

	fb2wp::books.regex_search("(?<=<genre>)(.*?)(?=</genre>)", book.genre);
	fb2wp::books.regex_search("(?<=<book-name>)(.*?)(?=</book-name>)", book.book_name);
	fb2wp::books.regex_search("(?<=<book-title>)(.*?)(?=</book-title>)", book.book_title);
	fb2wp::books.regex_search("(?<=<publisher>)(.*?)(?=</publisher>)", book.publisher);
	fb2wp::books.regex_search("(?<=<city>)(.*?)(?=</city>)", book.city);
	fb2wp::books.regex_search("(?<=<year>)(.*?)(?=</year>)", book.year);
	fb2wp::books.regex_search("(?<=<isbn>)(.*?)(?=</isbn>)", book.isbn);
}

void fb2wp::books::get_the_authors_info()
{
	/* =========== *
	 * Get authors
	 * =========== */

	fb2wp::books.regex_search("(?<=<first-name>)(.*?)(?=</first-name>)", book.first_name);
	fb2wp::books.regex_search("(?<=<last-name>)(.*?)(?=</last-name>)", book.last_name);
}

void fb2wp::books::get_the_content()
{
	/* ================================== *
	 * Get tales per each <section> in it
	 * ================================== */

	fb2wp::books.regex_search("(?<=<section>)(.*?)(?=</section>)", book.tales);
	fb2wp::books.regex_search_in("(?<=<title>)(.*?)(?=</title>)", book.tales, book.titles);
}

void fb2wp::books::regex_search(const char *pattern, std::vector<std::string> &storage)
{
	/* ========================= *
	 * Regular expression search
	 * ========================= */

	boost::regex regex(pattern, boost::regex::perl);

	for (boost::sregex_token_iterator it(text.begin(), text.end(), regex, 0), it_end; it != it_end;
			++it)
	{
		storage.push_back(*it);
	}

	std::cout << "[" << storage.size() << "]" << std::endl;
}

void fb2wp::books::regex_search_in(const char *pattern, std::vector<std::string> &text,
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
