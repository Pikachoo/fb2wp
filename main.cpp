#include "main.hpp"

int main()
{
	fb2wp::books.find_in("books/");
	fb2wp::books.parse();


	fb2wp::book_skel book;


	/* ===================== *
	 * Get book primary info
	 * ===================== */

	fb2wp::books.regex_search("<genre>(.*?)</genre>", book.genre);
	fb2wp::books.regex_search("<book-name>(.*?)</book-name>", book.book_name);
	fb2wp::books.regex_search("<book-title>(.*?)</book-title>", book.book_title);
	fb2wp::books.regex_search("<publisher>(.*?)</publisher", book.publisher);
	fb2wp::books.regex_search("<city>(.*?)</city>", book.city);
	fb2wp::books.regex_search("<year>(.*?)</year>", book.year);
	fb2wp::books.regex_search("<isbn>(.*?)</isbn>", book.isbn);


	/* ================ *
	 * Get book authors
	 * ================ */

	fb2wp::books.regex_search("<first-name>(.*?)</first-name>", book.first_name);
	fb2wp::books.regex_search("<last-name>(.*?)</last-name>", book.last_name);


	/* ======================================= *
	 * Get book tales per each <section> in it
	 * ======================================= */

	fb2wp::books.regex_search("<section>(.*?)</section>", book.isbn);

//	std::cout << book.genre[0] << std::endl;
//	std::cout << book.book_name[0] << std::endl;
//	std::cout << book.book_title[0] << std::endl;
//	std::cout << book.publisher[0] << std::endl;
//	std::cout << book.city[0] << std::endl;
//	std::cout << book.year[0] << std::endl;
//	std::cout << book.isbn[0] << std::endl;

	return 0;
}
