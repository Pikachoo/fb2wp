#include "main.hpp"

int main()
{
	fb2wp::books.load_settings("config.ini");

	fb2wp::books.find_books("books/");
	fb2wp::books.load_book(fb2wp::books.get_the_file_list()[0].c_str());

	fb2wp::books.get_the_primary_info();
	fb2wp::books.get_the_authors_info();
	fb2wp::books.get_the_content();



	std::cout << fb2wp::books.get_book().genre[0] << std::endl;
	std::cout << fb2wp::books.get_book().book_name[0] << std::endl;
	std::cout << fb2wp::books.get_book().book_title[0] << std::endl;
	std::cout << fb2wp::books.get_book().publisher[0] << std::endl;
	std::cout << fb2wp::books.get_book().city[0] << std::endl;
	std::cout << fb2wp::books.get_book().year[0] << std::endl;
	std::cout << fb2wp::books.get_book().isbn[0] << std::endl;

	std::cout << fb2wp::books.get_settings().blogURL << std::endl;
	std::cout << fb2wp::books.get_settings().blogTitle << std::endl;
	std::cout << fb2wp::books.get_settings().blogDescription << std::endl;
	std::cout << fb2wp::books.get_settings().blogLanguage << std::endl;

	std::cout << fb2wp::books.get_settings().postAuthor << std::endl;
	std::cout << fb2wp::books.get_settings().postStatus << std::endl;
	std::cout << fb2wp::books.get_settings().postType << std::endl;
	std::cout << fb2wp::books.get_settings().postVisibility << std::endl;
	std::cout << fb2wp::books.get_settings().postComments << std::endl;

	std::cout << fb2wp::books.get_settings().postDate << std::endl;
	std::cout << fb2wp::books.get_settings().postDateGMT << std::endl;
	std::cout << fb2wp::books.get_settings().postPubDate << std::endl;


	return 0;
}
